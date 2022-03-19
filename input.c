#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"
#include "row_parser.h"
#include "input.h"

row_t *getInput(int *nOfRows) {
    // Tablica na wczytywane linie tekstu.
    row_t *rows = (row_t *) safeMalloc(ROWS_STARTING_SIZE * sizeof(row_t));
    int rowsSize = ROWS_STARTING_SIZE; // Pomocnicza zmienna do realokacji.

    // validLineIndex pomija komentarze oraz puste i błędne linie.
    int lineIndex = 1, validLineIndex = 0;

    char *buffer = NULL, *bufferCopy = NULL;
    size_t bufferSize = 0;

    int getlineSize = safeGetline(&buffer, &bufferSize);

    while (getlineSize != -1) {
        // "strlen(buffer) != getlineSize" wyklucza linie z '\0' wewnątrz.
        if (isStringIllegal(buffer) || strlen(buffer) != (size_t) getlineSize) {
            fprintf(stderr, "ERROR %d\n", lineIndex);
        } else if (!isStringEmpty(buffer) && buffer[0] != COMMENT_CHAR) {
            // Skopiowanie bufora do tymczasowej tablicy.
            bufferCopy = (char *) safeMalloc((getlineSize + 1) * sizeof(char));
            strcpy(bufferCopy, buffer);
            toLowercase(&bufferCopy);

            // Przetworzenie wczytanej linii.
            row_t newRow;
            newRow.line = bufferCopy;
            newRow.lineIndex = lineIndex;
            splitString(bufferCopy, &newRow);
            rows[validLineIndex++] = newRow;

            if (validLineIndex == rowsSize) {
                rows = safeRealloc(rows, &rowsSize, sizeof(row_t));
            }
        }

        // Wczytanie kolejnej linii.
        lineIndex++;
        getlineSize = safeGetline(&buffer, &bufferSize);
    }

    free(buffer);

    *nOfRows = validLineIndex;
    qsort(rows, *nOfRows, sizeof(row_t), compareRows);

    return rows;
}