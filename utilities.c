// Wymagane do poprawnego działania funkcji getline().
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include "utilities.h"

bool isStringEmpty(char *string) {
    while (*string != '\0') {
        if (!isspace((unsigned char) *string))
            return false;
        string++;
    }

    return true;
}

bool isStringIllegal(char *string) {
    // Wykluczamy komentarze.
    if (string[0] == COMMENT_CHAR) return false;

    while (*string != '\0') {
        if ((int) *string < MIN_CHAR || (int) *string > MAX_CHAR) {
            if (!isspace((unsigned char) *string)) return true;
        }
        string++;
    }

    return false;
}

void toLowercase(char **string) {
    for (int i = 0; (*string)[i]; i++)
        (*string)[i] = tolower((*string)[i]);
}

int countWords(const char *string) {
    bool insideWord = !isspace((unsigned char) string[0]);
    int count = insideWord ? 1 : 0;

    while (*string != '\0') {
        if (!isspace((unsigned char) *string) && !insideWord) {
            count++;
            insideWord = true;
        } else if (isspace((unsigned char) *string))
            insideWord = false;
        string++;
    }

    return count;
}

int compareLongDouble(const void *a, const void *b) {
    if (*(long double *) a < *(long double *) b) return -1;
    else if (*(long double *) a > *(long double *) b) return 1;
    else return 0;
}

int compareInt(const void *a, const void *b) {
    if (*(int *) a < *(int *) b) return -1;
    else if (*(int *) a > *(int *) b) return 1;
    else return 0;
}

int compareString(const void *a, const void *b) {
    return strcmp(*(const char **) a, *(const char **) b);
}

int compareRows(const void *a, const void *b) {
    row_t rowA = *(const row_t *) a;
    row_t rowB = *(const row_t *) b;
    int maxNumbersSize = ((rowA.numbersSize > rowB.numbersSize)
                          ? rowA.numbersSize : rowB.numbersSize);

    // Porównanie tablic liczb.
    for (int i = 0; i < maxNumbersSize; i++) {
        if (i == rowA.numbersSize) {
            return -1;
        } else if (i == rowB.numbersSize) {
            return 1;
        }
        if (rowA.numbers[i] > rowB.numbers[i]) {
            return 1;
        } else if (rowA.numbers[i] < rowB.numbers[i]) {
            return -1;
        }
    }

    // Porównanie tablic nieliczb.
    int maxWordsSize = ((rowA.wordsSize > rowB.wordsSize)
                        ? rowA.wordsSize : rowB.wordsSize);
    for (int i = 0; i < maxWordsSize; i++) {
        if (i == rowA.wordsSize) {
            return -1;
        } else if (i == rowB.wordsSize) {
            return 1;
        }
        if (strcmp(rowA.words[i], rowB.words[i]) > 0) {
            return 1;
        } else if (strcmp(rowA.words[i], rowB.words[i]) < 0) {
            return -1;
        }
    }

    return 0;
}

void *safeMalloc(size_t size) {
    void *allocated = malloc(size);
    if (allocated == NULL) exit(1);

    return allocated;
}

void *safeRealloc(void *toRealloc, int *currSize, size_t typeSize) {
    *currSize *= REALLOC_MULTIPLIER;

    void *reallocated = realloc(toRealloc, *currSize * typeSize);
    if (reallocated == NULL) exit(1);

    return reallocated;
}

int safeGetline(char **buffer, size_t *bufferSize) {
    errno = 0;
    int getlineSize = (int) getline(buffer, bufferSize, stdin);

    // Sprawdzenie poprawnej alokacji bufora.
    if (errno == ENOMEM) exit(1);

    return getlineSize;
}