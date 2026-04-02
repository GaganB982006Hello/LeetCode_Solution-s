#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int pos;
} Robot;

// Comparator for sorting robots by position
int compare(const void* a, const void* b) {
    return ((Robot*)a)->pos - ((Robot*)b)->pos;
}

int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    Robot* robots = malloc(positionsSize * sizeof(Robot));
    for (int i = 0; i < positionsSize; i++) {
        robots[i].id = i;
        robots[i].pos = positions[i];
    }

    qsort(robots, positionsSize, sizeof(Robot), compare);

    int* stack = malloc(positionsSize * sizeof(int));
    int top = -1;

    for (int j = 0; j < positionsSize; j++) {
        int i = robots[j].id;
        if (directions[i] == 'R') {
            stack[++top] = i;
        } else {
            while (top >= 0 && healths[i] > 0) {
                int r_idx = stack[top];
                if (healths[r_idx] < healths[i]) {
                    healths[i]--;
                    healths[r_idx] = 0;
                    top--;
                } else if (healths[r_idx] > healths[i]) {
                    healths[r_idx]--;
                    healths[i] = 0;
                } else {
                    healths[i] = 0;
                    healths[r_idx] = 0;
                    top--;
                }
            }
        }
    }

    int* result = malloc(positionsSize * sizeof(int));
    int count = 0;
    for (int i = 0; i < positionsSize; i++) {
        if (healths[i] > 0) {
            result[count++] = healths[i];
        }
    }

    *returnSize = count;
    free(robots);
    free(stack);
    return result;
}
