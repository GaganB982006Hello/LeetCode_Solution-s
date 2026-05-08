/*
You are given an integer array nums of length n.

You start at index 0, and your goal is to reach index n - 1.

From any index i, you may perform one of the following operations:

Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
Return the minimum number of jumps required to reach index n - 1.

 

Example 1:

Input: nums = [1,2,4,6]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index 1.
At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
Thus, the answer is 2.

Example 2:

Input: nums = [2,3,4,7,9]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index i = 1.
At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
Thus, the answer is 2.

Example 3:

Input: nums = [4,6,5,8]

Output: 3

Explanation:

Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= 106
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VAL 1000001

// Global/Static Sieve for Smallest Prime Factor (SPF)
int spf[MAX_VAL];
bool sieve_done = false;

void sieve() {
    if (sieve_done) return;
    for (int i = 0; i < MAX_VAL; i++) spf[i] = i;
    for (int i = 2; i * i < MAX_VAL; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX_VAL; j += i)
                if (spf[j] == j) spf[j] = i;
        }
    }
    sieve_done = true;
}

// Linked list node to store indices in prime "buckets"
typedef struct Node {
    int index;
    struct Node* next;
} Node;

int minJumps(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;
    sieve();

    // 1. Pre-process Prime Buckets
    // Use calloc to initialize all pointers to NULL
    Node** prime_buckets = (Node**)calloc(MAX_VAL, sizeof(Node*));
    for (int i = 0; i < numsSize; i++) {
        int temp = nums[i];
        while (temp > 1) {
            int p = spf[temp];
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->index = i;
            newNode->next = prime_buckets[p];
            prime_buckets[p] = newNode;
            // Remove all instances of this prime factor
            while (temp % p == 0) temp /= p;
        }
    }

    // 2. BFS Setup
    int* queue = (int*)malloc(numsSize * sizeof(int));
    bool* visited_idx = (bool*)calloc(numsSize, sizeof(bool));
    bool* visited_primes = (bool*)calloc(MAX_VAL, sizeof(bool));
    
    int head = 0, tail = 0;
    queue[tail++] = 0;
    visited_idx[0] = true;
    int jumps = 0;

    // 3. BFS Execution
    while (head < tail) {
        int level_size = tail - head;
        while (level_size--) {
            int curr = queue[head++];
            if (curr == numsSize - 1) {
                // Free temporary BFS memory before returning
                free(queue); free(visited_idx); free(visited_primes);
                return jumps;
            }

            // Step A: Adjacent Jumps (+1, -1)
            int neighbors[] = {curr - 1, curr + 1};
            for (int k = 0; k < 2; k++) {
                int next = neighbors[k];
                if (next >= 0 && next < numsSize && !visited_idx[next]) {
                    visited_idx[next] = true;
                    queue[tail++] = next;
                }
            }

            // Step B: Prime Teleportation
            int val = nums[curr];
            // Only teleport if the current number itself is prime
            if (val > 1 && spf[val] == val && !visited_primes[val]) {
                visited_primes[val] = true;
                Node* currNode = prime_buckets[val];
                while (currNode) {
                    if (!visited_idx[currNode->index]) {
                        visited_idx[currNode->index] = true;
                        queue[tail++] = currNode->index;
                    }
                    currNode = currNode->next;
                }
            }
        }
        jumps++;
    }

    // Cleanup (Not strictly required for LC but good practice)
    free(queue); free(visited_idx); free(visited_primes);
    return -1;
}
            
        return -1
