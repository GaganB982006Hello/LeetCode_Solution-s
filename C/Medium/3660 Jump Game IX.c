/*
You are given an integer array nums.

From any index i, you can jump to another index j under the following rules:

Jump to index j where j > i is allowed only if nums[j] < nums[i].
Jump to index j where j < i is allowed only if nums[j] > nums[i].
For each index i, find the maximum value in nums that can be reached by following any sequence of valid jumps starting at i.

Return an array ans where ans[i] is the maximum value reachable starting from index i.

 

Example 1:

Input: nums = [2,1,3]

Output: [2,2,3]

Explanation:

For i = 0: No jump increases the value.
For i = 1: Jump to j = 0 as nums[j] = 2 is greater than nums[i].
For i = 2: Since nums[2] = 3 is the maximum value in nums, no jump increases the value.
Thus, ans = [2, 2, 3].

Example 2:

Input: nums = [2,3,1]

Output: [3,3,3]

Explanation:

For i = 0: Jump forward to j = 2 as nums[j] = 1 is less than nums[i] = 2, then from i = 2 jump to j = 1 as nums[j] = 3 is greater than nums[2].
For i = 1: Since nums[1] = 3 is the maximum value in nums, no jump increases the value.
For i = 2: Jump to j = 1 as nums[j] = 3 is greater than nums[2] = 1.
Thus, ans = [3, 3, 3].

 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
  */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxValue(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(sizeof(int) * numsSize);
    *returnSize = numsSize;
    
    int* prefixMax = (int*)malloc(sizeof(int) * numsSize);
    int* suffixMin = (int*)malloc(sizeof(int) * numsSize);
    
    prefixMax[0] = nums[0];
    for (int i = 1; i < numsSize; i++) {
        prefixMax[i] = (nums[i] > prefixMax[i-1]) ? nums[i] : prefixMax[i-1];
    }
    
    suffixMin[numsSize - 1] = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--) {
        suffixMin[i] = (nums[i] < suffixMin[i+1]) ? nums[i] : suffixMin[i+1];
    }
    
    int l = 0;
    while (l < numsSize) {
        int r = l;
        int compMax = nums[l];
        while (r + 1 < numsSize && prefixMax[r] > suffixMin[r + 1]) {
            r++;
            if (nums[r] > compMax) compMax = nums[r];
        }
        for (int i = l; i <= r; i++) {
            ans[i] = compMax;
        }
        l = r + 1;
    }
    
    free(prefixMax);
    free(suffixMin);
    return ans;
}
