/*
Medium
Topics
premium lock icon
Companies
Hint
An integer has sequential digits if and only if each digit in the number is one more than the previous digit.

Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.

 

Example 1:

Input: low = 100, high = 300
Output: [123,234]
Example 2:

Input: low = 1000, high = 13000
Output: [1234,2345,3456,4567,5678,6789,12345]
 

Constraints:

10 <= low <= high <= 10^9
*/

import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<Integer> sequentialDigits(int low, int high) {
        List<Integer> ans = new ArrayList<>();
        String digits = "123456789";
        
        // Check lengths from 2 to 9
        for (int length = 2; length <= 9; length++) {
            for (int i = 0; i <= 9 - length; i++) {
                int num = Integer.parseInt(digits.substring(i, i + length));
                if (num >= low && num <= high) {
                    ans.add(num);
                }
            }
        }
        
        return ans;
    }
}
