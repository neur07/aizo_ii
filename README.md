# II Projekt AIZO. Kamil Sobierajski 2024.

## Wymagania na ocenę 5.5

Program implementujący dwie reprezentacje grafu:

- Macierz Incydencji
- Lista Sąsiedztwa

Dla każdej z nich:

- algorytm Prima oraz algorytm Kruskala,
- algorytm Dijkstry oraz algorytm Forda-Bellmana,
- algorytm Forda-Fulkersona

Ponadto:

- Ograniczyć wykorzystanie bibliotek, całkowicie wykluczyć STL
- umożliwić tworzenie grafu spójnego na podstawie pliku oraz danych losowych (przy podanej liczbie wierzchołków oraz gęstości wypełnienia)
- zaimplementować precyzyjne odmierzanie czasu, na podstawie których powstanie analiza algorytmów w sprawozdaniu
- umożliwić wyświetlenie podglądu zawartości grafu dla obu reprezentacji
- dynamiczna alokacja pamięci

## Do zrealizowania

### Todo

- Sprawdzenie obecnej implementacji reprezentacji grafu
- Generowanie losowego grafu pełnego dla obu reprezentacji
- stopnie wypełnienia
- prawidłowe MST
- grafy skierowane
- prawidłowe shortest path

### 2024/06/03

- Generowanie losowego grafu spójnego
- (1) MST
- Implementacja obu skierowanych reprezentacji grafów
- (2) shortest path
- automatyczne testy + wykresy (folder z input-grafami, z wykresami, z wynikami w excel-friendly formacie - tabela przestawna)
- (3) ford-fulkerson ([edmonds-karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm))
- plan pomiarów
- sprawozdanie
- zoptymalizować dyrektywy include

## Teoria

### Ogólne parametry

| Parametr                        |            wartość |
| ------------------------------- | -----------------: |
| Liczba wierzchołków             |                  n |
| Min liczba krawędzi grafu spój. |       $e = n - 1 $ |
| Liczba krawędzi w grafie pełnym |    $e_p = n(n-1) $ |
| Stopień wypełnienia             | $\frac{e}{n(n-1)}$ |

### Złożoności pamięciowe

| Reprezentacja grafu | Złożoność pamięciowa | Złożoność czasowa |
| ------------------- | -------------------: | ----------------: |
| Lista krawędzi      |                 $2E$ |                 - |
| Macierz sąsiedztwa  |                $V^2$ |                 - |
| Lista sąsiedztwa    |          $V \cdot d$ |                 - |
| Macierz incydencji  |          $V \cdot E$ |                 - |

### Lista sąsiedztwa

### Macierz incydencji

Przykład ważonej skierowanej macierzy incydencji oparty na założeniach opisanych w [artykule](https://en.wikipedia.org/wiki/Incidence_matrix).

$
\begin{bmatrix}
    6 & 1 & 0 & 0 & 0          \\[1em]
    -6 & 0 & -8 & 0 & 0          \\[1em]
    0 & -1 & 8 & 9 & -3          \\[1em]
    0 & 0 & 0 & -9 & 3          \\[1em]
\end{bmatrix}
$

Implementacja dynamicznej Macierzy Incydencji w C++ przy wykorzystniu wskaźników na tablicę wskaźników ([wytłumaczone w tym filmie](https://www.youtube.com/watch?v=mGl9LO-je3o))
