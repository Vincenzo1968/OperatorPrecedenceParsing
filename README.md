OperatorPrecedenceParsing
=========================

Algorithm for parsing arithmetic expressions
--------------------------------------------

The algorithm involves the use of two stacks:

- Operators stack.
- Values stack.

The input is read from left to right. One proceeds in the following way:

* Step 1 *: push the symbol of the end of input, $, to operators stack.

* Step 2 *: reads the first token from the input string. If it is a value (operand) it's pushed on values stack. If it's an operator, we proceed as follows:

- 2.a: If the operator at the top of operators stack have higher precedence than or equal, you perform a reduce.
- 2.b: If the operator at the top of operators stack have lower precedence, you perform a shift.
- 3.c: if the two operators are the same, performing a reduce if the associativity is left; performing a shift if the associativity is right.

* Step 3 *: When the entire input string has been read, operators stack should only contain one item: $; values stack ​​should contain only one value, the result of the operation. Otherwise, here is a syntax error.

The shift operation is to push on operators stack, the operator just read from the input string.

The reduce operation consists in popping one operator from the operators stack and two (or one, if the operator is unary) operands from the values stack. It performs the operation and the result is pushed on values stack.

The management of parenthesis requires special handling: if the token just read from the input string is an open parenthesis, (, push it on operators stack. If the token read from the input string, however, is the opening parenthesis, ), you run the reduce operation repeatedly until the operators stack, contains, at the top, the opening parenthesis. Latter is popped from the operators stack and the two parenthesis are discarded. Continue reading the next token from the input string. If during the reduce operations you get to the bottom of the operators stack, $, without ever meeting the opening parenthesis, it shows the error "unbalanced parenthesis".



L'algoritmo prevede l'uso di due stack:

- stack degli operatori
- stack dei valori(operandi)

L'input viene letto da sinistra a destra un token alla volta. Si procede nel modo seguente:

*Passo 1*: si piazza il simbolo di fine input, $, nello stack degli operatori.

*Passo 2*: si legge il primo token dalla stringa di input. Se è un valore(operando) lo si piazza in cima allo stack dei valori. Se invece è un operatore, si procede come segue:

- 2.a: se l'operatore in cima allo stack degli operatori ha precedenza maggiore o uguale, si esegue un'operazione di reduce.
- 2.b: se l'operatore in cima allo stack degli operatori ha precedenza minore, si esegue un'operazione di shift.
- 3.c: se i due operatori sono uguali si esegue un'operazione di reduce se l'associatività è a sinistra; si esegue un'operazione di shift se l'associatività è a destra.

*Passo 3*: Quando l'intera stringa di input è stata letta, lo stack degli operatori dovrebbe contenere un solo elemento: $; lo stack dei valori dovrebbe contenere un solo valore, il risultato dell'operazione. In caso contrario si riporta un errore di sintassi.

L'operazione di shift consiste nel piazzare in cima allo stack degli operatori l'operatore appena letto dalla stringa di input.

L'operazione di reduce consiste nel prelevare un operatore dallo stack degli operatori e due(o uno, se l'operatore è unario) operandi dallo stack dei valori. Si esegue l'operazione e il risultato lo si piazza in cima allo stack dei valori.

La gestione delle parentesi richiede un trattamento particolare: se il token appena letto dalla stringa di input è una parentesi aperta, (, la si piazza in cima allo stack degli operatori. Se il token letto dalla stringa di input è, invece, la parentesi tonda, si esegue ripetutamente l'operazione di reduce finché lo stack degli operatori, contiene, in cima, la parentesi aperta. Quest'ultima viene prelevata dallo stack degli operatori e le due parentesi vengono scartate. Si prosegue leggendo il token successivo dalla stringa di input. Se durante le operazioni di reduce si arriva in fondo allo stack degli operatori, $, senza incontrare mai la parentesi aperta, si riporta l'errore "unbalanced parenthesis".
