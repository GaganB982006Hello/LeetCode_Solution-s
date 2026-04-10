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

1 <= n == nums.length <= 100
1 <= nums[i] <= n
*/

#include <stdlib.h>

#define SIZE 10007 // Hash table size

typedef struct Node {
    int key;
    int first_idx;
    int second_idx;
    struct Node* next;
} Node;

// Simple hash function
int get_hash(int key) {
    int h = key % SIZE;
    return (h < 0) ? h + SIZE : h;
}

int minimumDistance(int* nums, int numsSize) {
    Node* hash_table[SIZE] = {NULL}; // Local initialization
    int min_dist = -1;

    for (int i = 0; i < numsSize; i++) {
        int h = get_hash(nums[i]);
        Node* curr = hash_table[h];
        
        while (curr != NULL && curr->key != nums[i]) {
            curr = curr->next;
        }

        if (curr == NULL) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->key = nums[i];
            newNode->first_idx = i;
            newNode->second_idx = -1;
            newNode->next = hash_table[h];
            hash_table[h] = newNode;
        } else {
            if (curr->second_idx == -1) {
                curr->second_idx = i;
            } else {
                int current_span = 2 * (i - curr->first_idx);
                if (min_dist == -1 || current_span < min_dist) {
                    min_dist = current_span;
                }
                // Slide the window
                curr->first_idx = curr->second_idx;
                curr->second_idx = i;
            }
        }
    }

    // Optional: Clean up memory before returning
    // In many competitive platforms, you can skip this to save time
    return min_dist;
}
