#include <stdlib.h>
#include "utilities.h"
#include "set_maker.h"

// Komparator struktur typu set_t, używany do posortowania
// ich rosnąco względem pierwszych elementów tablicy rows.
static int compareSets(const void *a, const void *b) {
    set_t setA = *(const set_t *) a;
    set_t setB = *(const set_t *) b;

    if (setA.rows[0] < setB.rows[0]) return -1;
    else if (setA.rows[0] > setB.rows[0]) return 1;
    else return 0;
}

set_t *groupSimilarRows(row_t *rows, int nOfRows, int *nOfSets) {
    // Tablica ze zbiorami podobnych wierszy.
    set_t *sets = (set_t *) safeMalloc(nOfRows * sizeof(set_t));
    for (int i = 0; i < nOfRows; i++) {
        sets[i].rows = (int *) safeMalloc(SET_STARTING_SIZE * sizeof(int));
    }
    int currSetSize = SET_STARTING_SIZE; // Pomocnicza zmienna do realokacji.

    // Wykluczenie pustego pliku wejściowego.
    if (nOfRows == 0) return sets;

    int setIndex = 0, rowIndex = 1;
    sets[setIndex].rows[0] = rows[0].lineIndex;

    for (int i = 1; i < nOfRows; i++) {
        if (compareRows((void *) &rows[i - 1], (void *) &rows[i]) == 0) {
            // Podobne wiersze grupujemy razem.
            sets[setIndex].rows[rowIndex++] = rows[i].lineIndex;

            if (rowIndex == currSetSize) {
                sets[setIndex].rows = safeRealloc(sets[setIndex].rows,
                                                  &currSetSize, sizeof(int));
            }
        } else {
            // Różne wiersze rozdzielamy do oddzielnych setów.
            qsort(sets[setIndex].rows, rowIndex, sizeof(int), compareInt);
            sets[setIndex].rowsSize = rowIndex;

            setIndex++;
            currSetSize = SET_STARTING_SIZE;
            sets[setIndex].rows[0] = rows[i].lineIndex;
            rowIndex = 1;
        }
    }
    qsort(sets[setIndex].rows, rowIndex, sizeof(int), compareInt);
    sets[setIndex].rowsSize = rowIndex;

    setIndex++;
    qsort(sets, setIndex, sizeof(set_t), compareSets);
    *nOfSets = setIndex;

    return sets;
}