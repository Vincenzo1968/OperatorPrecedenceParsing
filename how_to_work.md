OperatorPrecedenceParsing
=========================

Example
-------

The *shift* operation is to push on operators stack, the operator just read from the input string.

The *reduce* operation consists in popping one operator from the operators stack and two (or one, if the operator is unary) operands from the values stack. It performs the operation and the result is pushed on values stack.

You want to evaluate the following expression:

    21 - 8 - 2 * 3 + (6 / 3) + 2^2^3

<table border="0">
    <tr><td>The initial situation is as follows($ indicates the end of input):</td></tr>
    <tr><td><img src="Images/opp01.jpg"></td></tr>
    <tr><td>The first token read from the input string is the value 21; push it on values stack:</td></tr>
    <tr><td><img src="Images/opp02.jpg"></td></tr>
    <tr><td>The next token is the "-" operator; performing a shift:</td></tr>
    <tr><td><img src="Images/opp03.jpg"></td></tr>
    <tr><td>The next token is the value 8; push it on values stack:</td></tr>
    <tr><td><img src="Images/opp04.jpg"></td></tr>
    <tr><td>The next token is the "-" operator, we compare it with the operator at the top of the stack of operators, "-". have equal precedence; perform a reduce operation because the "-" operator is left associative:</td></tr>
    <tr><td><img src="Images/opp05.jpg"></td></tr>
    <tr><td>Shift "-" operator:</td></tr>
    <tr><td><img src="Images/opp06.jpg"></td></tr>
    <tr><td>Push value 2 on values stack:</td></tr>
    <tr><td><img src="Images/opp07.jpg"></td></tr>
    <tr><td>The next token, the "*" operator has higher precedence than what is located in top of the stack of operators, "-", and then goes shifted:</td></tr>
    <tr><td><img src="Images/opp08.jpg"></td></tr>
    <tr><td>Value 3 is pushed into values stack:</td></tr>
    <tr><td><img src="Images/opp09.jpg"></td></tr>
    <tr><td>The next token, the operator "+", has lower precedence than the one that is located in top of the stack of operators, "*", and then execute a reduce operation:</td></tr>
    <tr><td><img src="Images/opp10.jpg"></td></tr>
    <tr><td>The comparison between the two operators, now, is reflected in an operation to reduce (equal precedence but the "-" operator, on top of the operators stack, is left associative):</td></tr>
    <tr><td><img src="Images/opp11.jpg"></td></tr>
    <tr><td>The "+" operator is shifted. The open parenthesis is shifted:</td></tr>
    <tr><td><img src="Images/opp12.jpg"></td></tr>
    <tr><td>Value 6 is pushed on values stack:</td></tr>
    <tr><td><img src="Images/opp13.jpg"></td></tr>
    <tr><td>The "/" operator is shifted:</td></tr>
    <tr><td><img src="Images/opp14.jpg"></td></tr>
    <tr><td>The next token in the input string, is the closing parenthesis. We proceed to a reduce operation repeatedly, until we meet, on top of the operators stack, the open parenthesis:</td></tr>
    <tr><td><img src="Images/opp15.jpg"></td></tr>
    <tr><td>The two parenthesis are discarded:</td></tr>
    <tr><td><img src="Images/opp16.jpg"></td></tr>
    <tr><td>The next step is a reduce operation (equal operators, left associativity):</td></tr>
    <tr><td><img src="Images/opp17.jpg"></td></tr>
    <tr><td>The "+" operator is shifted:</td></tr>
    <tr><td><img src="Images/opp18.jpg"></td></tr>
    <tr><td>Value 2 is pushed on values stack:</td></tr>
    <tr><td><img src="Images/opp19.jpg"></td></tr>
    <tr><td>The next token, the operator "^" has precedence greater than that in the top of the stack of operators, "+". It then is shifted:</td></tr>
    <tr><td><img src="Images/opp20.jpg"></td></tr>
    <tr><td>Value 2 is pushed on values stack:</td></tr>
    <tr><td><img src="Images/opp21.jpg"></td></tr>
    <tr><td>The next token, the operator "^" is equal to the top of the operators stack. The "^" operator is right-associative and then proceeds to an operation of shift:</td></tr>
    <tr><td><img src="Images/opp22.jpg"></td></tr>
    <tr><td>Value 3 is pushed on values stack:</td></tr>
    <tr><td><img src="Images/opp23.jpg"></td></tr>
    <tr><td>We reached the end of the input string. Repeatedly perform the task of reducing until the operators stack contains, at the top, the end-of-input symbol, $:</td></tr>
    <tr><td><img src="Images/opp24.jpg"></td></tr>
    <tr><td><img src="Images/opp25.jpg"></td></tr>
    <tr><td>Now the value stack contains only one value, the result:</td></tr>
    <tr><td><img src="Images/opp26.jpg"></td></tr>
</table>
