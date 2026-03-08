class Solution {
    public boolean isPalindrome(int x) {
        // Negative numbers are not palindromes
        // Numbers ending in 0 (except 0 itself) are not palindromes
        if (x < 0 || (x % 10 == 0 && x != 0)) {
            return false;
        }
        
        // Reverse half of the number
        int reversedHalf = 0;
        while (x > reversedHalf) {
            reversedHalf = reversedHalf * 10 + x % 10;
            x = x / 10;
        }
        
        // Check if the original number equals the reversed half
        // For odd length numbers, we can get rid of the middle digit by reversedHalf/10
        return x == reversedHalf || x == reversedHalf / 10;
    }
}
