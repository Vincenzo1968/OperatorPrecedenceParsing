OperatorPrecedenceParsing
=========================

Esempio
-------

L'operazione di *shift* consiste nel piazzare in cima allo stack degli operatori l'operatore appena letto dalla stringa di input.

L'operazione di *reduce* consiste nel prelevare un operatore dallo stack degli operatori e due(o uno, se l'operatore è unario) operandi dallo stack dei valori. Si esegue l'operazione e il risultato lo si piazza in cima allo stack dei valori.


Si voglia valutare la seguente espressione:

    21 - 8 - 2 * 3 + (6 / 3) + 2^2^3

La situazione di partenza è la seguente($ indica le fine dell'input):
![opp01](Images/opp01.jpg)  

Il primo token letto dalla stringa di input è il valore 21; lo si piazza in cima allo stack dei valori:
![opp02](Images/opp02.jpg)  

Il token successivo è l'operatore "-"; si esegue un'operazione di shift:
![opp03](Images/opp03.jpg)  

Il token successivo è il valore 8; lo piazziamo in cima allo stack dei valori:
![opp04](Images/opp04.jpg)  

Il token successivo è l'operatore "-"; lo confrontiamo con l'operatore in cima allo stack degli operatori, "-". hanno uguale precedenza; eseguiamo un'operazione di reduce perché l'operatore "-" è associativo a sinistra:
![opp05](Images/opp05.jpg)  

L'operatore "-" viene shiftato:
![opp06](Images/opp06.jpg)  

Piazziamo il token successivo, il valore 2, nello stack dei valori:
![opp07](Images/opp07.jpg)  

Il token successivo, l'operatore "*" ha precedenza maggiore di quello che si trova in cima allo stack degli operatori, "-", e quindi va shiftato:
![opp08](Images/opp08.jpg)  

Il valore 3 viene piazzato in cima allo stack dei valori:
![opp09](Images/opp09.jpg)  

Il token successivo, l'operatore "+", ha precedenza minore rispetto a quello che si trova in cima allo stack degli operatori, "*", e quindi eseguimo un'operazione di reduce:
![opp10](Images/opp10.jpg)  

Il confronto fra i due operatori, adesso, si traduce in un'operazione di reduce(precedenza uguale ma l'operatore "-", in cima allo stack degli operatori, è associativo a sinistra):
![opp11](Images/opp11.jpg)  

L'operatore "+" viene shiftato. La parentesi aperta viene shiftata:
![opp12](Images/opp12.jpg)  

Il valore 6 viene piazzato in cima allo stack degli operatori:
![opp13](Images/opp13.jpg)  

L'operatore "/" viene shiftato:
![opp14](Images/opp14.jpg)  

Il token successivo, nella stringa di input, è la parentesi chiusa. Si procede ripetutamente a un'operazione du reduce, finché non incontriamo, in cima allo stack degli operatori, la parentesi aperta:
![opp15](Images/opp15.jpg)  

Le due parenesi vengono scartate:
![opp16](Images/opp16.jpg)  

L'operazione successiva è una reduce(operatori uguali, associatività a sinistra):
![opp17](Images/opp17.jpg)  

L'operatore "+" viene shiftato:
![opp18](Images/opp18.jpg)  

Il valore 2 viene piazzato in cima allo stack degli operatori:
![opp19](Images/opp19.jpg)  

Il token successivo, l'operatore "^" ha prededenza maggiore rispetto a quello in cima allo stack degli operatori, "+". Si procede quindi a un'operazione di shift:
![opp20](Images/opp20.jpg)  

Il valore 2 viene piazzato in cima allo stack dei valori:
![opp21](Images/opp21.jpg)  

Il token successivo, l'operatore "^" è uguale a quello in cima allo stack degli operatori. L'operatore "^" è associativo a destra e si procede, quindi, a un'operazione di shift:
![opp22](Images/opp22.jpg)  

Il valore 3 viene piazzato in cima allo stack dei valori:
![opp23](Images/opp23.jpg)  

Siamo giunti alla fine della stringa di input. Eseguiamo ripetutamente l'operazione di reduce finché lo stack degli operatori contiene, in cima, il simbolo di fine input, $:
![opp24](Images/opp24.jpg)  

![opp25](Images/opp25.jpg)  

Adesso lo stack dei valori contiene un solo valore, il risultato dell'espressione:
![opp26](Images/opp26.jpg)  
