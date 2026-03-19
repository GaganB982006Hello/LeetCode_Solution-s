#include <string.h>
#include <stdbool.h>

int numberOfSubmatrices(char** grid, int gridSize, int* gridColSize) {
    int C = gridColSize[0];
    
    // Allocate 1D arrays directly on the stack (extremely fast, zero heap overhead)
    int diff[C];
    bool hasX[C];
    
    // Initialize memory to 0
    memset(diff, 0, sizeof(int) * C);
    memset(hasX, 0, sizeof(bool) * C);
    
    int count = 0;
    
    for (int i = 0; i < gridSize; ++i) {
        int rowDiff = 0;
        bool rowHasX = false;
        
        // Cache the row pointer to avoid double-dereferencing grid[i][j]
        char* row = grid[i]; 
        
        for (int j = 0; j < C; ++j) {
            char val = row[j];
            
            if (val == 'X') {
                rowDiff++;
                rowHasX = true;
            } else if (val == 'Y') {
                rowDiff--;
            }
            
            // Update vertical prefix state
            diff[j] += rowDiff;
            
            if (rowHasX) {
                hasX[j] = true;
            }
            
            // Check validity
            if (diff[j] == 0 && hasX[j]) {
                count++;
            }
        }
    }
    
    return count;
}
