/*
You want to build n new buildings in a city. The new buildings will be built in a line and are labeled from 1 to n.

However, there are city restrictions on the heights of the new buildings:

The height of each building must be a non-negative integer.
The height of the first building must be 0.
The height difference between any two adjacent buildings cannot exceed 1.
Additionally, there are city restrictions on the maximum height of specific buildings. These restrictions are given as a 2D integer array restrictions where restrictions[i] = [idi, maxHeighti] indicates that building idi must have a height less than or equal to maxHeighti.

It is guaranteed that each building will appear at most once in restrictions, and building 1 will not be in restrictions.

Return the maximum possible height of the tallest building.

 

Example 1:


Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,1,2], and the tallest building has a height of 2.
Example 2:


Input: n = 6, restrictions = []
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,4,5], and the tallest building has a height of 5.
Example 3:


Input: n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
Output: 5
Explanation: The green area in the image indicates the maximum allowed height for each building.
We can build the buildings with heights [0,1,2,3,3,4,4,5,4,3], and the tallest building has a height of 5.
 

Constraints:

2 <= n <= 109
0 <= restrictions.length <= min(n - 1, 105)
2 <= idi <= n
idi is unique.
0 <= maxHeighti <= 109
*/

#include <stdlib.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Comparator function to sort restrictions by building ID
int cmp(const void *a, const void *b) {
    int *pa = *(int **)a;
    int *pb = *(int **)b;
    return pa[0] - pb[0];
}

int maxBuilding(int n, int** restrictions, int restrictionsSize, int* restrictionsColSize) {
    int m = restrictionsSize;
    
    // Allocate memory for constraints + 1 (for the default building 1)
    int** arr = (int**)malloc((m + 1) * sizeof(int*));
    for (int i = 0; i < m; ++i) {
        arr[i] = (int*)malloc(2 * sizeof(int));
        arr[i][0] = restrictions[i][0];
        arr[i][1] = restrictions[i][1];
    }
    arr[m] = (int*)malloc(2 * sizeof(int));
    arr[m][0] = 1;
    arr[m][1] = 0;
    
    // Sort the array by building id
    qsort(arr, m + 1, sizeof(int*), cmp);
    
    // Left-to-right pass
    for (int i = 1; i <= m; ++i) {
        arr[i][1] = MIN(arr[i][1], arr[i-1][1] + arr[i][0] - arr[i-1][0]);
    }
    
    // Right-to-left pass
    for (int i = m - 1; i >= 0; --i) {
        arr[i][1] = MIN(arr[i][1], arr[i+1][1] + arr[i+1][0] - arr[i][0]);
    }
    
    int ans = 0;
    
    // Check maximum height achievable between each pair of adjacent restrictions
    for (int i = 1; i <= m; ++i) {
        int x1 = arr[i-1][0], h1 = arr[i-1][1];
        int x2 = arr[i][0], h2 = arr[i][1];
        
        // Cast to long long to avoid overflow when calculating peak
        ans = MAX(ans, (int)(((long long)h1 + h2 + x2 - x1) / 2));
    }
    
    // Calculate the growth from the last restriction to the end 'n'
    ans = MAX(ans, arr[m][1] + (n - arr[m][0]));
    
    // Free allocated memory to prevent leaks
    for(int i = 0; i <= m; i++) {
        free(arr[i]);
    }
    free(arr);
    
    return ans;
}
