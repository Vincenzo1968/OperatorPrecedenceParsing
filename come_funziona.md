OperatorPrecedenceParsing
=========================

Esempio
-------

L'operazione di *shift* consiste nel piazzare in cima allo stack degli operatori l'operatore appena letto dalla stringa di input.

L'operazione di *reduce* consiste nel prelevare un operatore dallo stack degli operatori e due(o uno, se l'operatore è unario) operandi dallo stack dei valori. Si esegue l'operazione e il risultato lo si piazza in cima allo stack dei valori.


Si voglia valutare la seguente espressione:

    21 - 8 - 2 * 3 + (6 / 3) + 2^2^3

<table>
    <tr><td>La situazione di partenza è la seguente($ indica le fine dell'input):</td></tr>
    <tr><td>![opp01](Images/opp01.jpg)</td></tr>
    <tr><td>Il primo token letto dalla stringa di input è il valore 21; lo si piazza in cima allo stack dei valori:</td></tr>
    <tr><td>![opp02](Images/opp02.jpg)</td></tr>
    <tr><td>Il token successivo è l'operatore "-"; si esegue un'operazione di shift:</td></tr>
    <tr><td>![opp03](Images/opp03.jpg)</td></tr>
    <tr><td>Il token successivo è il valore 8; lo piazziamo in cima allo stack dei valori:</td></tr>
    <tr><td>![opp04](Images/opp04.jpg)</td></tr>
    <tr><td>Il token successivo è l'operatore "-"; lo confrontiamo con l'operatore in cima allo stack degli operatori, "-". hanno uguale precedenza; eseguiamo un'operazione di reduce perché l'operatore "-" è associativo a sinistra:</td></tr>
    <tr><td>![opp05](Images/opp05.jpg)</td></tr>
    <tr><td>L'operatore "-" viene shiftato:</td></tr>
    <tr><td>![opp06](Images/opp06.jpg)</td></tr>
    <tr><td>Piazziamo il token successivo, il valore 2, nello stack dei valori:</td></tr>
    <tr><td>![opp07](Images/opp07.jpg)</td></tr>
    <tr><td>Il token successivo, l'operatore "*" ha precedenza maggiore di quello che si trova in cima allo stack degli operatori, "-", e quindi va shiftato:</td></tr>
    <tr><td>![opp08](Images/opp08.jpg)</td></tr>
    <tr><td>Il valore 3 viene piazzato in cima allo stack dei valori:</td></tr>
    <tr><td>![opp09](Images/opp09.jpg)</td></tr>
    <tr><td>Il token successivo, l'operatore "+", ha precedenza minore rispetto a quello che si trova in cima allo stack degli operatori, "*", e quindi eseguimo un'operazione di reduce:</td></tr>
    <tr><td>![opp10](Images/opp10.jpg)</td></tr>
    <tr><td>Il confronto fra i due operatori, adesso, si traduce in un'operazione di reduce(precedenza uguale ma l'operatore "-", in cima allo stack degli operatori, è associativo a sinistra):</td></tr>
    <tr><td>![opp11](Images/opp11.jpg)</td></tr>
    <tr><td>L'operatore "+" viene shiftato. La parentesi aperta viene shiftata:<td></tr>
    <tr>![opp12](Images/opp12.jpg)</tr>
    <tr><td>Il valore 6 viene piazzato in cima allo stack degli operatori:</td></tr>
    <tr><td>![opp13](Images/opp13.jpg)</td></tr>
    <tr><td>L'operatore "/" viene shiftato:</td></tr>
    <tr><td>![opp14](Images/opp14.jpg)</td></tr>
    <tr><td>Il token successivo, nella stringa di input, è la parentesi chiusa. Si procede ripetutamente a un'operazione du reduce, finché non incontriamo, in cima allo stack degli operatori, la parentesi aperta:</td></tr>
    <tr><td>![opp15](Images/opp15.jpg)</td></tr>
    <tr><td>Le due parenesi vengono scartate:</td></tr>
    <tr><td>![opp16](Images/opp16.jpg)</td></tr>
    <tr><td>L'operazione successiva è una reduce(operatori uguali, associatività a sinistra):</td></tr>
    <tr><td>![opp17](Images/opp17.jpg)</td></tr>
    <tr><td>L'operatore "+" viene shiftato:</td></tr>
    <tr><td>![opp18](Images/opp18.jpg)</td></tr>
    <tr><td>Il valore 2 viene piazzato in cima allo stack degli operatori:</td></tr>
    <tr><td>![opp19](Images/opp19.jpg)</td></tr>
    <tr><td>Il token successivo, l'operatore "^" ha prededenza maggiore rispetto a quello in cima allo stack degli operatori, "+". Si procede quindi a un'operazione di shift:</td></tr>
    <tr><td>![opp20](Images/opp20.jpg)</td></tr>
    <tr><td>Il valore 2 viene piazzato in cima allo stack dei valori:</td></tr>
    <tr><td>![opp21](Images/opp21.jpg)</td></tr>
    <tr><td>Il token successivo, l'operatore "^" è uguale a quello in cima allo stack degli operatori. L'operatore "^" è associativo a destra e si procede, quindi, a un'operazione di shift:<td></tr>
    <tr><td>![opp22](Images/opp22.jpg)</td></tr>
    <tr><td>Il valore 3 viene piazzato in cima allo stack dei valori:</td></tr>
    <tr><td>![opp23](Images/opp23.jpg)</td></tr>
    <tr><td>Siamo giunti alla fine della stringa di input. Eseguiamo ripetutamente l'operazione di reduce finché lo stack degli operatori contiene, in cima, il simbolo di fine input, $:</td></tr>
    <tr><td>![opp24](Images/opp24.jpg)</td></tr>
    <tr><td>![opp25](Images/opp25.jpg)</td></tr>
    <tr><td>Adesso lo stack dei valori contiene un solo valore, il risultato dell'espressione:</td></tr>
    <tr><td>![opp26](Images/opp26.jpg)</td></tr>
</table>
