/*
You are given an integer array nums of length n and an integer k.

You must select exactly k distinct non-empty subarrays nums[l..r] of nums. Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

 

Example 1:

Input: nums = [1,3,2], k = 2

Output: 4

Explanation:

One optimal approach is:

Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:

Input: nums = [4,2,5,1], k = 3

Output: 12

Explanation:

One optimal approach is:

Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.

 

Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​4
0 <= nums[i] <= 109
1 <= k <= min(105, n * (n + 1) / 2)
  */

#include <stdlib.h>

// Struct to hold the value and the boundaries of the subarray
typedef struct {
    long long val;
    int l;
    int r;
} HeapNode;

// Custom Max-Heap Structure
typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity) {
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap* h, HeapNode node) {
    if (h->size == h->capacity) return; 
    int i = h->size;
    h->data[i] = node;
    h->size++;
    
    // Bubble up
    while (i != 0 && h->data[(i - 1) / 2].val < h->data[i].val) {
        swapNodes(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode pop(MaxHeap* h) {
    if (h->size <= 0) {
        HeapNode empty = {0, 0, 0};
        return empty;
    }
    if (h->size == 1) {
        h->size--;
        return h->data[0];
    }
    
    HeapNode root = h->data[0];
    h->data[0] = h->data[h->size - 1];
    h->size--;
    
    // Bubble down
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;
        
        if (left < h->size && h->data[left].val > h->data[largest].val)
            largest = left;
        if (right < h->size && h->data[right].val > h->data[largest].val)
            largest = right;
            
        if (largest != i) {
            swapNodes(&h->data[i], &h->data[largest]);
            i = largest;
        } else {
            break;
        }
    }
    return root;
}

void freeHeap(MaxHeap* h) {
    free(h->data);
    free(h);
}

// Helper function to query the sparse table in O(1)
long long getVal(int l, int r, int** maxSt, int** minSt) {
    int len = r - l + 1;
    // __builtin_clz counts leading zeros. 31 - clz(len) is equivalent to floor(log2(len))
    int j = 31 - __builtin_clz(len); 
    
    int max_val = maxSt[l][j] > maxSt[r - (1 << j) + 1][j] ? maxSt[l][j] : maxSt[r - (1 << j) + 1][j];
    int min_val = minSt[l][j] < minSt[r - (1 << j) + 1][j] ? minSt[l][j] : minSt[r - (1 << j) + 1][j];
    
    return (long long)max_val - min_val;
}

long long maxTotalValue(int* nums, int numsSize, int k) {
    int n = numsSize;
    int log = 32 - __builtin_clz(n);
    
    // Allocate sparse tables dynamically
    int** maxSt = (int**)malloc(n * sizeof(int*));
    int** minSt = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        maxSt[i] = (int*)malloc(log * sizeof(int));
        minSt[i] = (int*)malloc(log * sizeof(int));
        maxSt[i][0] = nums[i];
        minSt[i][0] = nums[i];
    }

    // Build sparse tables
    for (int j = 1; j < log; j++) {
        for (int i = 0; i + (1 << j) <= n; i++) {
            int leftMax = maxSt[i][j - 1];
            int rightMax = maxSt[i + (1 << (j - 1))][j - 1];
            maxSt[i][j] = leftMax > rightMax ? leftMax : rightMax;
            
            int leftMin = minSt[i][j - 1];
            int rightMin = minSt[i + (1 << (j - 1))][j - 1];
            minSt[i][j] = leftMin < rightMin ? leftMin : rightMin;
        }
    }

    // Initialize the max-heap. 
    // Capacity only needs to be `n` because we never have more than `n` elements in the heap simultaneously.
    MaxHeap* pq = createHeap(n);
    
    for (int i = 0; i < n; ++i) {
        HeapNode node = {getVal(i, n - 1, maxSt, minSt), i, n - 1};
        push(pq, node);
    }

    long long total = 0;
    
    // Greedily grab the top k combinations
    for (int i = 0; i < k; ++i) {
        if (pq->size == 0) break;
        
        HeapNode top = pop(pq);
        total += top.val;
        
        // If we can shrink the subarray from the right, calculate its new value and push
        if (top.r > top.l) {
            HeapNode nextNode = {getVal(top.l, top.r - 1, maxSt, minSt), top.l, top.r - 1};
            push(pq, nextNode);
        }
    }

    // Clean up allocated memory to prevent leaks
    for (int i = 0; i < n; i++) {
        free(maxSt[i]);
        free(minSt[i]);
    }
    free(maxSt);
    free(minSt);
    freeHeap(pq);

    return total;
}
