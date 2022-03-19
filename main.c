#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "set_maker.h"
#include "input.h"

void readSets(set_t *sets, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < sets[i].rowsSize; j++) {
            if (j != sets[i].rowsSize - 1)
                printf("%d ", sets[i].rows[j]);
            else
                printf("%d", sets[i].rows[j]);
        }
        printf("\n");
    }
}

void freeEverything(row_t *rows, set_t *sets, int size) {
    for (int i = 0; i < size; i++) {
        free(rows[i].line);
        free(rows[i].words);
        free(rows[i].numbers);
        free(sets[i].rows);
    }
    free(rows);
    free(sets);
}

int main() {
    int nOfRows = 0;
    row_t *rows = getInput(&nOfRows);

    int nOfSets = 0;
    set_t *sets = groupSimilarRows(rows, nOfRows, &nOfSets);
    readSets(sets, nOfSets);

    freeEverything(rows, sets, nOfRows);

    return 0;
}