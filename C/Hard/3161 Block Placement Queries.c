/*
There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

You are given a 2D array queries, which contains two types of queries:

For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

 

Example 1:

Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]

Output: [false,true,true]

Explanation:



For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

Example 2:

Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]

Output: [true,true,false]

Explanation:



Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.
 

Constraints:

1 <= queries.length <= 15 * 104
2 <= queries[i].length <= 3
1 <= queries[i][0] <= 2
1 <= x, sz <= min(5 * 104, 3 * queries.length)
The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
The input is generated such that there is at least one query of type 2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Segment Tree Node
typedef struct {
    int max_gap;
    int min_val;
    int max_val;
} Node;

Node* tree;

// Combine two adjacent intervals
Node merge(Node L, Node R) {
    if (L.min_val == -1) return R; // Empty left child
    if (R.min_val == -1) return L; // Empty right child

    Node res;
    // 1. Best gap is at least the best gap from either child
    res.max_gap = L.max_gap > R.max_gap ? L.max_gap : R.max_gap;
    
    // 2. Check the gap formed right between the two children
    int gap = R.min_val - L.max_val;
    if (gap > res.max_gap) {
        res.max_gap = gap;
    }
    
    // 3. New interval boundaries
    res.min_val = L.min_val;
    res.max_val = R.max_val;
    
    return res;
}

// Initialize tree empty
void build(int node, int start, int end) {
    tree[node].max_gap = 0;
    tree[node].min_val = -1;
    tree[node].max_val = -1;
    
    if (start == end) return;
    
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
}

// Insert an obstacle at coordinate `idx`
void update(int node, int start, int end, int idx) {
    if (start == end) {
        tree[node].max_gap = 0;
        tree[node].min_val = idx;
        tree[node].max_val = idx;
        return;
    }
    
    int mid = start + (end - start) / 2;
    if (idx <= mid) {
        update(2 * node, start, mid, idx);
    } else {
        update(2 * node + 1, mid + 1, end, idx);
    }
    
    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

// Retrieve interval states spanning [l, r]
Node query(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        Node empty = {0, -1, -1};
        return empty;
    }
    if (l <= start && end <= r) {
        return tree[node];
    }
    
    int mid = start + (end - start) / 2;
    Node L = query(2 * node, start, mid, l, r);
    Node R = query(2 * node + 1, mid + 1, end, l, r);
    
    return merge(L, R);
}

bool* getResults(int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Dynamically size the space boundary by inspecting maximum x
    int max_x = 0;
    for (int i = 0; i < queriesSize; i++) {
        if (queries[i][1] > max_x) {
            max_x = queries[i][1];
        }
    }
    max_x += 2; // small buffer safety
    
    tree = (Node*)malloc(4 * max_x * sizeof(Node));
    build(1, 0, max_x - 1);
    
    // Always start with an obstacle at 0
    update(1, 0, max_x - 1, 0); 
    
    bool* results = (bool*)malloc(queriesSize * sizeof(bool));
    int res_cnt = 0;
    
    for (int i = 0; i < queriesSize; i++) {
        if (queries[i][0] == 1) {
            // Type 1: Add obstacle
            int x = queries[i][1];
            update(1, 0, max_x - 1, x);
        } else {
            // Type 2: Check sizing
            int x = queries[i][1];
            int sz = queries[i][2];
            
            Node res = query(1, 0, max_x - 1, 0, x);
            
            // Tail gap calculation: distance from the very last known obstacle up to boundary x
            int tail_gap = x - res.max_val;
            
            // True maximum available block space
            int max_available = res.max_gap > tail_gap ? res.max_gap : tail_gap;
            
            results[res_cnt++] = (max_available >= sz);
        }
    }
    
    *returnSize = res_cnt;
    free(tree);
    return results;
}
