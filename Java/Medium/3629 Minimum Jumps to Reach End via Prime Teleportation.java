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
import java.util.*;

class Solution {
    // Standard Sieve to find Smallest Prime Factor (SPF)
    private static final int MAX_VAL = 1000001;
    private static int[] spf = new int[MAX_VAL];
    static {
        for (int i = 2; i < MAX_VAL; i++) spf[i] = i;
        for (int i = 2; i * i < MAX_VAL; i++) {
            if (spf[i] == i) {
                for (int j = i * i; j < MAX_VAL; j += i)
                    if (spf[j] == j) spf[j] = i;
            }
        }
    }

    public int minJumps(int[] nums) {
        int n = nums.length;
        if (n == 1) return 0;

        // Map each prime to indices where nums[j] % p == 0
        Map<Integer, List<Integer>> primeToIndices = new HashMap<>();
        for (int i = 0; i < n; i++) {
            int temp = nums[i];
            while (temp > 1) {
                int p = spf[temp];
                primeToIndices.computeIfAbsent(p, k -> new ArrayList<>()).add(i);
                while (temp % p == 0) temp /= p;
            }
        }

        // BFS setup
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(0);
        boolean[] visitedIdx = new boolean[n];
        Set<Integer> visitedPrimes = new HashSet<>();
        visitedIdx[0] = true;
        
        int jumps = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int k = 0; k < size; k++) {
                int i = queue.poll();
                if (i == n - 1) return jumps;

                // 1. Adjacent Steps
                if (i + 1 < n && !visitedIdx[i + 1]) {
                    visitedIdx[i + 1] = true;
                    queue.offer(i + 1);
                }
                if (i - 1 >= 0 && !visitedIdx[i - 1]) {
                    visitedIdx[i - 1] = true;
                    queue.offer(i - 1);
                }

                // 2. Prime Teleportation
                // Check if nums[i] itself is prime
                if (isPrime(nums[i])) {
                    int p = nums[i];
                    if (!visitedPrimes.contains(p)) {
                        visitedPrimes.add(p);
                        if (primeToIndices.containsKey(p)) {
                            for (int nextIdx : primeToIndices.get(p)) {
                                if (!visitedIdx[nextIdx]) {
                                    visitedIdx[nextIdx] = true;
                                    queue.offer(nextIdx);
                                }
                            }
                            // Clear the bucket to avoid redundant checks
                            primeToIndices.get(p).clear();
                        }
                    }
                }
            }
            jumps++;
        }

        return -1;
    }

    private boolean isPrime(int n) {
        return n > 1 && spf[n] == n;
    }
}
