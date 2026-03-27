#include <stdbool.h>

bool areSimilar(int** mat, int matSize, int* matColSize, int k) {
    int n = matColSize[0];
    k %= n;
    
    for (int i = 0; i < matSize; i++) {
        for (int j = 0; j < n; j++) {
            // Even if the direction differs (left vs right), 
            // the condition for similarity is mat[i][j] == mat[i][(j + k) % n]
            if (mat[i][j] != mat[i][(j + k) % n]) {
                return false;
            }
        }
    }
    return true;
}
