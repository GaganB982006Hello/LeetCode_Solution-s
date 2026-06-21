/*
It is a sweltering summer day, and a boy wants to buy some ice cream bars.

At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible. 

Note: The boy can buy the ice cream bars in any order.

Return the maximum number of ice cream bars the boy can buy with coins coins.

You must solve the problem by counting sort.

 

Example 1:

Input: costs = [1,3,2,4,1], coins = 7
Output: 4
Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
Example 2:

Input: costs = [10,6,8,7,7,8], coins = 5
Output: 0
Explanation: The boy cannot afford any of the ice cream bars.
Example 3:

Input: costs = [1,6,3,1,2,5], coins = 20
Output: 6
Explanation: The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
 

Constraints:

costs.length == n
1 <= n <= 105
1 <= costs[i] <= 105
1 <= coins <= 108
  */

#include <stdlib.h>

int maxIceCream(int* costs, int costsSize, int coins) {
    int maxCost = 0;
    for (int i = 0; i < costsSize; i++) {
        if (costs[i] > maxCost) {
            maxCost = costs[i];
        }
    }
    
    // Allocate and initialize the frequency array with zeros
    int* count = (int*)calloc(maxCost + 1, sizeof(int));
    for (int i = 0; i < costsSize; i++) {
        count[costs[i]]++;
    }
    
    int iceCreams = 0;
    for (int i = 1; i <= maxCost; i++) {
        if (count[i] == 0) continue;
        if (coins < i) break;
        
        // Find how many we can afford vs how many exist
        int canAfford = coins / i;
        int buy = (count[i] < canAfford) ? count[i] : canAfford;
        
        iceCreams += buy;
        coins -= buy * i;
    }
    
    free(count); // Prevent memory leaks
    return iceCreams;
}
