/*
You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.

You are also given an integer array nums of length n and an integer maxDiff.

An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).

You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.

Return an array answer, where answer[i] is the result of the ith query.

Note: The edges between the nodes are unweighted.

 

Example 1:

Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]

Output: [1,1]

Explanation:

The resulting graph is:



Query	Shortest Path	Minimum Distance
[0, 3]	0 → 3	1
[2, 4]	2 → 4	1
Thus, the output is [1, 1].

Example 2:

Input: n = 5, nums = [5,3,1,9,10], maxDiff = 2, queries = [[0,1],[0,2],[2,3],[4,3]]

Output: [1,2,-1,1]

Explanation:

The resulting graph is:



Query	Shortest Path	Minimum Distance
[0, 1]	0 → 1	1
[0, 2]	0 → 1 → 2	2
[2, 3]	None	-1
[4, 3]	3 → 4	1
Thus, the output is [1, 2, -1, 1].

Example 3:

Input: n = 3, nums = [3,6,1], maxDiff = 1, queries = [[0,0],[0,1],[1,2]]

Output: [0,-1,-1]

Explanation:

There are no edges between any two nodes because:

Nodes 0 and 1: |nums[0] - nums[1]| = |3 - 6| = 3 > 1
Nodes 0 and 2: |nums[0] - nums[2]| = |3 - 1| = 2 > 1
Nodes 1 and 2: |nums[1] - nums[2]| = |6 - 1| = 5 > 1
Thus, no node can reach any other node, and the output is [0, -1, -1].

 

Constraints:

1 <= n == nums.length <= 105
0 <= nums[i] <= 105
0 <= maxDiff <= 105
1 <= queries.length <= 105
queries[i] == [ui, vi]
0 <= ui, vi < n
  */
#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int cmp(const void *a, const void *b) {
    return ((Node*)a)->val - ((Node*)b)->val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    Node* arr = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].idx = i;
    }
    
    qsort(arr, n, sizeof(Node), cmp);
    
    int* pos = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        pos[arr[i].idx] = i;
    }
    
    int LOG = 18;
    int** up = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        up[i] = (int*)malloc(LOG * sizeof(int));
    }
    
    int right = 0;
    for (int i = 0; i < n; i++) {
        while (right + 1 < n && arr[right + 1].val - arr[i].val <= maxDiff) {
            right++;
        }
        up[i][0] = right;
    }
    
    for (int k = 1; k < LOG; k++) {
        for (int i = 0; i < n; i++) {
            up[i][k] = up[up[i][k-1]][k-1];
        }
    }
    
    *returnSize = queriesSize;
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    
    for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];
        int x = pos[u];
        int y = pos[v];
        
        if (x == y) {
            ans[i] = 0;
            continue;
        }
        if (x > y) {
            int temp = x; 
            x = y; 
            y = temp;
        }
        
        if (up[x][LOG - 1] < y) {
            ans[i] = -1;
            continue;
        }
        
        int steps = 0;
        int curr = x;
        for (int k = LOG - 1; k >= 0; k--) {
            if (up[curr][k] < y) {
                curr = up[curr][k];
                steps += (1 << k);
            }
        }
        ans[i] = steps + 1;
    }
    
    // Free allocated memory
    free(arr);
    free(pos);
    for (int i = 0; i < n; i++) {
        free(up[i]);
    }
    free(up);
    
    return ans;
}
