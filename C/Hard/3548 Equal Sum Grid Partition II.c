#include <stdbool.h>
#include <stdlib.h>

typedef long long ll;

// Frequency array for values 0-100000
int f1[100001];
int f2[100001];

bool check(ll s1, ll s2, int* freq, int h, int w, int** grid, int r1, int r2, int c1, int c2) {
    if (s1 == s2) return true;
    ll diff = s1 - s2;
    if (diff <= 0 || diff > 100000) return false;
    int d = (int)diff;

    // Check if the value exists in the section's frequency map
    if (freq[d] == 0) return false;

    // Connectivity Rule:
    // 1. If 2D (h > 1 && w > 1), any cell works.
    if (h > 1 && w > 1) return true;
    // 2. If 1D, only endpoints of the strip work.
    if (h == 1) return grid[r1][c1] == d || grid[r1][c2] == d;
    if (w == 1) return grid[r1][c1] == d || grid[r2][c1] == d;
    
    return false;
}

void clear_freq() {
    for (int i = 0; i <= 100000; i++) f1[i] = f2[i] = 0;
}

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    ll totalSum = 0;
    
    clear_freq();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            totalSum += grid[i][j];
            f2[grid[i][j]]++; // Initially all elements are in the "bottom/right" section
        }
    }

    // --- Horizontal Cuts ---
    ll topSum = 0;
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n; j++) {
            int val = grid[i][j];
            topSum += val;
            f1[val]++;
            f2[val]--;
        }
        ll botSum = totalSum - topSum;
        if (check(topSum, botSum, f1, i + 1, n, grid, 0, i, 0, n - 1) ||
            check(botSum, topSum, f2, m - 1 - i, n, grid, i + 1, m - 1, 0, n - 1)) return true;
    }

    // --- Vertical Cuts ---
    // Reset frequencies for vertical pass
    clear_freq();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) f2[grid[i][j]]++;
    }

    ll leftSum = 0;
    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < m; i++) {
            int val = grid[i][j];
            leftSum += val;
            f1[val]++;
            f2[val]--;
        }
        ll rightSum = totalSum - leftSum;
        if (check(leftSum, rightSum, f1, m, j + 1, grid, 0, m - 1, 0, j) ||
            check(rightSum, leftSum, f2, m, n - 1 - j, grid, 0, m - 1, j + 1, n - 1)) return true;
    }

    return false;
}
