/*
   Copyright (C) 2013 Vincenzo Lo Cicero

   Author: Vincenzo Lo Cicero.
   e-mail: vincenzo.locicero@live.it

   This file is part of ParseExprLib.

   ParseExprLib is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   ParseExprLib is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with ParseExprLib.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

// gcc -Wall -W -O3 -funroll-loops -std=c99 ParseExpr.c parser.c lexer.c -lm -o expr

#include "parser.h"

/*
expr  : expr1 {('+' | '-') expr1};
expr1 : expr2 {('*' | '/') expr2};
expr2 : ['-'] expr3;
expr3 : expr4 {'^' expr4}
expr4 : T_NUMBER
		| '(' expr ')'
*/

int shift(ParserData *pd)
{
	if ( pd->m_topOpr >= MAXSTACK )
	{
		printf("Error 6: stack operator overflow.\n");
		return 0;
	}
		
	pd->m_stackOpr[++(pd->m_topOpr)] = pd->m_Token.Type;
	//printf("SHIFT %s\n", pd->m_Token.str);
	
	GetNextToken(pd->m_strExpr, &(pd->m_Token));
	
	return 1;
}

int reduce(ParserData *pd)
{
	double right;
	
	if ( pd->m_topOpr < 1 )
	{
		printf("Error 7: missing operator or parenthesis.\n");
		return 0;
	}		
	
	if ( pd->m_top < 1 )
	{
		if ( pd->m_stackOpr[pd->m_topOpr] != T_UMINUS )
		{
			printf("Error 8: missing operand.\n");
			return 0;
		}
		else
		{
			if ( pd->m_top < 0 )
			{
				printf("Error 9: missing operand.\n");
				return 0;						
			}
		}
	}
					
	switch ( pd->m_stackOpr[pd->m_topOpr] )
	{
		case T_PLUS:			
			//printf("REDUCE +\n");
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);		
			right = pd->m_stack[(pd->m_top)--];
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);
			pd->m_stack[pd->m_top] = pd->m_stack[pd->m_top] + right;
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);
			break;
		case T_MINUS:
			//printf("REDUCE -\n");		
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);				
			right = pd->m_stack[(pd->m_top)--];
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);			
			pd->m_stack[pd->m_top] = pd->m_stack[pd->m_top] - right;		
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);
			break;
		case T_MULT:
			//printf("REDUCE *\n");		
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);						
			right = pd->m_stack[(pd->m_top)--];
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);						
			pd->m_stack[pd->m_top] = pd->m_stack[pd->m_top] * right;		
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);			
			break;
		case T_DIV:
			//printf("REDUCE /\n");		
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);								
			right = pd->m_stack[(pd->m_top)--];
			if ( right == 0 )
			{
				printf("Error 10: division by 0.\n");
				return 0;
			}
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);			
			pd->m_stack[pd->m_top] = pd->m_stack[pd->m_top] / right;		
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);
			break;
		case T_UMINUS:
			//printf("REDUCE unary minus\n");		
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);										
			pd->m_stack[pd->m_top] *= -1;
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);			
			break;
		case T_EXP:
			//printf("REDUCE ^\n");		
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);								
			right = pd->m_stack[(pd->m_top)--];
			//printf("POP %lf\n", pd->m_stack[pd->m_top]);
			pd->m_stack[pd->m_top] = pow(pd->m_stack[pd->m_top], right);
			//printf("PUSH %lf\n", pd->m_stack[pd->m_top]);			
			break;
		default:
			printf("Error 11: %s %d\n", pd->m_Token.str, pd->m_stackOpr[pd->m_topOpr]);
			return 0;
	}
	
	(pd->m_topOpr)--;
		
	return 1;
}

int Parse(const char *strExpr, double *dblRet)
{
	int ret = 1;	
	ParserData md;
					
	int8_t parseTable[9][9] =
	{
		/* stack   ----------- input ---------------- */
		/*         +   -   *   /   UM  ^   (   )   $  */
		/*         --  --  --  --  --  --  --  --  -- */
		/* +  */ { R,  R,  S,  S,  S,  S,  S,  R,  R },
		/* -  */ { R,  R,  S,  S,  S,  S,  S,  R,  R },
		/* *  */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* /  */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* UM */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* ^  */ { R,  R,  R,  R,  R,  S,  S,  R,  R },
		/* (  */ { S,  S,  S,  S,  S,  S,  S,  S,  E1},
		/* )  */ { R,  R,  R,  R,  R,  R,  E2, R,  R },
		/* $  */ { S,  S,  S,  S,  S,  S,  S,  E3, A }
	};		
	
	*dblRet = 0;

	strcpy(md.m_strExpr, strExpr);
	
	md.m_top = -1;
	md.m_value = 0;	
	md.m_topOpr = 0;
	md.m_stackOpr[0] = T_EOL;
	//printf("SHIFT $\n");

	initToken(&(md.m_Token));
	GetNextToken(md.m_strExpr, &(md.m_Token));
	if ( md.m_Token.Type == T_EOL )
	{
		return 1;
	}

	while ( 1 )
	{		
		switch ( md.m_Token.Type )
		{
			case T_UNKNOWN:
				printf("Error 0: invalid token: %s\n", md.m_Token.str);
				return 0;			
			case T_NUMBER:
				md.m_stack[++md.m_top] = md.m_Token.Value;
				//printf("PUSH %s\n", md.m_Token.str);
				GetNextToken(md.m_strExpr, &(md.m_Token));
				break;
			case T_UPLUS:
				GetNextToken(md.m_strExpr, &(md.m_Token));			
				break;
			case T_OPAREN:
				if ( !shift(&md) )
					return 0;
				break;
			case T_CPAREN:
				while ( md.m_stackOpr[md.m_topOpr] != T_OPAREN )
				{
					if ( !reduce(&md) )
						return 0;
				}
				--(md.m_topOpr);
				GetNextToken(md.m_strExpr, &(md.m_Token));
				//printf("REDUCE ()\n");
				break;
			default:
				switch ( parseTable[md.m_stackOpr[md.m_topOpr]][md.m_Token.Type] )
				{
					case S:
						if ( !shift(&md) )
							return 0;
						break;
					case R:
						if ( !reduce(&md) )
							return 0;
						break;
					case A:
						if ( md.m_top != 0 )
						{
							printf("Error 1: missing operator.\n");
							return 0;
						}
						if ( md.m_topOpr != 0 )
						{
							printf("Error 2: missing operand.\n");
							return 0;
						}						
						md.m_value = md.m_stack[(md.m_top)--];
						*dblRet = md.m_value;
						//printf("ACCEPT: %lf\n", *dblRet);
						return 1;
					case E1:
						printf("Error 3: missing right parenthesis\n");
						return 0;
					case E2:
						printf("Error 4: missing operator\n");
						return 0;					
					case E3:
						printf("Error 5: unbalanced parenthesis\n");
						return 0;						
				}
				break;
		}		
	}

	return ret;
}
