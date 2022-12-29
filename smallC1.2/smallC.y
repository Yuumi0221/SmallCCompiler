////////////////////////////////////////////////////////
//��������
%{
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<memory.h>
#include<string.h>

#define bool int
#define true 1
#define false 0

#define txmax 100     /* ���ű����� */
#define al 10         /* ��ʶ������󳤶� */
#define amax 2048     /* ��ַ�Ͻ�*/
#define levmax 3      /* ����������Ƕ����������*/
#define cxmax 200     /* ��������������� */
#define stacksize 500 /* ����ʱ����ջԪ�����Ϊ500�� */

/* ���ű��е����� */
enum object {
    constant, 
    variable, 
    procedure,
};

/* ���ű�ṹ */
struct tablestruct
{
   char name[al];      /* ���� */
   enum object kind;   /* ���ͣ�const��var��procedure */
   int val;            /* ��ֵ����constʹ�� */
	 int level;          /* �����㣬��const��ʹ�� */ 
	 int adr;            /* ��ַ����const��ʹ�� */
	 int size;           /* ��Ҫ������������ռ�, ��procedureʹ�� */
};
struct tablestruct table[txmax]; /* ���ű� */

/* ���������ָ�� */
enum fct {
    lit,     opr,     lod, 
    sto,     cal,     ini, 
    jmp,     jpc,     jpn,
};

/* ���������ṹ */
struct instruction
{
	enum fct f;   /* ���������ָ�� */
	int l;        /* ���ò���������Ĳ�β� */
	int a;        /* ����f�Ĳ�ͬ����ͬ */
};
struct instruction code[cxmax]; /* ����������������� */

int tx;         /* ���ű�ǰβָ�� */
int cx;         /* ���������ָ��, ȡֵ��Χ[0, cxmax-1] */
int px;         /* Ƕ�׹���������proctable��ָ�� */
int lev;        /* ��μ�¼ */
int proctable[3];   /* Ƕ�׹������������Ƕ������ */
char id[al];
int num;
bool listswitch;   /* ��ʾ������������ */
bool tableswitch;  /* ��ʾ���ű���� */

FILE* fin;      /* ����Դ�ļ� */
FILE* ftable;	  /* ������ű� */
FILE* fcode;    /* ������������ */
FILE* foutput;  /* �������ʾ�⣨���д� */
FILE* fresult;  /* ���ִ�н�� */
FILE* finput;	/* �������� */
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
//�������岿��
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
%nonassoc ELSESYM  // ��������ȼ���

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
//���򲿷�
%%
/* ���� */
program: block;

/*  �ֳ��� */
block:         {               
                table[tx].adr = cx;				  /* ��¼��ǰ�����Ŀ�ʼλ�� */  
                $<number>$ = cx;
               	gen(jmp, 0 , 0);            /* ������תָ���תλ��δ֪��ʱ��0 */
               }
               get_table_addr               /* ��¼�����ʶ���ĳ�ʼλ�� */
               LBRACE constdecl vardecl procdecls 
               {
               	code[$<number>1].a = cx;            /* ��ǰ�����ɵ���ת������תλ�øĳɵ�ǰλ�� */
               	table[$2].adr = cx;         /* ��¼��ǰ���̴����ַ */
               	table[$2].size = $5 + 3;    /* ��¼��ǰ���̷������ݴ�С */
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

/*  �������� */
constdecl: CONSTSYM constlist SEMICOLON 
         | CONSTSYM constlist %prec LOWER_THAN_SEMICOLON
		 	{
				yyerror("You may have missed a ';'");
			}
		 |
         ;

/* ���������б� */
constlist: constdef 
          | constlist COMMA constdef 
          ;

/* �������� */
constdef: IDENT EQL NUMBER
               {
               	strcpy(id,$1);   
               	num = $3;
               	enter(constant);
               }
        ;

/*  �������� */
vardecl: INTSYM varlist SEMICOLON
            {
                $$ = $2;         /* ���ݱ��������ĸ��� */
                setdx($2);       /* ���������Ե�ַ */
            }
	   | INTSYM varlist %prec LOWER_THAN_SEMICOLON
               {
                $$ = $2;         /* ���ݱ��������ĸ��� */
                setdx($2);       /* ���������Ե�ַ */
				yyerror("You may have missed a ';'");
               }
       |
          	{
          		$$ = 0;          /* û�б������� */
          	}
       ;
          		
/* ���������б� */
varlist: vardef 
               {
               	$$ = $1;
               }
       | varlist COMMA vardef 
               {
               	$$ = $1 + $3;  /* ���������ĸ������ */
               }
       ;

/* �������� */
vardef: IDENT
            {
              	strcpy(id, $1); 
              	enter(variable); 
              	$$ = 1;
            }
      ;

/*  �������� */
procdecls: procdecls procdecl procbody 
          |  
          ;

/*  ��������ͷ�� */
procdecl: inc_px PROCSYM IDENT SEMICOLON
               {                 
                 strcpy(id, $3);
	               enter(procedure); 
	               proctable[px] = tx;                
               }
          ;

/*  ������������ */
procbody: inc_level block dec_level_px SEMICOLON
        ;

/* �л�û����� */
statement_decl: statement_list
			  | 
			  ;

/* һ���������� */
statement_list: statement
			  | statement_list statement
          	  ;

/*  ��� */
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

/* ������� */
compound_stat: LBRACE statement_decl RBRACE 
           	 ;

expression_stat: expression SEMICOLON
			   | expression %prec LOWER_THAN_SEMICOLON
			   		{
						yyerror("You may have missed a ';'");
					}
			   | SEMICOLON
			   ;

/* ���ʽ����ֵ */
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

/* exit��� */
exit_stat: EXITSYM
			{
				gen(jmp, 0 , 0);
			}
		 ;

/*  ������� */
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

/* ������� */
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

/* else�Ӿ� ������Q��Լ��Լ��ͻ */
else_stat: ELSESYM statement
		 | %prec LOWER_THAN_ELSE
		 ;

/* whileѭ����� */
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

/* do-whenѭ����� */
do_when_stat: DOSYM get_code_addr statement WHENSYM LPAREN expression RPAREN
					{
						gen(jpn, 0 , $2);
					}
          	 ;

/* repeat-untilѭ����� */
repeat_until_stat: REPEATSYM get_code_addr statement UNTILSYM LPAREN expression RPAREN
					{
						gen(jpc, 0 , $2);
					}
          	 	 ;

/* continue��� */
/* continue_stat: CONTINUESYM
				{
					// gen(jmp, 0, $2);
				}
			 ; */

/* break��� */
/* break_stat: BREAKSYM
				{
					gen(jmp, 0, 2);
				}
		  ; */

/* forѭ����� */
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

/* forѭ����ʼ���� */
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

/* ����� */
read_stat: READSYM readvar
         ;

/* �������� */
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

/* д��� */
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

/* ��� ���ȼ�6 */
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

/* �Ƚ� ���ȼ�5 */
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

/* �Ӽ� ���ȼ�4 */
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

/* �˳�ģ ���ȼ�3 */
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

/* ȡ�� ���ȼ�2*/
notTerm: factor
	   | NOT factor
			{
			 gen(opr, 0, 7);
			}
	   ;

/* �����Լ� ���ȼ�1 */
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
               	if (lev > levmax)		/* Ƕ�ײ������� */
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
//���򲿷�
%%
void yyerror(char *s)
{
	err = err + 1;
    printf("%s in line %d\n", s, line);
	fprintf(foutput, "%s in line %d\n", s, line);
	/* return 0; */
}

/* ��ʼ�� */
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

/* �ڷ��ű��м���һ�� */
void enter(enum object k)
{
	tx = tx + 1;
	strcpy(table[tx].name, id);
	table[tx].kind = k;
	switch (k)
	{
		case constant:	/* ���� */			
			table[tx].val = num; /* �Ǽǳ�����ֵ */
			break;
		case variable:	/* ���� */
			table[tx].level = lev;	
			break;
		case procedure:	/* ���� */
			table[tx].level = lev;
			break;
	}
}

/* ���ұ�ʶ���ڷ��ű��е�λ�� */
int position(char *s)
{
	int i;
	strcpy(table[0].name, s);
	i = tx;
	while(strcmp(table[i].name, s) != 0)
		i--;
	return i;
}

/* Ϊ�������������Ե�ַ����3��ʼ���� */
void setdx(int n)
{
	int i;
	for(i = 1; i <= n; i++)
		table[tx - i + 1].adr = n - i + 3;
}

/* ������������� */
void gen(enum fct x, int y, int z)
{
	if (cx >= cxmax)
	{
		printf("Program is too long!\n");	/* ���ɵ���������������� */
		exit(1);
	}
	if ( z >= amax)
	{
		printf("Displacement address is too big!\n");	/* ��ַƫ��Խ�� */
		exit(1);
	}
	code[cx].f = x;
	code[cx].l = y;
	code[cx].a = z;
	cx++;
}

/* �������Ŀ�����  */
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

/* ������ű� */
void displaytable()
{
	int i;
/* if (tableswitch)		// ������ű�
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

/* ���ͳ��� */
void interpret()
{
	int p = 0; /* ָ��ָ�� */
	int b = 1; /* ָ���ַ */
	int t = 0; /* ջ��ָ�� */
	struct instruction i;	/* ��ŵ�ǰָ�� */
	int s[stacksize];	/* ջ */

	printf("Start smallC\n");
	/* fprintf(fresult,"Start smallC\n"); */
	s[0] = 0; /* s[0]���� */
	s[1] = 0; /* �������������ϵ��Ԫ����Ϊ0 */
	s[2] = 0;
	s[3] = 0;
	do {
	    i = code[p];	/* ����ǰָ�� */
		p = p + 1;
		switch (i.f)
		{
			case lit:	/* ������a��ֵȡ��ջ�� */
				t = t + 1;
				s[t] = i.a;				
				break;
			case opr:	/* ��ѧ���߼����� */
				switch (i.a)
				{
					case 0:  /* �������ý����󷵻� */
						t = b - 1;
						p = s[t + 3];
						b = s[t + 2];
						break;
					case 1: /* ջ��Ԫ��ȡ�� */
						s[t] = - s[t];
						break;
					case 2: /* ��ջ�������ջ���������ջԪ�أ����ֵ��ջ */
						t = t - 1;
						s[t] = s[t] + s[t + 1];
						break;
					case 3:/* ��ջ�����ȥջ���� */
						t = t - 1;
						s[t] = s[t] - s[t + 1];
						break;
					case 4:/* ��ջ�������ջ���� */
						t = t - 1;
						s[t] = s[t] * s[t + 1];
						break;
					case 5:/* ��ջ�������ջ���� */
						t = t - 1;
						s[t] = s[t] / s[t + 1];
						break;
					case 6:/* ջ��Ԫ�ص���ż�ж� */
						s[t] = s[t] % 2;
						break;
					case 7: /* ջ��Ԫ��ȡ�� */
						s[t] = !s[t];
						break;
					case 8:/* ��ջ������ջ�����Ƿ���� */
						t = t - 1;
						s[t] = (s[t] == s[t + 1]);
						break;
					case 9:/* ��ջ������ջ�����Ƿ񲻵� */
						t = t - 1;
						s[t] = (s[t] != s[t + 1]);
						break;
					case 10:/* ��ջ�����Ƿ�С��ջ���� */
						t = t - 1;
						s[t] = (s[t] < s[t + 1]);
						break;
					case 11:/* ��ջ�����Ƿ���ڵ���ջ���� */
						t = t - 1;
						s[t] = (s[t] >= s[t + 1]);
						break;
					case 12:/* ��ջ�����Ƿ����ջ���� */
						t = t - 1;
						s[t] = (s[t] > s[t + 1]);
						break;
					case 13: /* ��ջ�����Ƿ�С�ڵ���ջ���� */
						t = t - 1;
						s[t] = (s[t] <= s[t + 1]);
						break;
					case 14:/* ջ��ֵ��� */
						printf("%d", s[t]);
						fprintf(fresult, "%d", s[t]);
						t = t - 1;
						break;
					case 15:/* ������з� */
						printf("\n");
						fprintf(fresult,"\n");
						break;
					case 16:/* ����һ����������ջ�� */
						t = t + 1;
						printf("?");
						/* fprintf(finput, "?"); */
						fscanf(finput, "%d", &(s[t]));
						/* fprintf(finput, "%d\n", s[t]); */
						break;
					case 17:/* ��ջ����ģջ���� */
						t = t - 1;
						s[t] = s[t] % s[t + 1];
						break;
					case 18:/* ��ջ�������ջ���� */
						t = t - 1;
						s[t] = s[t] ^ s[t + 1];
						break;
					case 19: /* ջ��Ԫ������1 */
						s[t] = s[t] + 1;
						break;
					case 20: /* ջ��Ԫ���Լ�1 */
						s[t] = s[t] - 1;
						break;
					case 21:/* ��ջ������ջ�����߼��� */
						t = t - 1;
						s[t] = (s[t] && s[t + 1]);
						break;
					case 22:/* ��ջ������ջ�����߼��� */
						t = t - 1;
						s[t] = (s[t] || s[t + 1]);
						break;
				}
				break;
			case lod:	/* ȡ��Ե�ǰ���̵����ݻ���ַΪa���ڴ��ֵ��ջ�� */
				t = t + 1;
				s[t] = s[base(i.l,s,b) + i.a];				
				break;
			case sto:	/* ջ����ֵ�浽��Ե�ǰ���̵����ݻ���ַΪa���ڴ� */
				s[base(i.l, s, b) + i.a] = s[t];
				t = t - 1;
				break;
			case cal:	/* �����ӹ��� */
				s[t + 1] = base(i.l, s, b);	/* �������̻���ַ��ջ����������̬�� */
				s[t + 2] = b;	/* �������̻���ַ��ջ����������̬�� */
				s[t + 3] = p;	/* ����ǰָ��ָ����ջ�������淵�ص�ַ */
				b = t + 1;	/* �ı����ַָ��ֵΪ�¹��̵Ļ���ַ */
				p = i.a;	/* ��ת */
				break;
			case ini:	/* ������ջ��Ϊ�����õĹ��̿���a����Ԫ�������� */
				t = t + i.a;	
				break;
			case jmp:	/* ֱ����ת */
				p = i.a;
				break;
			case jpc:	/* ������ת */
				if (s[t] == 0) 
					p = i.a;
				t = t - 1;
				break;
			case jpn:	/* ������ת */
				if (s[t] != 0) 
					p = i.a;
				t = t - 1;
				break;
		}
	} while (p != 0);
	printf("End smallC\n");
	/* fprintf(fresult,"End smallC\n"); */
}

/* ͨ�����̻�ַ����l����̵Ļ�ַ */
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
	// scanf("%s", fname);		/* �����ļ��� */

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
	
	/* printf("List object codes?(Y/N)");	// �Ƿ�������������
	scanf("%s", fname);
	listswitch = (fname[0]=='y' || fname[0]=='Y'); */
	/* listswitch = 'y'; */

	/* printf("List symbol table?(Y/N)");	// �Ƿ�������ű�
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
		
		listall();  /* ������д��� */
		fclose(fcode);
		
		interpret();	/* ���ý���ִ�г��� */        	
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



