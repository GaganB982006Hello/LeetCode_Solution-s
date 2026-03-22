#include <stdbool.h>

bool findRotation(int** mat, int matSize, int* matColSize, int** target, int targetSize, int* targetColSize) {
    int n = matSize;
    
    // Assume all 4 possible rotations could be valid initially
    bool deg0 = true;
    bool deg90 = true;
    bool deg180 = true;
    bool deg270 = true;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Check 0 degrees (no rotation)
            if (mat[i][j] != target[i][j]) {
                deg0 = false;
            }
            // Check 90 degrees clockwise
            if (mat[i][j] != target[j][n - 1 - i]) {
                deg90 = false;
            }
            // Check 180 degrees
            if (mat[i][j] != target[n - 1 - i][n - 1 - j]) {
                deg180 = false;
            }
            // Check 270 degrees clockwise
            if (mat[i][j] != target[n - 1 - j][i]) {
                deg270 = false;
            }
        }
    }
    
    // If any rotation remains true, it's a valid match
    return deg0 || deg90 || deg180 || deg270;
}
