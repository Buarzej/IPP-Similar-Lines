#ifndef ROW_PARSER_H
#define ROW_PARSER_H

// Funkcja przetwarzająca wejściowe linie tekstu poprzez:
//   1. podzielenie stringa na wyrażenia poprzez usunięcie
//      białych znaków,
//   2. sklasyfikowanie każdego takiego wyrażenia jako
//      liczba (i konwersja do systemu dziesiętnego i typu
//      long double) lub jako nieliczba,
//   3. wypełnienie przetworzonymi wyrażeniami tablic numbers
//      i words oraz pól numbersSize i wordsSize podanej
//      struktury row,
//   4. posortowanie tablicy numbers rosnąco i tablicy
//      words alfabetycznie.
void splitString(char *string, row_t *row);

#endif // ROW_PARSER_H
