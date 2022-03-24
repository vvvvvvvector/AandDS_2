# Zadanie "BajtCoin" (Dijkstra's algorithm)

## Treść zadania

Duża popularność kryptowalut sprawiła, że i nasz bohater Alojzy zainteresował się tą tematyką. System, którego nie da się złamać?! Rewolucja! Alojzy zdumiony możliwościami technologii blockchain, służącej do przechowywania i przesyłania informacji o transakcjach zawartych w internecie, zdecydował się inwestować w internetowe monety. Najbardziej zaciekawił go BajtCoin, który ponoć stosuje wyjątkową, nikomu nieznaną formę algorytmu. Jego unikalność sprawia, że można na nim bardzo dobrze zarobić… Niestety rynek kryptowalut jest bardzo niestabilny, a wybrana przez naszego poczciwego programistę waluta dostępna jest jedynie na ograniczonej liczbie giełd…

Na szczęście można przelewać kryptowaluty pomiędzy giełdami, tak aby dotrzeć do tej upragnionej. Oczywiście wiążę się to z pewnymi kosztami, mianowicie każda z giełd za wypłacanie z niej pieniędzy pobiera od nich pewną prowizję. Wpływ na wysokość prowizji ma to, pomiędzy którymi giełdami jest dokonywany transfer. W trosce o swoje **100000** zł, które zainwestuje, nasz przezorny student zdecydował, że nie może być zbyt pazerny. Aby nie wpaść w pułapkę grania na giełdach oraz uniknąć innych zagrożeń tj. niestabilność tego innowacyjnego rynku. Postawił sobie pewne ograniczenie. Mianowicie, jeśli zwiększy wartość swoich BajtCoinów o 20% to przeleje pieniądze z powrotem do swojej wiodącej polskiej giełdy cyfrowych walut.

Możliwości dostania się do giełd, które operują BajtCoinami jest mnóstwo. Każda giełda obciąża nas nieusystematyzowaną wielkością prowizji, co komplikuje wybór naszego bohatera. Pomóż Alojzemu w przygotowaniu algorytmu, który ułatwi mu wybór.

## Wejście:

Program wczytuje liczby naturalną **X**, która definiuje ilość giełd. Następnie algorytm powinien odczytać **X wartości 0 lub 1**, określające status posiadania BajtCointa kolejnych giełd. **0** jeśli giełda nie posiada w swojej ofercie BajtCoina i 1 w przeciwnym wypadku. Kolejno algorytm wczytuje liczbę naturalną **N i N połączeń pomiędzy giełdami, czyli parę liczb A i B oraz dwie liczby rzeczywiste większe-równe zeru I i J**. **A** i **B** to liczby odpowiadające giełdom, zaś **I** to wysokość prowizji podczas transferu przed powieleniem majątku przez Alojzego, a **J** po jego powieleniu. Następnie program wczytuję liczbę naturalną **M**, która określa numer naszej wiodącej giełdy kryptowalut.

**1 <= X, N <= 1000000000**\
**0 <= A, B <= 1000000000**\
**0.0 <= I, J <= 0.5**

## Wyjście:

Na wyjściu algorytm powinien wyświetlić największą kwotę, jaką mógłby otrzymać Alojzy, przelewając pieniądze pomiędzy giełdami. Wynikiem powinna być liczba całkowita zaokrąglona w dół do liczby jedności.

### PRZYKŁADOWE DANE WEJŚCIOWE:

```
4
0 0 0 1
5
0 1 0.01 0.02
0 2 0.005 0.005
0 3 0.02 0.00
1 3 0.01 0.00
2 3 0.015 0.001
0
```

### PRZYKŁADOWE DANE WYJŚCIOWE:

```
117612
```

### UWAGA

Na giełdach pomijane są koszty zamiany PLN na kryptowaluty, a prowizji ulega wartość w PLN. Poniżej obrazek poglądowy. Wagi zmieniają się dopiero po powieleniu kapitału przez naszego bohatera.

### RYSUNEK POMOCNICZY

![rysunek pomocniczy](1.png)
