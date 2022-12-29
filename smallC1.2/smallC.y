////////////////////////////////////////////////////////
//声明部分
%{
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>

#define bool int
#define true 1
#define false 0

#define txmax 100     /* 符号表容量 */
#define al 10         /* 标识符的最大长度 */
#define amax 2048     /* 地址上界*/
#define levmax 3      /* 最大允许过程嵌套声明层数*/
#define cxmax 200     /* 最多的虚拟机代码数 */
#define stacksize 500 /* 运行时数据栈元素最多为500个 */

/* 符号表中的类型 */
enum object {
    constant, 
    variable, 
    procedure,
};

/* 符号表结构 */
struct tablestruct
{
   char name[al];      /* 名字 */
   enum object kind;   /* 类型：const，var或procedure */
   int val;            /* 数值，仅const使用 */
	 int level;          /* 所处层，仅const不使用 */ 
	 int adr;            /* 地址，仅const不使用 */
	 int size;           /* 需要分配的数据区空间, 仅procedure使用 */
};
struct tablestruct table[txmax]; /* 符号表 */

/* 虚拟机代码指令 */
enum fct {
    lit,     opr,     lod, 
    sto,     cal,     ini, 
    jmp,     jpc,     jpn,
};

/* 虚拟机代码结构 */
struct instruction
{
	enum fct f;   /* 虚拟机代码指令 */
	int l;        /* 引用层与声明层的层次差 */
	int a;        /* 根据f的不同而不同 */
};
struct instruction code[cxmax]; /* 存放虚拟机代码的数组 */

int tx;         /* 符号表当前尾指针 */
int cx;         /* 虚拟机代码指针, 取值范围[0, cxmax-1] */
int px;         /* 嵌套过程索引表proctable的指针 */
int lev;        /* 层次记录 */
int proctable[3];   /* 嵌套过程索引表，最多嵌套三层 */
char id[al];
int num;
bool listswitch;   /* 显示虚拟机代码与否 */
bool tableswitch;  /* 显示符号表与否 */

FILE* fin;      /* 输入源文件 */
FILE* ftable;	  /* 输出符号表 */
FILE* fcode;    /* 输出虚拟机代码 */
FILE* foutput;  /* 输出出错示意（如有错） */
FILE* fresult;  /* 输出执行结果 */
FILE* finput;	/* 输入内容 */
char fname[al];
int err;
extern int line; 

void init();
void enter(enum object k);
int position(char *s);
void setdx(int n);
void gen(enum fct x, int y, int z);
void listall();
void displaytable();
void interpret();
int base(int l, int* s, int b);

int yylex(void);
void yyerror(char *s);
int redirectInput(FILE*);
%}

////////////////////////////////////////////////////////
//辅助定义部分
%union{
char *ident;
int number;
}


%token CALLSYM CONSTSYM IFSYM PROCSYM
%token READSYM INTSYM WHILESYM WRITESYM FORSYM DOSYM WHENSYM REPEATSYM UNTILSYM
%token LSS LEQ GTR GEQ PLUS MINUS TIMES SLASH LPAREN RPAREN
%token EQL COMMA PERIOD NEQ SEMICOLON NOT EQUALS ELSESYM LBRACE RBRACE
%token MOD XOR ODDSYM MOREPLUS MOREMINUS AND OR
%token CONTINUESYM EXITSYM BREAKSYM

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSESYM  // 下面的优先级高

%nonassoc LOWER_THAN_MORE
%nonassoc MOREPLUS MOREMINUS

%nonassoc LOWER_THAN_SEMICOLON
%nonassoc SEMICOLON

%token <ident> IDENT
%token <number> NUMBER

%type <number> ident
%type <number> vardecl varlist vardef
%type <number> get_table_addr get_code_addr

////////////////////////////////////////////////////////
//规则部分
%%
/* 程序 */
program: block;

/*  分程序 */
block:         {               
                table[tx].adr = cx;				  /* 记录当前层代码的开始位置 */  
                $<number>$ = cx;
               	gen(jmp, 0 , 0);            /* 产生跳转指令，跳转位置未知暂时填0 */
               }
               get_table_addr               /* 记录本层标识符的初始位置 */
               LBRACE constdecl vardecl procdecls 
               {
               	code[$<number>1].a = cx;            /* 把前面生成的跳转语句的跳转位置改成当前位置 */
               	table[$2].adr = cx;         /* 记录当前过程代码地址 */
               	table[$2].size = $5 + 3;    /* 记录当前过程分配数据大小 */
               	gen(ini, 0, $5 + 3);
               	displaytable();
               }
               statement_decl
               {
               	gen(opr, 0 , 0);               	
               	tx = proctable[px];
               }
			   RBRACE
          ;

/*  常量声明 */
constdecl: CONSTSYM constlist SEMICOLON 
         | CONSTSYM constlist %prec LOWER_THAN_SEMICOLON
		 	{
				yyerror("You may have missed a ';'");
			}
		 |
         ;

/* 常量声明列表 */
constlist: constdef 
          | constlist COMMA constdef 
          ;

/* 单个常量 */
constdef: IDENT EQL NUMBER
               {
               	strcpy(id,$1);   
               	num = $3;
               	enter(constant);
               }
        ;

/*  变量声明 */
vardecl: INTSYM varlist SEMICOLON
            {
                $$ = $2;         /* 传递变量声明的个数 */
                setdx($2);       /* 分配变量相对地址 */
            }
	   | INTSYM varlist %prec LOWER_THAN_SEMICOLON
               {
                $$ = $2;         /* 传递变量声明的个数 */
                setdx($2);       /* 分配变量相对地址 */
				yyerror("You may have missed a ';'");
               }
       |
          	{
          		$$ = 0;          /* 没有变量声明 */
          	}
       ;
          		
/* 变量声明列表 */
varlist: vardef 
               {
               	$$ = $1;
               }
       | varlist COMMA vardef 
               {
               	$$ = $1 + $3;  /* 变量声明的个数相加 */
               }
       ;

/* 单个变量 */
vardef: IDENT
            {
              	strcpy(id, $1); 
              	enter(variable); 
              	$$ = 1;
            }
      ;

/*  过程声明 */
procdecls: procdecls procdecl procbody 
          |  
          ;

/*  过程声明头部 */
procdecl: inc_px PROCSYM IDENT SEMICOLON
               {                 
                 strcpy(id, $3);
	               enter(procedure); 
	               proctable[px] = tx;                
               }
          ;

/*  过程声明主体 */
procbody: inc_level block dec_level_px SEMICOLON
        ;

/* 有或没有语句 */
statement_decl: statement_list
			  | 
			  ;

/* 一条或多条语句 */
statement_list: statement
			  | statement_list statement
          	  ;

/*  语句 */
statement:  callstm 
          | compound_stat 
          | if_stat 
          | while_stat 
          | read_stat 
          | write_stat 
		  | expression_stat
		  | exit_stat
		  | for_stat
		  | do_when_stat
		  | repeat_until_stat
		  /* | continue_stat */
		  /* | break_stat */
          ;

/* 复合语句 */
compound_stat: LBRACE statement_decl RBRACE 
           	 ;

expression_stat: expression SEMICOLON
			   | expression %prec LOWER_THAN_SEMICOLON
			   		{
						yyerror("You may have missed a ';'");
					}
			   | SEMICOLON
			   ;

/* 表达式、赋值 */
expression: ident EQL andOr_expr
			   {
                 if ($1 == 0)
                       yyerror("Symbol does not exist");
                 else
                    {
                       if (table[$1].kind != variable)
                           yyerror("Symbol should be a variable");
                       else
                           gen(sto, lev - table[$1].level, table[$1].adr);
                    }
               }
		  | andOr_expr
		  ;

/* exit语句 */
exit_stat: EXITSYM
			{
				gen(jmp, 0 , 0);
			}
		 ;

/*  调用语句 */
callstm: CALLSYM ident
             {
                 if ($2 == 0)
                       yyerror("call Symbol does not exist");
                 else
                    {
                       if (table[$2].kind != procedure)
                           yyerror("Symbol should be a procedure");
                       else
                           gen (cal, lev - table[$2].level, table[$2].adr);    
                    }
              }
          ;

/* 条件语句 */
if_stat: IFSYM LPAREN expression RPAREN get_code_addr 
               {
               	gen(jpc, 0, 0);
               }
        	statement get_code_addr
               {
				gen(jmp, 0, 0);
               	code[$5].a = cx;
               }
			else_stat
			   {
				code[$8].a = cx;
			   }
       ;

/* else子句 用来解決归约归约冲突 */
else_stat: ELSESYM statement
		 | %prec LOWER_THAN_ELSE
		 ;

/* while循环语句 */
while_stat: WHILESYM get_code_addr LPAREN expression RPAREN get_code_addr 
               {
               	gen(jpc, 0 , 0);
               }
            statement 
               {
               	gen(jmp, 0, $2);
               	code[$6].a = cx;
               }
          ;

/* do-when循环语句 */
do_when_stat: DOSYM get_code_addr statement WHENSYM LPAREN expression RPAREN
					{
						gen(jpn, 0 , $2);
					}
          	 ;

/* repeat-until循环语句 */
repeat_until_stat: REPEATSYM get_code_addr statement UNTILSYM LPAREN expression RPAREN
					{
						gen(jpc, 0 , $2);
					}
          	 	 ;

/* continue语句 */
/* continue_stat: CONTINUESYM
				{
					// gen(jmp, 0, $2);
				}
			 ; */

/* break语句 */
/* break_stat: BREAKSYM
				{
					gen(jmp, 0, 2);
				}
		  ; */

/* for循环语句 */
for_stat: FORSYM LPAREN for_init SEMICOLON get_code_addr expression get_code_addr
			   {
               	gen(jpc, 0 , 0);
               }
			SEMICOLON get_code_addr
			   {
				gen(jmp, 0, 0);
			   }
			get_code_addr expression
			   {
				gen(jmp, 0, $5);
				code[$10].a = cx;
			   }
			RPAREN statement 
               {
               	gen(jmp, 0, $12);
               	code[$7].a = cx;
               }
        ;

/* for循环初始条件 */
for_init: ident EQL andOr_expr
			   {
                 if ($1 == 0)
                       yyerror("Symbol does not exist");
                 else
                    {
                       if (table[$1].kind != variable)
                           yyerror("Symbol should be a variable");
                       else
                           gen(sto, lev - table[$1].level, table[$1].adr);
                    }
               }
		| 
		;

/* 读语句 */
read_stat: READSYM readvar
         ;

/* 读语句变量 */
readvar: ident SEMICOLON
			{
			 gen(opr, 0, 16);
			 gen(sto, lev - table[$1].level, table[$1].adr);
			}
	   | ident %prec LOWER_THAN_SEMICOLON
			{
			 gen(opr, 0, 16);
			 gen(sto, lev - table[$1].level, table[$1].adr);
			 yyerror("You may have missed a ';'");
			} 
       ;

/* 写语句 */
write_stat: WRITESYM expression SEMICOLON
			{
			 gen(opr, 0, 14);
			 gen(opr, 0, 15);
			}
		  | WRITESYM expression %prec LOWER_THAN_SEMICOLON
			{
			 gen(opr, 0, 14);
			 gen(opr, 0, 15);
			 yyerror("You may have missed a ';'");
			}
          ;

/* 与或 优先级6 */
andOr_expr: bool_expr
		  | bool_expr AND bool_expr 
               {
               	gen(opr, 0, 21);
               }
          | bool_expr OR bool_expr 
               {
               	gen(opr, 0, 22);
               }
		  ;

/* 比较 优先级5 */
bool_expr: additive_expr
		 | ODDSYM additive_expr 
               {
               	gen(opr, 0, 6);
               }
         | additive_expr LSS additive_expr 
               {
               	gen(opr, 0, 10);
               }
         | additive_expr LEQ additive_expr 
               {
               	gen(opr, 0, 13);
               }
         | additive_expr GTR additive_expr 
               {
               	gen(opr, 0, 12);
               }
         | additive_expr GEQ additive_expr 
               {
               	gen(opr, 0, 11);
               }
         | additive_expr EQUALS additive_expr 
               {
               	gen(opr, 0, 8);
               }
         | additive_expr NEQ additive_expr 
               {
               	gen(opr, 0, 9);
               }
		 | additive_expr XOR additive_expr 
               {
               	gen(opr, 0, 18);
               }
         ;

/* 加减 优先级4 */
additive_expr: PLUS term
          | MINUS term
               {
               	gen(opr, 0, 1);
               }
          | term             
          | additive_expr PLUS term
               {
               	gen(opr, 0, 2);
               }
          | additive_expr MINUS term
               {
               	gen(opr, 0, 3);
               }
          ;

/* 乘除模 优先级3 */
term: notTerm
	| term TIMES notTerm
		{
		gen(opr, 0, 4);
		}
	| term SLASH notTerm
		{
		gen(opr, 0, 5);
		}        
	| term MOD notTerm
		{
		gen(opr, 0, 17);
		}    
	;

/* 取非 优先级2*/
notTerm: factor
	   | NOT factor
			{
			 gen(opr, 0, 7);
			}
	   ;

/* 自增自减 优先级1 */
factor: ident MOREPLUS
			{ if ($1 == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[$1].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
						if(table[$1].kind == constant)
							yyerror("Symbol should not be a constant");
						else{
							gen(lod, lev - table[$1].level, table[$1].adr);
							gen(opr, 0, 19);
							gen(sto, lev - table[$1].level, table[$1].adr);
							gen(lod, lev - table[$1].level, table[$1].adr);
						 }
						}
				}
			}    
	  | ident MOREMINUS
			{ if ($1 == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[$1].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
						if(table[$1].kind == constant)
							yyerror("Symbol should not be a constant");
						else{
							gen(lod, lev - table[$1].level, table[$1].adr);
							gen(opr, 0, 20);
							gen(sto, lev - table[$1].level, table[$1].adr);
							gen(lod, lev - table[$1].level, table[$1].adr);
						 }
						}
				}
			} 
	  | ident %prec LOWER_THAN_MORE
			{ if ($1 == 0)
					yyerror("Symbol does not exist");
				else
				{
					if (table[$1].kind == procedure)
						yyerror("Symbol should not be a procedure");
					else
						{
							if(table[$1].kind == constant)
							gen(lit, 0, table[$1].val);
						else
							gen(lod, lev - table[$1].level, table[$1].adr);
						}
				}
			} 
      | NUMBER 
			{
			 gen(lit, 0, $1);
			}
      | LPAREN expression RPAREN;

ident: IDENT 
               {
                $$ = position ($1); 
               }
          ;
get_table_addr:
               {
                $$ = tx;
               } 
          ;
get_code_addr:
               {
               	$$ = cx;
               }
          ;

inc_level:
               {
               	lev++;               
               	if (lev > levmax)		/* 嵌套层数过多 */
                     yyerror("Lev is too big");    
               }
          ;
inc_px:
              {
               px++;              
              }     
          ;
dec_level_px:
              {
              	lev--;
              	px--;              
              }    
          ;


////////////////////////////////////////////////////////
//程序部分
%%
void yyerror(char *s)
{
	err = err + 1;
    printf("%s in line %d\n", s, line);
	fprintf(foutput, "%s in line %d\n", s, line);
	/* return 0; */
}

/* 初始化 */
void init()
{
	tx = 0;
	cx = 0;
	px = 0;  
  lev = 0;   
  proctable[0] = 0;
  num = 0;
  err = 0;
}

/* 在符号表中加入一项 */
void enter(enum object k)
{
	tx = tx + 1;
	strcpy(table[tx].name, id);
	table[tx].kind = k;
	switch (k)
	{
		case constant:	/* 常量 */			
			table[tx].val = num; /* 登记常数的值 */
			break;
		case variable:	/* 变量 */
			table[tx].level = lev;	
			break;
		case procedure:	/* 过程 */
			table[tx].level = lev;
			break;
	}
}

/* 查找标识符在符号表中的位置 */
int position(char *s)
{
	int i;
	strcpy(table[0].name, s);
	i = tx;
	while(strcmp(table[i].name, s) != 0)
		i--;
	return i;
}

/* 为本层变量分配相对地址，从3开始分配 */
void setdx(int n)
{
	int i;
	for(i = 1; i <= n; i++)
		table[tx - i + 1].adr = n - i + 3;
}

/* 生成虚拟机代码 */
void gen(enum fct x, int y, int z)
{
	if (cx >= cxmax)
	{
		printf("Program is too long!\n");	/* 生成的虚拟机代码程序过长 */
		exit(1);
	}
	if ( z >= amax)
	{
		printf("Displacement address is too big!\n");	/* 地址偏移越界 */
		exit(1);
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	cx++;
}

/* 输出所有目标代码  */
void listall()
{
	int i;
	char name[][5]=
	{
		{"lit"},{"opr"},{"lod"},{"sto"},{"cal"},{"int"},{"jmp"},{"jpc"},{"jpn"},
	};
	/* if (listswitch)
	{ */
		for (i = 0; i < cx; i++)
		{
			printf("%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			fprintf(fcode,"%d %s %d %d\n", i, name[code[i].f], code[i].l, code[i].a);
			
		}
	/* } */
}

/* 输出符号表 */
void displaytable()
{
	int i;
/* if (tableswitch)		// 输出符号表
	{ */
	
	for (i = 1; i <= tx; i++)
		{
			switch (table[i].kind)
			{
				case constant:
					printf("    %d const %s ", i, table[i].name);
					printf("val=%d\n", table[i].val);
					fprintf(ftable, "    %d const %s ", i, table[i].name);
					fprintf(ftable, "val=%d\n", table[i].val);
					break;
				case variable:
					printf("    %d var   %s ", i, table[i].name);
					printf("lev=%d addr=%d\n", table[i].level, table[i].adr);
					fprintf(ftable, "    %d var   %s ", i, table[i].name);
					fprintf(ftable, "lev=%d addr=%d\n", table[i].level, table[i].adr);
					break;
				case procedure:
					printf("    %d proc  %s ", i, table[i].name);
					printf("lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
					fprintf(ftable,"    %d proc  %s ", i, table[i].name);
					fprintf(ftable,"lev=%d addr=%d size=%d\n", table[i].level, table[i].adr, table[i].size);
					break;
			}
		}
		printf("\n");
		fprintf(ftable, "\n");
	}

/* } */

/* 解释程序 */
void interpret()
{
	int p = 0; /* 指令指针 */
	int b = 1; /* 指令基址 */
	int t = 0; /* 栈顶指针 */
	struct instruction i;	/* 存放当前指令 */
	int s[stacksize];	/* 栈 */

	printf("Start smallC\n");
	/* fprintf(fresult,"Start smallC\n"); */
	s[0] = 0; /* s[0]不用 */
	s[1] = 0; /* 主程序的三个联系单元均置为0 */
	s[2] = 0;
	s[3] = 0;
	do {
	    i = code[p];	/* 读当前指令 */
		p = p + 1;
		switch (i.f)
		{
			case lit:	/* 将常量a的值取到栈顶 */
				t = t + 1;
				s[t] = i.a;				
				break;
			case opr:	/* 数学、逻辑运算 */
				switch (i.a)
				{
					case 0:  /* 函数调用结束后返回 */
						t = b - 1;
						p = s[t + 3];
						b = s[t + 2];
						break;
					case 1: /* 栈顶元素取反 */
						s[t] = - s[t];
						break;
					case 2: /* 次栈顶项加上栈顶项，退两个栈元素，相加值进栈 */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3:/* 次栈顶项减去栈顶项 */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4:/* 次栈顶项乘以栈顶项 */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5:/* 次栈顶项除以栈顶项 */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6:/* 栈顶元素的奇偶判断 */
						s[t] = s[t] % 2;
						break;
					case 7: /* 栈顶元素取非 */
						s[t] = !s[t];
						break;
					case 8:/* 次栈顶项与栈顶项是否相等 */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9:/* 次栈顶项与栈顶项是否不等 */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10:/* 次栈顶项是否小于栈顶项 */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11:/* 次栈顶项是否大于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12:/* 次栈顶项是否大于栈顶项 */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* 次栈顶项是否小于等于栈顶项 */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14:/* 栈顶值输出 */
						printf("%d", s[t]);
						fprintf(fresult, "%d", s[t]);
						t = t - 1;
						break;
					case 15:/* 输出换行符 */
						printf("\n");
						fprintf(fresult,"\n");
						break;
					case 16:/* 读入一个输入置于栈顶 */
						t = t + 1;
						printf("?");
						/* fprintf(finput, "?"); */
						fscanf(finput, "%d", &(s[t]));
						/* fprintf(finput, "%d\n", s[t]); */
						break;
					case 17:/* 次栈顶项模栈顶项 */
						t = t - 1;
						s[t] = s[t] % s[t + 1];
						break;
					case 18:/* 次栈顶项异或栈顶项 */
						t = t - 1;
						s[t] = s[t] ^ s[t + 1];
						break;
					case 19: /* 栈顶元素自增1 */
						s[t] = s[t] + 1;
						break;
					case 20: /* 栈顶元素自减1 */
						s[t] = s[t] - 1;
						break;
					case 21:/* 次栈顶项与栈顶项逻辑与 */
						t = t - 1;
						s[t] = (s[t] && s[t + 1]);
						break;
					case 22:/* 次栈顶项与栈顶项逻辑或 */
						t = t - 1;
						s[t] = (s[t] || s[t + 1]);
						break;
				}
				break;
			case lod:	/* 取相对当前过程的数据基地址为a的内存的值到栈顶 */
				t = t + 1;
				s[t] = s[base(i.l,s,b) + i.a];				
				break;
			case sto:	/* 栈顶的值存到相对当前过程的数据基地址为a的内存 */
				s[base(i.l, s, b) + i.a] = s[t];
				t = t - 1;
				break;
			case cal:	/* 调用子过程 */
				s[t + 1] = base(i.l, s, b);	/* 将父过程基地址入栈，即建立静态链 */
				s[t + 2] = b;	/* 将本过程基地址入栈，即建立动态链 */
				s[t + 3] = p;	/* 将当前指令指针入栈，即保存返回地址 */
				b = t + 1;	/* 改变基地址指针值为新过程的基地址 */
				p = i.a;	/* 跳转 */
				break;
			case ini:	/* 在数据栈中为被调用的过程开辟a个单元的数据区 */
				t = t + i.a;	
				break;
			case jmp:	/* 直接跳转 */
				p = i.a;
				break;
			case jpc:	/* 条件跳转 */
				if (s[t] == 0) 
					p = i.a;
				t = t - 1;
				break;
			case jpn:	/* 条件跳转 */
				if (s[t] != 0) 
					p = i.a;
				t = t - 1;
				break;
		}
	} while (p != 0);
	printf("End smallC\n");
	/* fprintf(fresult,"End smallC\n"); */
}

/* 通过过程基址求上l层过程的基址 */
int base(int l, int* s, int b)
{
	int b1;
	b1 = b;
	while (l > 0)
	{
		b1 = s[b1];
		l--;
	}
	return b1;
}

int main(void)
{
	// printf("Input pl/0 file?   ");
	// scanf("%s", fname);		/* 输入文件名 */

	// if ((fin = fopen(fname, "r")) == NULL)
	if ((fin = fopen("c_o_d_e.txt", "r")) == NULL)
	{
		printf("Can't open the input file!\n");
		exit(1);
	}	
	if ((foutput = fopen("foutput.txt", "w")) == NULL)
  	{
		printf("Can't open the output file!\n");
		exit(1);
	}
	if ((ftable = fopen("ftable.txt", "w")) == NULL)
	{
		printf("Can't open ftable.txt file!\n");
		exit(1);
	}
	if ((finput = fopen("finput.txt", "r")) == NULL)
	{
		printf("Can't open finput.txt file!\n");
		exit(1);
	}
	
	/* printf("List object codes?(Y/N)");	// 是否输出虚拟机代码
	scanf("%s", fname);
	listswitch = (fname[0]=='y' || fname[0]=='Y'); */
	/* listswitch = 'y'; */

	/* printf("List symbol table?(Y/N)");	// 是否输出符号表
	scanf("%s", fname);
	tableswitch = (fname[0]=='y' || fname[0]=='Y'); */
	/* tableswitch = 'y'; */
	
	redirectInput(fin);		
	init();
  	yyparse();
	if(err == 0)
	{
		printf("\n===Parsing success!===\n");
		fprintf(foutput, "\n===Parsing success!===\n");
		if ((fcode = fopen("fcode.txt", "w")) == NULL)
		{
			printf("Can't open fcode.txt file!\n");
			exit(1);
		}		

		if ((fresult = fopen("fresult.txt", "w")) == NULL)
		{
			printf("Can't open fresult.txt file!\n");
			exit(1);
		}
		
		listall();  /* 输出所有代码 */
		fclose(fcode);
		
		interpret();	/* 调用解释执行程序 */        	
		fclose(fresult);
	}
  	else
	{
		printf("%d errors in smallC program\n", err);
		fprintf(foutput, "%d errors in smallC program\n", err);
		
	}
	
	fclose(ftable);
  	fclose(foutput);
	fclose(finput);
	fclose(fin);
	return 0;
}



