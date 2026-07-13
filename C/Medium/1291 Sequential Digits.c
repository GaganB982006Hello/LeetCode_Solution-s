/*
Medium
Topics
premium lock icon
Companies
Hint
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

 

Example 1:

Input: low = 100, high = 300
Output: [123,234]
Example 2:

Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]
 

Constraints:

10 <= low <= high <= 10^9
  */

#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    // Max combinations: 8+7+6+5+4+3+2+1 = 36
    int* ans = (int*)malloc(36 * sizeof(int)); 
    *returnSize = 0;
    
    char digits[] = "123456789";
    
    // Check lengths from 2 to 9
    for (int len = 2; len <= 9; len++) {
        for (int i = 0; i <= 9 - len; i++) {
            int num = 0;
            // Build the integer manually
            for (int j = 0; j < len; j++) {
                num = num * 10 + (digits[i + j] - '0');
            }
            if (num >= low && num <= high) {
                ans[(*returnSize)++] = num;
            }
        }
    }
    
    return ans;
}
