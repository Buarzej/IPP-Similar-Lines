#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "row_parser.h"

static bool isBase8(char *string) {
    if (string[0] != '0') return false;

    while (*string != '\0') {
        if (*string < '0' || *string > '7')
            return false;
        string++;
    }

    return true;
}

static bool isBase16(char *string) {
    bool outside09, outsideAF;

    if ((int) strlen(string) < 2 || string[0] != '0' || string[1] != 'x')
        return false;

    string += 2;
    while (*string != '\0') {
        outside09 = (*string < '0' || *string > '9');
        outsideAF = (*string < 'a' || *string > 'f');
        if (outside09 && outsideAF)
            return false;
        string++;
    }

    return true;
}

// Funkcja sprawdzająca, czy string zawiera fragment "0x".
static bool contains0x(char *string) {
    int size = (int) strlen(string);

    for (int i = 1; i < size; i++) {
        if (string[i - 1] == '0' && string[i] == 'x')
            return true;
    }

    return false;
}

// Funkcja przetwarzająca pojedyncze wyrażenie,
// klasyfikująca je jako liczba (i konwertująca do
// typu long double) lub jako nieliczba.
static long double convertString(char *string, bool *isWord) {
    long double number;
    char *wordCheck = NULL; // Pomocniczy argument do strtoull() i strtold().

    if (isBase8(string) || isBase16(string)) {
        // Konwersja do systemu dziesiętnego.
        number = (long double) strtoull(string, &wordCheck, 0);
        return number;
    } else {
        number = strtold(string, &wordCheck);

        // "number == number" wyklucza NaN,
        // "!contains0x()" wyklucza nieprawidłowe liczby szesnastkowe.
        if (*wordCheck == '\0' && number == number && !contains0x(string)) {
            return number;
        } else {
            *isWord = true;
            return 0;
        }
    }
}

void splitString(char *string, row_t *row) {
    int inputSize = countWords(string);
    int wordsIndex = 0, numbersIndex = 0;
    bool isWord;
    long double convertedNumber;

    char **tempWords = (char **) safeMalloc(inputSize * sizeof(char *));
    long double *tempNumbers =
            (long double *) safeMalloc(inputSize * sizeof(long double));

    char whitespaces[] = " \t\n\v\f\r";
    char *splitWord = strtok(string, whitespaces);

    while (splitWord != NULL) {
        isWord = false;
        convertedNumber = convertString(splitWord, &isWord);
        if (isWord) {
            tempWords[wordsIndex++] = splitWord;
        } else {
            tempNumbers[numbersIndex++] = convertedNumber;
        }

        splitWord = strtok(NULL, whitespaces);
    }

    qsort(tempNumbers, numbersIndex, sizeof(long double), compareLongDouble);
    qsort(tempWords, wordsIndex, sizeof(char *), compareString);

    row->numbers = tempNumbers;
    row->numbersSize = numbersIndex;
    row->words = tempWords;
    row->wordsSize = wordsIndex;
}
