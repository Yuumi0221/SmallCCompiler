%x COMMENT
%{
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "y.tab.h"

int line=1;
void yyerror(char *);
int yywrap(void);
%}

%%
[ \t]	{;}
[\n]	{line++;}
"call"	{return CALLSYM;}
"const"	{return CONSTSYM;}
"if"	{return IFSYM;}
"else"	{return ELSESYM;}
"odd"	{return ODDSYM;}
"procedure"	{return PROCSYM;}
"read"	{return READSYM;}
"int"	{return INTSYM;}
"while"	{return WHILESYM;}
"for"	{return FORSYM;}
"do"	{return DOSYM;}
"when"	{return WHENSYM;}
"repeat"	{return REPEATSYM;}
"until"	{return UNTILSYM;}
"continue"	{return CONTINUESYM;}
"break"	{return BREAKSYM;}
"write"	{return WRITESYM;}
"exit"	{return EXITSYM;}
[A-Za-z]([A-Za-z]|[0-9])*	{yylval.ident=(char *)malloc(strlen(yytext)+1);
                                 strcpy(yylval.ident,yytext);
                                 return IDENT;
}
[0-9]+	{yylval.number=atoi(yytext);
	 return NUMBER;}
"<"	{return LSS;}
"<="	{return LEQ;}
">"	{return GTR;}
">="	{return GEQ;}
"+"	{return PLUS;}
"++"	{return MOREPLUS;}
"-"	{return MINUS;}
"--"	{return MOREMINUS;}
"*"	{return TIMES;}
"%"	{return MOD;}
"^"	{return XOR;}
"/"	{return	SLASH;}
"("	{return	LPAREN;}
")"	{return	RPAREN;}
"{"	{return LBRACE;}
"}"	{return RBRACE;}
"="	{return	EQL;}
"=="	{return EQUALS;}
","	{return COMMA;}
"."	{return PERIOD;}
"!" {return NOT;}
"!="	{return NEQ;}
";"	{return	SEMICOLON;}
"&&"	{return AND;}
"||"	{return OR;}

"//".*	{}
"/*"	{BEGIN COMMENT;}
<COMMENT>"*/"	{BEGIN INITIAL;}
<COMMENT>.	{}		/*跳过多行注释*/
.	{yyerror("Unknown character");}

%%

void redirectInput(FILE *input)
{
	yyin=input;
}

int yygetchar(void)
{
	int ret;
	ret = getc(yyin);
	printf("%c",ret);
	return ret;
}

int yywrap(void)
{
	return 1;
}