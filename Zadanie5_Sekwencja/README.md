# Zadanie "Ukryta sekwencja" (Rabin-Karp)

## Treść zadania

Mówiąc delikatnie Alojzemu kolejne inwestycje w BajtCoina "nie pykły". W związku z tym, szuka sposobu na łatwy zarobek i próbował już wielu rzeczy. Teraz zainteresowały go gry losowe tj. LOTTO. Uważa, że wszystko jest tam ustawione! By wygrać duże pieniądze w kumulacji należy odgadnąć zasady funkcjonowania systemu. Te zasady nasz bohater usłyszał od swojego kolegi, w postaci bardzo ciekawej nowiny. Niestety nie do końca rozumie o co w niej chodzi!

**CIEKAWA NOWINA KOLEGI ALOJZEGO - SEBY:**\
*"Liczby podzielone są na pewne okresy. **Okres jest sekwencją wielu liczb z zakresu od 0 do 100**. W każdym okresie co najmniej dwa razy pojawia się pewna **subsekwencja liczb - X**. Suma dwóch poprzednich miejsca wystąpienia subsekwencji mówi o tym, gdzie subsekwencja pojawi się po raz kolejny w danym okresie. Pierwsza pozycja subsekwencji wykraczająca poza zakres okresu, pomniejszona o ilość elementów w okresie, będzie indeksem wystąpienia tej subsekwencji w kolejnym okresie liczb."*\
Pomóż Alojzemu odkryć pierwsze wystąpienie magicznej **subsekwencji X** w następnym okresie.

## Wejście:
Program wczytuje liczbę naturalną **V**, będącą ilością liczb w aktualnym okresie. Następnie program powinien wczytać **V liczb naturalnych**. W kolejnym kroku algorytm powinien wczytać liczbę naturalną **P**, a na koniec **P liczb naturalnych** reprezentujących **subsekwencję X**.

**0 <= liczby w sekwencji <= 100**\
**0 <= V, P, N <= 2 000 000 000**

## Wyjście:
Wyświetl **pozycję pierwszego wystąpienia subsekwencji w kolejnym okresie**. Zakładając, że sekwencje numerowane są od 0.

### PRZYKŁADOWE DANE WEJŚCIOWE 
```
16
1 1 1 2 3 88 99 24 1 2 3 1 2 3 99 39
2
2 3
```
### PRZYKŁADOWE DANE WYJŚCIOWE
```
5
```
### UWAGA
Zadanie powinno być samodzielną implementacją algorytmu Rabina-Karpa.

![Zadanie5Tests](../TestResults/Zadanie5.png)