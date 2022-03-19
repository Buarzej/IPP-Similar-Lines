#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdbool.h>
#include <ctype.h>

// Zakres kodów ASCII dozwolonych znaków w słowach.
#define MIN_CHAR 33
#define MAX_CHAR 126

// Początkowy znak linii będących komentarzami.
#define COMMENT_CHAR '#'

// Mnożnik rozmiaru zaalokowanej pamięci przy realokacjach.
#define REALLOC_MULTIPLIER 2

// Struktura przechowująca pojedynczą linię z wejścia:
// line - wejściowy ciąg znaków
// numbers - tablica wszystkich liczb wydzielonych z line
// words - tablica wszystkich nieliczb wydzielonych z line
// numbersSize, wordsSize - liczby elementów powyższych tablic
// lineIndex - numer linii (taki sam, jak na wejściu)
typedef struct row_t {
    char *line;
    long double *numbers;
    char **words;
    int numbersSize, wordsSize, lineIndex;
} row_t;

// Funkcja sprawdzająca, czy string składa się tylko z białych znaków.
extern bool isStringEmpty(char *string);

// Funkcja sprawdzająca, czy string zawiera niedozwolone znaki,
// czyli znaki o kodach ASCII spoza powyżej zdefiniowanego zakresu
// [MIN_CHAR, MAX_CHAR]; oprócz tego dozwolone są białe znaki. Dla komentarzy
// (stringów zaczynających się od COMMENT_CHAR) funkcja zawsze zwraca false.
extern bool isStringIllegal(char *string);

// Funkcja zmieniająca wielkie litery na małe.
extern void toLowercase(char **string);

// Funkcja zliczająca liczbę spójnych wyrażeń oddzielonych
// białymi znakami w podanym stringu.
extern int countWords(const char *string);

// Komparator liczb typu long double, zgodny z interfejsem
// komparatorów używanych w qsort (z biblioteki standardowej).
extern int compareLongDouble(const void *a, const void *b);

// Komparator liczb typu int, zgodny z interfejsem
// komparatorów używanych w qsort (z biblioteki standardowej).
extern int compareInt(const void *a, const void *b);

// Komparator stringów, zgodny z interfejsem komparatorów
// używanych w qsort (z biblioteki standardowej).
extern int compareString(const void *a, const void *b);

// Komparator struktur typu row_t, zgodny z interfejsem komparatorów
// używanych w qsort (z biblioteki standardowej).
//
// Funkcja sprawdza kolejne atrybuty struktur, aby
// posortować je według następującej hierarchii:
//   1. kolejne wartości liczbowe tablicy numbers (rosnąco),
//   2. rozmiar tablicy numbers (rosnąco),
//   3. kolejne wartości stringów tablicy words (alfabetycznie),
//   4. rozmiar tablicy words (rosnąco).
int compareRows(const void *a, const void *b);

// Bezpieczna alokacja podanego rozmiaru pamięci
// (zawiera sprawdzenie, czy operacja się powiodła).
extern void *safeMalloc(size_t size);

// Bezpieczna realokacja pamięci.
// toRealloc - struktura do realokacji
// typeSize - rozmiar pojedynczego elementu struktury toRealloc
// currSize - obecna liczba elementów w strukturze toRealloc
//
// Funkcja najpierw modyfikuje zmienną currSize, mnożąc ją przez zdefiniowany
// REALLOC_MULTIPLIER, następnie realokuje strukturę toRealloc do rozmiaru
// currSize * typeSize, a na końcu sprawdza, czy operacja się powiodła.
extern void *safeRealloc(void *toRealloc, int *currSize, size_t typeSize);

// Bezpieczne wywołanie funkcji getline
// (zawiera sprawdzenie poprawnej alokacji bufora).
extern int safeGetline(char **buffer, size_t *bufferSize);

#endif // UTILITIES_H
