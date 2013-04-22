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


using System;
//using System.Collections.Generic;
//using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;

using ExprCS;

/*
expr  : expr1 {('+' | '-') expr1};
expr1 : expr2 {('*' | '/') expr2};
expr2 : ['-'] expr3;
expr3 : expr4 {'^' expr4}
expr4 : T_NUMBER
		| '(' expr ')'
*/

namespace ExprCS
{
    public class CParser
    {
        public CParser()
        {
            m_top = -1;
            m_top = -1;            
            m_value = 0;
            m_stack = new double[MAXSTACK];
            m_stackOpr = new int[MAXSTACK];
            m_Lexer = new CLexer();
        }
        
		bool shift()
		{
			if ( m_topOpr >= MAXSTACK )
			{
				Console.WriteLine("Error 6: stack operator overflow.");
				return false;
			}
		
			m_stackOpr[++m_topOpr] = (int)m_Lexer.m_currToken.Type;
	
			m_Lexer.GetNextToken();
	
			return true;
		}

		bool reduce()
		{
			double right;
	
			if ( m_topOpr < 1 )
			{
				Console.WriteLine("Error 7: missing operator or parenthesis.");
				return false;
			}		
	
			if ( m_top < 1 )
			{
				if ( m_stackOpr[m_topOpr] != (int)TokenType.T_UMINUS )
				{
					Console.WriteLine("Error 8: missing operand.");
					return false;
				}
				else
				{
					if ( m_top < 0 )
					{
						Console.WriteLine("Error 9: missing operand.");
						return false;
					}
				}
			}
					
			switch ( m_stackOpr[m_topOpr] )
			{
				case (int)TokenType.T_PLUS:			
					right = m_stack[m_top--];
					m_stack[m_top] += right;
					break;
				case (int)TokenType.T_MINUS:
					right = m_stack[m_top--];
					m_stack[m_top] -= right;		
					break;
				case (int)TokenType.T_MULT:
					right = m_stack[m_top--];
					m_stack[m_top] *= right;
					break;
				case (int)TokenType.T_DIV:
					right = m_stack[m_top--];
					if ( right == 0 )
					{
						Console.WriteLine("Error 10: division by 0");
						return false;
					}
					m_stack[m_top] /= right;
					break;
				case (int)TokenType.T_UMINUS:
					m_stack[m_top] *= -1;
					break;
				case (int)TokenType.T_EXP:
					right = m_stack[m_top--];
					m_stack[m_top] = Math.Pow(m_stack[m_top], right);
					break;
				default:
					Console.WriteLine("Error 11: {0} {1}", m_Lexer.m_currToken.str, m_stackOpr[m_topOpr]);
					return false;
			}
	
			m_topOpr--;
		
			return true;
		}
        
        public bool Parse(string strExpr)
        {
            //bool ret = true;
			const int S  = 0; /* shift */
			const int R  = 1; /* reduce */
			const int A  = 2; /* accept */  
			const int E1 = 3; /* error: missing right parenthesis */
			const int E2 = 4; /* error: missing operator */
			const int E3 = 5; /* error: unbalanced parenthesis */    			          
            
			int[,] parseTable = new int[,]
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
            
            //m_strExpr = strExpr;
            m_top = -1;
            m_value = 0;
            
			m_topOpr = 0;
			m_stackOpr[0] = (int)TokenType.T_EOL;
            
            m_Lexer.SetExpr(strExpr);

            m_Lexer.GetNextToken();
            
			if ( m_Lexer.m_currToken.Type == TokenType.T_EOL )
			{
				return true;
			}

			while ( true )
			{		
				switch ( m_Lexer.m_currToken.Type )
				{
					case TokenType.T_UNKNOWN:
						Console.WriteLine("Error 0: invalid token: {0}", m_Lexer.m_currToken.str);
						return false;			
					case TokenType.T_NUMBER:
						m_stack[++m_top] = m_Lexer.m_currToken.Value;
						m_Lexer.GetNextToken();
						break;
					case TokenType.T_UPLUS:
						m_Lexer.GetNextToken();
						break;
					case TokenType.T_OPAREN:
						if ( !shift() )
							return false;
						break;
					case TokenType.T_CPAREN:
						while ( m_stackOpr[m_topOpr] != (int)TokenType.T_OPAREN )
						{
							if ( !reduce() )
								return false;
						}
						--m_topOpr;
						m_Lexer.GetNextToken();
						break;
					default:
						switch ( parseTable[m_stackOpr[m_topOpr], (int)m_Lexer.m_currToken.Type] )
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
									Console.WriteLine("Error 1: missing operator.");
									return false;
								}
								if ( m_topOpr != 0 )
								{
									Console.WriteLine("Error 2: missing operand.");
									return false;
								}						
								m_value = m_stack[m_top--];
								return true;
							case E1:
								Console.WriteLine("Error 3: missing right parenthesis");
								return false;
							case E2:
								Console.WriteLine("Error 4: missing operator");
								return false;					
							case E3:
								Console.WriteLine("Error 5: unbalanced parenthesis");
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
        //private string m_strExpr;
        private int m_top;
        private double[] m_stack;
		private int m_topOpr;
		private int[] m_stackOpr;
        private double m_value;
		private const int MAXSTACK = 1024;
    }
}

