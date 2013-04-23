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

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

#include "parser.h"

// g++ -Wall -W -O3 -std=c++11 ParseExpr.cpp parser.cpp lexer.cpp -lm -o expr

/*
expr  : expr1 {('+' | '-') expr1};
expr1 : expr2 {('*' | '/') expr2};
expr2 : ['-'] expr3;
expr3 : expr4 {'^' expr4};
expr4 : T_NUMBER
		| '(' expr ')';
*/

bool CParser::shift()
{
	if ( m_topOpr >= MAXSTACK )
	{
		cout << "Error 4: stack operator overflow.\n";
		return false;
	}
		
	m_stackOpr[++m_topOpr] = m_Lexer.m_currToken.Type;
	
	m_Lexer.GetNextToken();
	
	return true;
}

bool CParser::reduce()
{
	double right;
		
	if ( m_topOpr < 1 && m_stackOpr[m_topOpr] != T_OPAREN && m_stackOpr[m_topOpr] != T_CPAREN )
	{
		cout << "Error 5: missing operator or parenthesis.\n";
		return false;
	}		
	
	if ( m_top < 1 )
	{
		if ( m_stackOpr[m_topOpr] != T_UMINUS )
		{
			cout << "Error 6: missing operand.\n";
			return false;
		}
		else
		{
			if ( m_top < 0 )
			{
				cout << "Error 7: missing operand.\n";
				return false;
			}
		}
	}
						
	switch ( m_stackOpr[m_topOpr] )
	{
		case T_PLUS:	
			right = m_stack[m_top--];
			m_stack[m_top] += right;
			break;
		case T_MINUS:
			right = m_stack[m_top--];
			m_stack[m_top] -= right;		
			break;
		case T_MULT:
			right = m_stack[m_top--];
			m_stack[m_top] *= right;
			break;
		case T_DIV:
			right = m_stack[m_top--];
			if ( right == 0 )
			{
				cout << "Error 8: division by 0.\n";
				return false;
			}
			m_stack[m_top] /= right;
			break;
		case T_UMINUS:
			m_stack[m_top] *= -1;
			break;
		case T_EXP:
			right = m_stack[m_top--];
			m_stack[m_top] = pow(m_stack[m_top], right);
			break;
		case T_OPAREN:
			if ( m_Lexer.m_currToken.Type == T_CPAREN )
				m_Lexer.GetNextToken();
			break;
		case T_CPAREN:
			break;			
		default:
			cout << "Error 9: " << m_Lexer.m_currToken.str << " " << m_stackOpr[m_topOpr] << endl;
			return false;
	}
	
	m_topOpr--;
		
	return true;
}


bool CParser::Parse(const char *strExpr)
{
	int8_t parseTable[9][9] =
	{
		/* stack   -------- input ----------- */
		/*         +   -   *   /   UM  ^   (   )   $  */
		/*         --  --  --  --  --  --  --  --  -- */
		/* +  */ { R,  R,  S,  S,  S,  S,  S,  R,  R },
		/* -  */ { R,  R,  S,  S,  S,  S,  S,  R,  R },
		/* *  */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* /  */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* UM */ { R,  R,  R,  R,  S,  S,  S,  R,  R },
		/* ^  */ { R,  R,  R,  R,  R,  S,  S,  R,  R },
		/* (  */ { S,  S,  S,  S,  S,  S,  S,  R,  E1},
		/* )  */ { R,  R,  R,  R,  R,  R,  E2, R,  R },
		/* $  */ { S,  S,  S,  S,  S,  S,  S,  E3, A }		
	};
	
	//strcpy(m_strExpr, strExpr);

	m_Lexer.SetExpr(strExpr);
	m_top = -1;
	m_value = 0;
	
	m_topOpr = 0;
	m_stackOpr[0] = T_EOL;

	m_Lexer.GetNextToken();
	
	if ( m_Lexer.m_currToken.Type == T_EOL )
	{
		return true;
	}

	while ( true )
	{		
		switch ( m_Lexer.m_currToken.Type )
		{
			case T_UNKNOWN:
				cout << "Error 0: invalid token: " << m_Lexer.m_currToken.str << endl;
				return false;			
			case T_NUMBER:
				m_stack[++m_top] = m_Lexer.m_currToken.Value;
				m_Lexer.GetNextToken();
				break;
			case T_UPLUS:
				m_Lexer.GetNextToken();
				break;
			default:
				switch ( parseTable[m_stackOpr[m_topOpr]][m_Lexer.m_currToken.Type] )
				{
					case S:
						if ( !shift() )
							return false;
						break;
					case R:
						if ( !reduce() )
							return false;
						break;
					case A:
						if ( m_top != 0 )
						{
							cout << "Error 10: missing operator.\n";
							return false;
						}
						if ( m_topOpr != 0 )
						{
							cout << "Error 11: missing operand.\n";
							return false;
						}						
						m_value = m_stack[m_top--];
						return true;
					case E1:
						cout << "Error 1: missing right parenthesis\n";
						return false;
					case E2:
						cout << "Error 2: missing operator\n";
						return false;					
					case E3:
						cout << "Error 3: unbalanced parenthesis\n";
						return false;
				}
				break;
		}		
	}

	//return ret;	
}
