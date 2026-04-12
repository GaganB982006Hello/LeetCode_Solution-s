/*
You are given an integer array nums.

A tuple (i, j, k) of 3 distinct indices is good if nums[i] == nums[j] == nums[k].

The distance of a good tuple is abs(i - j) + abs(j - k) + abs(k - i), where abs(x) denotes the absolute value of x.

Return an integer denoting the minimum possible distance of a good tuple. If no good tuples exist, return -1.

 

Example 1:

Input: nums = [1,2,1,1,3]

Output: 6

Explanation:

The minimum distance is achieved by the good tuple (0, 2, 3).

(0, 2, 3) is a good tuple because nums[0] == nums[2] == nums[3] == 1. Its distance is abs(0 - 2) + abs(2 - 3) + abs(3 - 0) = 2 + 1 + 3 = 6.

Example 2:

Input: nums = [1,1,2,3,2,1,2]

Output: 8

Explanation:

The minimum distance is achieved by the good tuple (2, 4, 6).

(2, 4, 6) is a good tuple because nums[2] == nums[4] == nums[6] == 2. Its distance is abs(2 - 4) + abs(4 - 6) + abs(6 - 2) = 2 + 2 + 4 = 8.

Example 3:

Input: nums = [1]

Output: -1

Explanation:

There are no good tuples. Therefore, the answer is -1.

 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= n
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minimumDistance(int* nums, int numsSize) {
    int n = numsSize;
    // 'last' stores the most recent index seen for a value
    // 'prev' stores the index before that, 'prev_prev' the one before that
    int* last = (int*)malloc((n + 1) * sizeof(int));
    int* prev = (int*)malloc((n + 1) * sizeof(int));
    
    for (int i = 0; i <= n; i++) {
        last[i] = -1;
        prev[i] = -1;
    }

    long long min_dist = LLONG_MAX;
    int found = 0;

    for (int i = 0; i < n; i++) {
        int val = nums[i];
        
        if (prev[val] != -1) {
            // We have at least 3 occurrences: prev[val], last[val], and current i
            long long current_dist = 2LL * (i - prev[val]);
            if (current_dist < min_dist) {
                min_dist = current_dist;
                found = 1;
            }
        }
        
        // Shift history: newest is i, middle is old last, oldest is old prev
        prev[val] = last[val];
        last[val] = i;
    }

    free(last);
    free(prev);

    return found ? (int)min_dist : -1;
}
