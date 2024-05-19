# II Projekt AIZO. Kamil Sobierajski 2024.

## 2024/05/20

- Organizacja menu
- Implementacja obu nieskierowanych reprezentacji grafów
- Pobieranie grafu z pliku
- Generowanie losowe grafu spójnego
- Wyświetlanie grafu
- Funkcja benchmark
- MST

## 2024/05/27

- Implementacja obu skierowanych reprezentacji grafów
- shortest path
- automatyczne testy + wykresy (folder z input-grafami, z wykresami, z wynikami w excel-friendly formacie - tabela przestawna)
- ford-fulkerson ([edmonds-karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm))
- readme

## Reprezentacja grafu

### Złożoności pamięciowe

- Lista krawędzi ($2E$)
- Macierz sąsiedztwa ($V^2$)
- Lista sąsiedztwa ($V \cdot d$)
- Macierz incydencji ($V \cdot E$)

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

### Ogólne parametry

- Liczba wierzchołków
- Liczba krawędzi
- Max liczba krawędzi
- Stopień wypełnienia
- Wagi poszczególnych krawędzi
- Maksymalny stopień wierzchołków (ewentualnie średni)

## MST (Minimum Spanning Tree)

| Parametr                        | wartość |
| ------------------------------- | ------- |
| Liczba wierzchołków             | n       |
| Liczba krawędzi                 | n - 1   |
| Liczba krawędzi w grafie pełnym | n(n-1)  |
