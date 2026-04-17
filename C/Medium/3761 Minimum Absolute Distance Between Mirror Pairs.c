/*
You are given an integer array nums.

A mirror pair is a pair of indices (i, j) such that:

0 <= i < j < nums.length, and
reverse(nums[i]) == nums[j], where reverse(x) denotes the integer formed by reversing the digits of x. Leading zeros are omitted after reversing, for example reverse(120) = 21.
Return the minimum absolute distance between the indices of any mirror pair. The absolute distance between indices i and j is abs(i - j).

If no mirror pair exists, return -1.

 

Example 1:

Input: nums = [12,21,45,33,54]

Output: 1

Explanation:

The mirror pairs are:

(0, 1) since reverse(nums[0]) = reverse(12) = 21 = nums[1], giving an absolute distance abs(0 - 1) = 1.
(2, 4) since reverse(nums[2]) = reverse(45) = 54 = nums[4], giving an absolute distance abs(2 - 4) = 2.
The minimum absolute distance among all pairs is 1.

Example 2:

Input: nums = [120,21]

Output: 1

Explanation:

There is only one mirror pair (0, 1) since reverse(nums[0]) = reverse(120) = 21 = nums[1].

The minimum absolute distance is 1.

Example 3:

Input: nums = [21,120]

Output: -1

Explanation:

There are no mirror pairs in the array.

 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109​​​​​​​
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Simple Hash Table Entry
typedef struct {
    int key;
    int value;
    int isSet;
} HashEntry;

// Helper to reverse an integer (handles leading zeros as per problem)
int reverseInt(int n) {
    long long rev = 0;
    while (n > 0) {
        rev = rev * 10 + (n % 10);
        n /= 10;
    }
    return (int)rev;
}

int minMirrorPairDistance(int* nums, int numsSize) {
    // Hash table size (roughly 2x the input size to reduce collisions)
    int tableSize = numsSize * 2;
    HashEntry* table = (HashEntry*)calloc(tableSize, sizeof(HashEntry));
    
    int minDist = -1;

    for (int j = 0; j < numsSize; j++) {
        int currentVal = nums[j];
        
        // 1. Check if current value exists in the map (as a target for a previous mirror)
        int h1 = abs(currentVal) % tableSize;
        while (table[h1].isSet) {
            if (table[h1].key == currentVal) {
                int dist = j - table[h1].value;
                if (minDist == -1 || dist < minDist) {
                    minDist = dist;
                }
                break; // Found the most recent index
            }
            h1 = (h1 + 1) % tableSize;
        }

        // 2. Calculate reverse and store/update in map
        int revVal = reverseInt(currentVal);
        int h2 = abs(revVal) % tableSize;
        while (table[h2].isSet && table[h2].key != revVal) {
            h2 = (h2 + 1) % tableSize;
        }
        table[h2].key = revVal;
        table[h2].value = j; // Update to the most recent index
        table[h2].isSet = 1;
    }

    free(table);
    return minDist;
}
