OperatorPrecedenceParsing
=========================

Example
-------

The *shift* operation is to push on operators stack, the operator just read from the input string.

The *reduce* operation consists in popping one operator from the operators stack and two (or one, if the operator is unary) operands from the values stack. It performs the operation and the result is pushed on values stack.

You want to evaluate the following expression:

    21 - 8 - 2 * 3 + (6 / 3) + 2^2^3

The initial situation is as follows($ indicates the end of input):
![opp01](Images/opp01.jpg)  

The first token read from the input string is the value 21; push it on values stack:
![opp02](Images/opp02.jpg)  

The next token is the "-" operator; performing a shift:
![opp03](Images/opp03.jpg)  

The next token is the value 8; push it on values stack:
![opp04](Images/opp04.jpg)  

The next token is the "-" operator, we compare it with the operator at the top of the stack of operators, "-". have equal precedence; perform a reduce operation because the "-" operator is left associative:
![opp05](Images/opp05.jpg)  

Shift "-" operator:
![opp06](Images/opp06.jpg)  

Push value 2 on values stack:
![opp07](Images/opp07.jpg)  

The next token, the "*" operator has higher precedence than what is located in top of the stack of operators, "-", and then goes shifted:
![opp08](Images/opp08.jpg)  

Value 3 is pushed into values stack:
![opp09](Images/opp09.jpg)  

The next token, the operator "+", has lower precedence than the one that is located in top of the stack of operators, "*", and then execute a reduce operation:
![opp10](Images/opp10.jpg)  

The comparison between the two operators, now, is reflected in an operation to reduce (equal precedence but the "-" operator, on top of the operators stack, is left associative):
![opp11](Images/opp11.jpg)  

The "+" operator is shifted. The open parenthesis is shifted:
![opp12](Images/opp12.jpg)  

Value 6 is pushed on values stack:
![opp13](Images/opp13.jpg)  

The "/" operator is shifted:
![opp14](Images/opp14.jpg)  

The next token in the input string, is the closing parenthesis. We proceed to a reduce operation repeatedly, until we meet, on top of the operators stack, the open parenthesis:
![opp15](Images/opp15.jpg)  

The two parenthesis are discarded:
![opp16](Images/opp16.jpg)  

The next step is a reduce operation (equal operators, left associativity):
![opp17](Images/opp17.jpg)  

The "+" operator is shifted:
![opp18](Images/opp18.jpg)  

Value 2 is pushed on values stack:
![opp19](Images/opp19.jpg)  

The next token, the operator "^" has prededenza greater than that in the top of the stack of operators, "+". It then is shifted:
![opp20](Images/opp20.jpg)  

Value 2 is pushed on values stack:
![opp21](Images/opp21.jpg)  

The next token, the operator "^" is equal to the top of the operators stack. The "^" operator is right-associative and then proceeds to an operation of shift:
![opp22](Images/opp22.jpg)  

Value 3 is pushed on values stack:
![opp23](Images/opp23.jpg)  

We reached the end of the input string. Repeatedly perform the task of reducing until the operators stack contains, at the top, the end-of-input symbol, $:
![opp24](Images/opp24.jpg)  

![opp25](Images/opp25.jpg)  

Now the value stack contains only one value, the result:
![opp26](Images/opp26.jpg)  
