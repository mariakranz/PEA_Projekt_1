# Implementacja i analiza efektywności algorytmu podziału i ograniczeń

Zadanie polegało na zaimplementowaniu algoytmów rozwiązujących problem komiwojażera, takich jak przegląd zupełny (brute force) i metoda podziału i ograniczeń (branch and bound).


## Brute Force
Brute Force to algorytm, który generuje wszystkie możliwe permutacje ścieżek, oblicza ich koszt i zapamiętuje najmniejszą wartość.

## Branch and Bound
Ta metoda polega na zastosowaniu ograniczeń, które eliminują potrzebę przeglądu pewnej puli rozwiązań. W tej implementacji zastosowano ograniczenie dolne i górne. 
Ograniczenie dolne jest obliczane dla każdego badanego wierzchołka, natomiast ograniczenie górne jest aktualizowane (bądź nie) po dojściu do liścia drzewa. 
Przeszukiwanie grafu odbywa się metodą w głąb.

### Przykład działania B&B:  
Dany jest graf o zadanej macierzy sąsiedztwa (adjMatrix):  
<p>
  <img src="https://github.com/mariakranz/PEA_Projekt_1/assets/105527593/65ff9ee2-cf7c-4231-8130-5db5d155fcc1.png" alt="Title screen" />
</p>

Oszacowanie górne (UB) ustawiamy na nieskończoność.
Tworzymy tablice najmniejszych krawędzi wychodzących z każdego wierzchołka:
| vertex | minEdge |
|--------|---------|
| 0      | 10      |
| 1      | 11      |
| 2      | 10      |
| 3      | 10      |

Przeszukiwanie rozpoczynamy od wierzchołka 0. Ograniczenie dolne LB(0) = 10 + 11 + 10 + 10 = 41.  

Schodzimy do pierwszego syna wierzchołka 0, czyli wierzchołka 1. Aby wyliczyć dolne ograniczenie dla wierzchołka 1 należy podmienić krawędź minimalną wychodzącą z rodzica (wierzchołek 0)
na rzeczywistą krawędź, czyli w tym wypadku krawędź 0 -> 1. Po obliczeniu tej wartości, sprawdzamy czy jest mniejsza od UB.  
LB(0, 1) = 41 - minEdge[0] + adjMatrix[0][1] = 41 - 10 + 11 = 42 < UB 

Wartość jest mniejsza od ograniczenia górnego, zatem schodzimy do syna wierzchołka 1, czyli wierzchołka 2 i powtarzamy proces.  
LB(0, 1, 2) = 42 - minEdge[1] + adjMatrix[1][2] = 42 - 11 + 15 = 46 < UB  

Wartość jest mniejsza od ograniczenia górnego, zatem schodzimy do syna wierzchołka 2, czyli wierzchołka 3 i powtarzamy proces.  
LB(0, 1, 2, 3) = 42 - minEdge[2] + adjMatrix[2][3] = 46 - 10 + 20 = 56 < UB  

Węzeł 3 jest liściem, zatem obliczamy ostateczną ścieżkę dodając do dotychczasowej ścieżki krawędź 3 -> 0.  
Cycle = 56 - minEdge[3] + adjMatrix[3][0] = 56 - 10 + 10 = 56 < UB  

Utworzony został cykl, zatem jeśli Cycle < UB, to UB = Cycle.  

Graficzna reprezentacja tego przykładu znajduje się poniżej.
<p align="center">
  <img src="https://github.com/mariakranz/PEA_Projekt_1/assets/105527593/ca2a9297-e551-4029-8950-124c4e0553c0.png" alt="Graficzna reprezentacja przykładu." />
</p>

Pełne rozwiązanie znajduje się poniżej.
<p align="center">
  <img src="https://github.com/mariakranz/PEA_Projekt_1/assets/105527593/0db84f9a-37fe-4d4b-9f02-b9f855f6fcec.png" alt="Graficzna reprezentacja rozwiązania dla całego drzewa." />
</p>
Czerwone wierzchołki nie zostały odwiedzone (jak również ich dzieci) – zostały odrzucone dzięki ograniczeniu.


## Analiza efektywności obu algorytmów
Przeprowadzone badania wykazały szybszy wzrost wykładniczy dla algorytmu Brute Force, zatem jest on mniej wydajny niż algorytm Branch and Bound.
