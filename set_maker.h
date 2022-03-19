#ifndef SET_MAKER_H
#define SET_MAKER_H

// Początkowy rozmiar tablicy "rows" struktury
// typu set_t (realokowany w razie potrzeby).
#define SET_STARTING_SIZE 4

// Struktura przechowująca pojedynczą grupę podobnych wierszy:
// rows - tablica indeksów podobnych wierszy
// rowsSize - liczba elementów tablicy rows
typedef struct set_t {
    int *rows;
    int rowsSize;
} set_t;

// Funkcja przetwarzająca wejściową tablicę rows rozmiaru nOfRows poprzez:
//   1. połączenie podobnych wierszy (elementów tablicy rows) w grupy,
//   2. utworzenie struktury typu set_t dla każdej grupy i wypełnienie
//      jej odpowiednimi numerami wierszy posortowanymi rosnąco,
//   3. zapisanie grup do tablicy struktur typu set_t
//      i posortowanie jej rosnąco względem najmniejszego
//      numeru wiersza w każdej grupie,
//   4. zwrócenie gotowej tablicy grup podobnych wierszy oraz
//      zapisanie liczby jej elementów do zmiennej nOfSets.
extern set_t *groupSimilarRows(row_t *rows, int nOfRows, int *nOfSets);

#endif // SET_MAKER_H
