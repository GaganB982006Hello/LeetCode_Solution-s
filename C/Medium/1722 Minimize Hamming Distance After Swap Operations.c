/*
You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.

The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).

Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.

 

Example 1:

Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
Output: 1
Explanation: source can be transformed the following way:
- Swap indices 0 and 1: source = [2,1,3,4]
- Swap indices 2 and 3: source = [2,1,4,3]
The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
Example 2:

Input: source = [1,2,3,4], target = [1,3,2,4], allowedSwaps = []
Output: 2
Explanation: There are no allowed swaps.
The Hamming distance of source and target is 2 as they differ in 2 positions: index 1 and index 2.
Example 3:

Input: source = [5,1,2,4,3], target = [1,5,4,2,3], allowedSwaps = [[0,4],[4,2],[1,3],[1,4]]
Output: 0
 

Constraints:

n == source.length == target.length
1 <= n <= 105
1 <= source[i], target[i] <= 105
0 <= allowedSwaps.length <= 105
allowedSwaps[i].length == 2
0 <= ai, bi <= n - 1
ai != bi
*/

#include <stdlib.h>
#include <string.h>

/**
 * Union-Find: Find with Path Compression.
 * Time complexity: O(alpha(N))
 */
int find(int* parent, int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

/**
 * Union-Find: Union by Rank to keep the tree flat.
 */
void unite(int* parent, int* rank, int i, int j) {
    int root_i = find(parent, i);
    int root_j = find(parent, j);
    if (root_i != root_j) {
        if (rank[root_i] < rank[root_j]) {
            parent[root_i] = root_j;
        } else {
            parent[root_j] = root_i;
            if (rank[root_i] == rank[root_j]) rank[root_i]++;
        }
    }
}

/**
 * Comparison function for qsort to sort elements within components.
 */
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minimumHammingDistance(int* source, int sourceSize, int* target, int targetSize, int** allowedSwaps, int allowedSwapsSize, int* allowedSwapsColSize) {
    int n = sourceSize;
    int* parent = (int*)malloc(n * sizeof(int));
    int* rank = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    // 1. Group indices into connected components based on allowed swaps
    for (int i = 0; i < allowedSwapsSize; i++) {
        unite(parent, rank, allowedSwaps[i][0], allowedSwaps[i][1]);
    }

    // 2. Group source and target elements by their root component
    // Using calloc here is CRITICAL so that initial reallocs receive a NULL pointer.
    int** compSource = (int**)calloc(n, sizeof(int*));
    int** compTarget = (int**)calloc(n, sizeof(int*));
    int* compSizes = (int*)calloc(n, sizeof(int));
    int* compCapacity = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        int root = find(parent, i);
        if (compSizes[root] == compCapacity[root]) {
            compCapacity[root] = (compCapacity[root] == 0) ? 2 : compCapacity[root] * 2;
            compSource[root] = (int*)realloc(compSource[root], compCapacity[root] * sizeof(int));
            compTarget[root] = (int*)realloc(compTarget[root], compCapacity[root] * sizeof(int));
        }
        compSource[root][compSizes[root]] = source[i];
        compTarget[root][compSizes[root]] = target[i];
        compSizes[root]++;
    }

    // 3. For each component, count element matches using sorting and two-pointers
    int totalMatches = 0;
    for (int i = 0; i < n; i++) {
        if (compSizes[i] > 0) {
            qsort(compSource[i], compSizes[i], sizeof(int), compare);
            qsort(compTarget[i], compSizes[i], sizeof(int), compare);
            
            int s = 0, t = 0;
            while (s < compSizes[i] && t < compSizes[i]) {
                if (compSource[i][s] == compTarget[i][t]) {
                    totalMatches++;
                    s++;
                    t++;
                } else if (compSource[i][s] < compTarget[i][t]) {
                    s++;
                } else {
                    t++;
                }
            }
            // Free individual component buffers after processing
            free(compSource[i]);
            free(compTarget[i]);
        }
    }

    // 4. Cleanup and return result
    free(parent);
    free(rank);
    free(compSource);
    free(compTarget);
    free(compSizes);
    free(compCapacity);

    // Hamming distance = total elements - elements that could be matched
    return n - totalMatches;
}
