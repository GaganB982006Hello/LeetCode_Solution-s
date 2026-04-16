/*
You are given a circular array nums and an array queries.

For each query i, you have to find the following:

The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
Return an array answer of the same size as queries, where answer[i] represents the result for query i.

 

Example 1:

Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]

Output: [2,-1,3]

Explanation:

Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
Example 2:

Input: nums = [1,2,3,4], queries = [0,1,2,3]

Output: [-1,-1,-1,-1]

Explanation:

Each value in nums is unique, so no index shares the same value as the queried element. This results in -1 for all queries.

 

Constraints:

1 <= queries.length <= nums.length <= 105
1 <= nums[i] <= 106
0 <= queries[i] < nums.length
*/

#include <stdlib.h>
#include <math.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct {
    int val;
    int original_idx;
} Node;

// Sort by value first, then by index
int compareNodes(const void* a, const void* b) {
    Node* n1 = (Node*)a;
    Node* n2 = (Node*)b;
    if (n1->val != n2->val) return n1->val - n2->val;
    return n1->original_idx - n2->original_idx;
}

int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    *returnSize = queriesSize;
    int* result = (int*)malloc(queriesSize * sizeof(int));
    
    // Step 1: Create a list of nodes and sort them to group equal values
    Node* nodes = (Node*)malloc(numsSize * sizeof(Node));
    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].original_idx = i;
    }
    qsort(nodes, numsSize, sizeof(Node), compareNodes);

    // Step 2: For each query, find the range of indices with the same value
    for (int i = 0; i < queriesSize; i++) {
        int targetIdx = queries[i];
        int targetVal = nums[targetIdx];
        
        // Find the first occurrence of targetVal using binary search
        Node targetKey = {targetVal, -1};
        Node* first = NULL;
        int low = 0, high = numsSize - 1;
        int startPos = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nodes[mid].val >= targetVal) {
                if (nodes[mid].val == targetVal) startPos = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        
        // Find the last occurrence
        low = 0, high = numsSize - 1;
        int endPos = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nodes[mid].val <= targetVal) {
                if (nodes[mid].val == targetVal) endPos = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        int count = endPos - startPos + 1;
        if (count <= 1) {
            result[i] = -1;
            continue;
        }

        // Step 3: Find current targetIdx within this range
        int currentInSortedRange = -1;
        low = startPos, high = endPos;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nodes[mid].original_idx == targetIdx) {
                currentInSortedRange = mid;
                break;
            } else if (nodes[mid].original_idx < targetIdx) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        // Step 4: Circular neighbors in the sorted range
        int prevIdxPos = (currentInSortedRange - startPos - 1 + count) % count + startPos;
        int nextIdxPos = (currentInSortedRange - startPos + 1) % count + startPos;
        
        int prev = nodes[prevIdxPos].original_idx;
        int next = nodes[nextIdxPos].original_idx;
        
        // Distance calculation
        int d1 = abs(targetIdx - prev);
        if (numsSize - d1 < d1) d1 = numsSize - d1;
        
        int d2 = abs(targetIdx - next);
        if (numsSize - d2 < d2) d2 = numsSize - d2;
        
        result[i] = (d1 < d2) ? d1 : d2;
    }

    free(nodes);
    return result;
}
