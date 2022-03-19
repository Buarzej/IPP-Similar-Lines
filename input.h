#ifndef INPUT_H
#define INPUT_H

// Początkowy rozmiar tablicy "rows" przechowującej dane
// wejściowych linii tekstu (realokowana w razie potrzeby).
#define ROWS_STARTING_SIZE 4

// Funkcja wczytująca i przetwarzająca dane z wejścia poprzez:
//   1. wczytanie wejściowych linii tekstu,
//   2. przetworzenie każdej linii (podział na liczby
//      i nieliczby oraz utworzenie struktury typu row_t),
//   3. utworzenie tablicy wypełnionych struktur typu row_t
//      i posortowanie jej przy użyciu funkcji compareRows
//      (sposób sortowania opisany przy definicji ww. funkcji
//      w pliku row_parser.h),
//   4. zwrócenie gotowej tablicy struktur typu row_t oraz
//      zapisanie liczby jej elementów do zmiennej nOfRows.
extern row_t *getInput(int *nOfRows);

#endif // INPUT_H
