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

import java.lang.String;
import java.lang.StringBuilder;

/*
expr  : expr1 {('+' | '-') expr1};
expr1 : expr2 {('*' | '/') expr2};
expr2 : ['-'] expr3;
expr3 : expr4 {'^' expr4}
expr4 : T_NUMBER | '(' expr ')'
*/

public class CParser
{
	public CParser()
	{
		m_Lexer = new CLexer();	
		m_MAXSTACK = 255;
		m_top = -1;
		m_topOpr = -1;
		m_value = 0;
		m_stack = new double[m_MAXSTACK];
		m_stackOpr = new CLexer.TokenTypeEnum[m_MAXSTACK];
	}
	
	private boolean shift()
	{
		if ( m_topOpr >= m_MAXSTACK )
		{
			System.out.println("Error 6: stack operator overflow.");
			return false;
		}
		
		m_stackOpr[++m_topOpr] = m_Lexer.m_currToken.Type;
	
		m_Lexer.GetNextToken();
	
		return true;
	}
	
	private boolean reduce()
	{
		double right;
	
		if ( m_topOpr < 1 )
		{
			System.out.println("Error 7: missing operator or parenthesis.");
			return false;
		}		
	
		if ( m_top < 1 )
		{
			if ( m_stackOpr[m_topOpr] != CLexer.TokenTypeEnum.T_UMINUS )
			{
				System.out.println("Error 8: missing operand.");
				return false;
			}
			else
			{
				if ( m_top < 0 )
				{
					System.out.println("Error 9: missing operand.");
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
					System.out.println("Error 10: division by 0.");
					return false;
				}
				m_stack[m_top] /= right;
				break;
			case T_UMINUS:
				m_stack[m_top] *= -1;
				break;
			case T_EXP:
				right = m_stack[m_top--];
				m_stack[m_top] = Math.pow(m_stack[m_top], right);
				break;
			default:
				System.out.println("Error 11: invalid syntax");
				return false;
		}
	
		m_topOpr--;
		
		return true;
	}		

	public boolean Parse(String strExpr)
	{
		boolean ret = true;
		
		final int S  = 0;   /* shift */
		final int R  = 1;   /* reduce */
		final int A  = 2;   /* accept */
		final int E1 = 3;   /* error: missing right parenthesis */
		final int E2 = 4;   /* error: missing operator */
		final int E3 = 5;   /* error: unbalanced parenthesis */
		
		int[][] parseTable =
		{
			/* stack   -------- input ----------- */
			/*         +   -   *   /   UM  ^   $  */
			/*         --  --  --  --  --  --  -- */
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

		m_strExpr = new String(strExpr);
		m_top = -1;
		m_value = 0;		

		m_Lexer.SetExpr(strExpr);
				
		m_topOpr = 0;
		m_stackOpr[0] = CLexer.TokenTypeEnum.T_EOL;
		
		m_Lexer.GetNextToken();
		if ( m_Lexer.m_currToken.Type == CLexer.TokenTypeEnum.T_EOL )
		{
			return true;
		}

		while ( true )
		{		
			switch ( m_Lexer.m_currToken.Type )
			{
				case T_UNKNOWN:
					System.out.print("Error 0: invalid token: ");
					System.out.println(m_Lexer.m_currToken.str);
					return false;			
				case T_NUMBER:
					m_stack[++m_top] = m_Lexer.m_currToken.Value;
					m_Lexer.GetNextToken();
					break;
				case T_UPLUS:
					m_Lexer.GetNextToken();				
					break;
				case T_OPAREN:
					if ( !shift() )
						return false;
					break;
				case T_CPAREN:
					while ( m_stackOpr[m_topOpr] != CLexer.TokenTypeEnum.T_OPAREN )
					{
						if ( !reduce() )
							return false;
					}
					--m_topOpr;
					m_Lexer.GetNextToken();					
					break;
				default:
					switch ( parseTable[m_stackOpr[m_topOpr].ordinal()][m_Lexer.m_currToken.Type.ordinal()] )
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
								System.out.println("Error 1: missing operator.\n");
								return false;
							}
							if ( m_topOpr != 0 )
							{
								System.out.println("Error 2: missing operand.\n");
								return false;
							}						
							m_value = m_stack[m_top--];
							return true;
						case E1:
							System.out.println("Error 3: missing right parenthesis");
							return false;
						case E2:
							System.out.println("Error 4: missing operator");
							return false;					
						case E3:
							System.out.println("Error 5: unbalanced parenthesis");
							return false;
					}
					break;
			}		
		}
	}
	
	public double GetValue()
	{
		return m_value;
	}
	
	private CLexer m_Lexer;
	private String m_strExpr;
	private int m_MAXSTACK;
	private int m_top;              
	private double[] m_stack;
	private int m_topOpr;
	private CLexer.TokenTypeEnum[] m_stackOpr;
	private double m_value;
}

