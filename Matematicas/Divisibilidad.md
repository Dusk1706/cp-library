# Criterios de divisibilidad
Existen varios problemas donde nos piden saber si es posible dividir un número con otro sin que haya residuo. Esta operación es sencilla cuando manejamos enteros, pero en algunos problemas nos dan números tan grandes que es necesario aplicar otras estrategias, aquí un apartado con alguna de estas técnicas con diferentes números.

## Aritmetica Modular
Es un sistema de aritmética para números enteros donde los números regresan a 0 cuando llegan a cierto valor llamado módulo. Los únicos números que se pueden utilizar son entre 0 y m-1, donde m es una constante.
Está técnica es útil en algunos ad hoc, pero sobre todo es utilizada en problemas de combinatoria donde las respuestas pueden ser demasiado grandes, por lo que las piden moduladas. Normalmente el módulo en este tipo de problemas es de 109 + 7.
Las operaciones son las siguientes:
![](https://github.com/Dusk1706/Estructuras-de-datos-y-Algoritmos/blob/main/Imagenes/AritmeticaModular.jpg)

## Un número es divisible por 2 siempre que la cifra de sus unidades sea 0, 2, 4, 6 u 8.
## Un número es divisible por 3 siempre que la suma de sus cifras sea un múltiplo de 3.
## Un número es divisible por 4 siempre que el número formado por sus dos últimas cifras sea un múltiplo de 4.
## Un número es divisible por 5 siempre que la cifra de sus unidades sea 0 ó 5.
## Un número es divisible por 6 siempre que se compruebe sea divisible por 2 y 3.
## Un número es divisible por 8 siempre que el número formado por sus tres últimas cifras sea un múltiplo de 8.
## Un número es divisible por 9 siempre que la suma de sus cifras sea múltiplo de 9.
## Un número es divisible por 10 siempre que la cifra de sus unidades sea 0.
## Un número es divisible por 11 siempre que el valor absoluto de la diferencia de la suma de sus cifras que ocupan lugar par y de las que ocupan lugar impar sea múltiplo de 11.
## Un número es divisible por 12 siempre que se compruebe es divisible por 3 y 4.
