import java.util.HashMap;
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
class Solution {
    public int minMirrorPairDistance(int[] nums) {
        // Maps the reverse of a number to the most recent index it appeared
        HashMap<Integer, Integer> targetMap = new HashMap<>();
        int minDist = Integer.MAX_VALUE;
        
        for (int j = 0; j < nums.length; j++) {
            // Check if current number completes a mirror pair
            if (targetMap.containsKey(nums[j])) {
                minDist = Math.min(minDist, j - targetMap.get(nums[j]));
            }
            
            // Store/Update the reverse of current number and its index
            int revVal = reverse(nums[j]);
            targetMap.put(revVal, j);
        }
        
        return (minDist == Integer.MAX_VALUE) ? -1 : minDist;
    }
    
    private int reverse(int n) {
        int rev = 0;
        while (n > 0) {
            rev = rev * 10 + (n % 10);
            n /= 10;
        }
        return rev;
    }
}
