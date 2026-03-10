#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // Allocate memory for the two indices
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    // Check every possible pair
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    
    // Fallback if no pair is found
    *returnSize = 0;
    return NULL;
}
