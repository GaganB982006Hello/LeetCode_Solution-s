/*
You are given an array of positive integers nums.

You need to select a subset of nums which satisfies the following condition:

You can place the selected elements in a 0-indexed array such that it follows the pattern: [x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x] (Note that k can be be any non-negative power of 2). For example, [2, 4, 16, 4, 2] and [3, 9, 3] follow the pattern while [2, 4, 8, 4, 2] does not.
Return the maximum number of elements in a subset that satisfies these conditions.

 

Example 1:

Input: nums = [5,4,1,2,2]
Output: 3
Explanation: We can select the subset {4,2,2}, which can be placed in the array as [2,4,2] which follows the pattern and 22 == 4. Hence the answer is 3.
Example 2:

Input: nums = [1,3,2,4]
Output: 1
Explanation: We can select the subset {1}, which can be placed in the array as [1] which follows the pattern. Hence the answer is 1. Note that we could have also selected the subsets {2}, {3}, or {4}, there may be multiple subsets which provide the same answer. 
 

Constraints:

2 <= nums.length <= 105
1 <= nums[i] <= 109
*/

#include <stdlib.h>

int compare(const void *a, const void *b) {
    long long diff = *(long long*)a - *(long long*)b;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

typedef struct {
    long long val;
    int count;
} Element;

// Helper to find the frequency using Binary Search
int find_count(Element* unique_nums, int size, long long target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (unique_nums[mid].val == target) {
            return unique_nums[mid].count;
        } else if (unique_nums[mid].val < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

int maximumLength(int* nums, int numsSize) {
    long long* sorted_nums = (long long*)malloc(numsSize * sizeof(long long));
    for (int i = 0; i < numsSize; i++) {
        sorted_nums[i] = nums[i];
    }
    
    // Sort array to easily count frequencies and use binary search later
    qsort(sorted_nums, numsSize, sizeof(long long), compare);
    
    Element* unique_nums = (Element*)malloc(numsSize * sizeof(Element));
    int unique_size = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (i == 0 || sorted_nums[i] != sorted_nums[i - 1]) {
            unique_nums[unique_size].val = sorted_nums[i];
            unique_nums[unique_size].count = 1;
            unique_size++;
        } else {
            unique_nums[unique_size - 1].count++;
        }
    }
    
    int ans = 1;
    
    for (int i = 0; i < unique_size; i++) {
        long long x = unique_nums[i].val;
        
        // Handle special case for 1
        if (x == 1) {
            int c = unique_nums[i].count;
            if (c % 2 == 0) c--;
            if (c > ans) ans = c;
            continue;
        }
        
        long long curr = x;
        int curr_len = 0;
        
        while (find_count(unique_nums, unique_size, curr) >= 2 && find_count(unique_nums, unique_size, curr * curr) >= 1) {
            curr_len += 2;
            curr = curr * curr;
        }
        
        curr_len += 1;
        if (curr_len > ans) ans = curr_len;
    }
    
    free(sorted_nums);
    free(unique_nums);
    return ans;
}
