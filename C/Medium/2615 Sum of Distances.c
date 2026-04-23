/*
You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.

Return the array arr.

 

Example 1:

Input: nums = [1,3,1,1,2]
Output: [5,0,3,4,0]
Explanation: 
When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
When i = 1, arr[1] = 0 because there is no other index with value 3.
When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
When i = 4, arr[4] = 0 because there is no other index with value 2. 

Example 2:

Input: nums = [0,5,3]
Output: [0,0,0]
Explanation: Since each element in nums is distinct, arr[i] = 0 for all i.
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
*/

#include <stdlib.h>

typedef struct {
    int val;
    int idx;
} Node;

int compare(const void* a, const void* b) {
    Node* n1 = (Node*)a;
    Node* n2 = (Node*)b;
    if (n1->val != n2->val) return n1->val - n2->val;
    return n1->idx - n2->idx;
}

long long* distance(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    long long* arr = (long long*)calloc(numsSize, sizeof(long long));
    Node* nodes = (Node*)malloc(numsSize * sizeof(Node));

    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].idx = i;
    }

    qsort(nodes, numsSize, sizeof(Node), compare);

    int i = 0;
    while (i < numsSize) {
        int j = i;
        long long totalSum = 0;
        // Find the range of identical values
        while (j < numsSize && nodes[j].val == nodes[i].val) {
            totalSum += nodes[j].idx;
            j++;
        }

        long long prefixSum = 0;
        int count = j - i;
        for (int k = 0; k < count; k++) {
            int currIdx = nodes[i + k].idx;
            prefixSum += currIdx;
            // Left distances + Right distances
            // (k * currIdx - (prefixSum - currIdx)) + ((totalSum - prefixSum) - (count - 1 - k) * currIdx)
            arr[currIdx] = (1LL * k * currIdx - (prefixSum - currIdx)) + 
                           ((totalSum - prefixSum) - 1LL * (count - 1 - k) * currIdx);
        }
        i = j;
    }

    free(nodes);
    return arr;
}
