/*
You are given an integer array nums of length n and an integer array queries.

Let gcdPairs denote an array obtained by calculating the GCD of all possible pairs (nums[i], nums[j]), where 0 <= i < j < n, and then sorting these values in ascending order.

For each query queries[i], you need to find the element at index queries[i] in gcdPairs.

Return an integer array answer, where answer[i] is the value at gcdPairs[queries[i]] for each query.

The term gcd(a, b) denotes the greatest common divisor of a and b.

 

Example 1:

Input: nums = [2,3,4], queries = [0,2,2]

Output: [1,2,2]

Explanation:

gcdPairs = [gcd(nums[0], nums[1]), gcd(nums[0], nums[2]), gcd(nums[1], nums[2])] = [1, 2, 1].

After sorting in ascending order, gcdPairs = [1, 1, 2].

So, the answer is [gcdPairs[queries[0]], gcdPairs[queries[1]], gcdPairs[queries[2]]] = [1, 2, 2].

Example 2:

Input: nums = [4,4,2,1], queries = [5,3,1,0]

Output: [4,2,1,1]

Explanation:

gcdPairs sorted in ascending order is [1, 1, 1, 2, 2, 4].

Example 3:

Input: nums = [2,2], queries = [0,0]

Output: [2,2]

Explanation:

gcdPairs = [2].

 

Constraints:

2 <= n == nums.length <= 105
1 <= nums[i] <= 5 * 104
1 <= queries.length <= 105
0 <= queries[i] < n * (n - 1) / 2
*/

class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int maxVal = 0;
        for (int num : nums) {
            maxVal = Math.max(maxVal, num);
        }

        // Step 1: Count frequencies of each number
        long[] count = new long[maxVal + 1];
        for (int num : nums) {
            count[num]++;
        }

        // Step 2: Compute the exact number of pairs for each GCD using Inclusion-Exclusion
        long[] exactGcdCount = new long[maxVal + 1];
        for (int i = maxVal; i >= 1; i--) {
            long multiplesCount = 0;
            // Count how many numbers are divisible by i
            for (int j = i; j <= maxVal; j += i) {
                multiplesCount += count[j];
            }
            
            // Total pairs where both elements are multiples of i
            long pairs = (multiplesCount * (multiplesCount - 1)) / 2;
            
            // Exclude pairs whose GCD is a strict multiple of i (e.g., 2i, 3i, 4i...)
            for (int j = 2 * i; j <= maxVal; j += i) {
                pairs -= exactGcdCount[j];
            }
            
            exactGcdCount[i] = pairs;
        }

        // Step 3: Compute prefix sums of the exact GCD counts
        long[] prefixSum = new long[maxVal + 1];
        for (int i = 1; i <= maxVal; i++) {
            prefixSum[i] = prefixSum[i - 1] + exactGcdCount[i];
        }

        // Step 4: Answer each query using Binary Search
        int[] ans = new int[queries.length];
        for (int k = 0; k < queries.length; k++) {
            long target = queries[k];
            int left = 1, right = maxVal;
            int res = maxVal;
            
            // Find the first index in prefixSum strictly greater than the target index
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (prefixSum[mid] > target) {
                    res = mid;
                    right = mid - 1; // Try to find a smaller valid GCD
                } else {
                    left = mid + 1;
                }
            }
            ans[k] = res;
        }

        return ans;
    }
}
