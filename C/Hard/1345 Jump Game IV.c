/*
Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You do not need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
 

Constraints:

1 <= arr.length <= 5 * 104
-108 <= arr[i] <= 108
  */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int val;
    int idx;
} Node;

// Comparator to sort by value, then by index
int compare(const void* a, const void* b) {
    Node* n1 = (Node*)a;
    Node* n2 = (Node*)b;
    if (n1->val != n2->val) {
        return (n1->val > n2->val) - (n1->val < n2->val);
    }
    return n1->idx - n2->idx;
}

int minJumps(int* arr, int arrSize) {
    if (arrSize <= 1) return 0;

    Node* nodes = (Node*)malloc(arrSize * sizeof(Node));
    for (int i = 0; i < arrSize; i++) {
        nodes[i].val = arr[i];
        nodes[i].idx = i;
    }
    qsort(nodes, arrSize, sizeof(Node), compare);

    // Arrays to map an original index directly to its sorted group details
    int* head = (int*)malloc(arrSize * sizeof(int));
    int* count = (int*)malloc(arrSize * sizeof(int));
    bool* groupVisited = (bool*)calloc(arrSize, sizeof(bool));

    // O(N) single-pass block processing to calculate head and count
    int i = 0;
    while (i < arrSize) {
        int startIdx = i;
        while (i < arrSize && nodes[i].val == nodes[startIdx].val) {
            i++;
        }
        int totalCount = i - startIdx;
        
        // Map all elements belonging to this value group back to their original positions
        for (int j = startIdx; j < i; j++) {
            int originalIdx = nodes[j].idx;
            head[originalIdx] = startIdx;
            count[originalIdx] = totalCount;
        }
    }

    // BFS Queue Setup
    int* queue = (int*)malloc(arrSize * sizeof(int));
    bool* visited = (bool*)calloc(arrSize, sizeof(bool));
    int front = 0, rear = 0;

    queue[rear++] = 0;
    visited[0] = true;
    int steps = 0;

    while (front < rear) {
        int currentSize = rear - front;
        for (int k = 0; k < currentSize; k++) {
            int idx = queue[front++];

            if (idx == arrSize - 1) {
                free(nodes); free(head); free(count); free(groupVisited); free(queue); free(visited);
                return steps;
            }

            // Option 1: Jump Forward
            if (idx + 1 < arrSize && !visited[idx + 1]) {
                visited[idx + 1] = true;
                queue[rear++] = idx + 1;
            }

            // Option 2: Jump Backward
            if (idx - 1 >= 0 && !visited[idx - 1]) {
                visited[idx - 1] = true;
                queue[rear++] = idx - 1;
            }

            // Option 3: Jump to same value indices
            int startPos = head[idx];
            if (!groupVisited[startPos]) {
                int totalElements = count[idx];
                for (int p = 0; p < totalElements; p++) {
                    int nextIdx = nodes[startPos + p].idx;
                    if (!visited[nextIdx]) {
                        visited[nextIdx] = true;
                        queue[rear++] = nextIdx;
                    }
                }
                groupVisited[startPos] = true; // Block further checks for this value group
            }
        }
        steps++;
    }

    free(nodes); free(head); free(count); free(groupVisited); free(queue); free(visited);
    return -1;
}
