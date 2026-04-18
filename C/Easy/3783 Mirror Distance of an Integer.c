/*
You are given an integer n.

Define its mirror distance as: abs(n - reverse(n))​​​​​​​ where reverse(n) is the integer formed by reversing the digits of n.

Return an integer denoting the mirror distance of n​​​​​​​.

abs(x) denotes the absolute value of x.

 

Example 1:

Input: n = 25

Output: 27

Explanation:

reverse(25) = 52.
Thus, the answer is abs(25 - 52) = 27.
Example 2:

Input: n = 10

Output: 9

Explanation:

reverse(10) = 01 which is 1.
Thus, the answer is abs(10 - 1) = 9.
Example 3:

Input: n = 7

Output: 0

Explanation:

reverse(7) = 7.
Thus, the answer is abs(7 - 7) = 0.
 

Constraints:

1 <= n <= 109
*/

#include <stdio.h>
#include <stdlib.h>

int mirrorDistance(int n) {
    long long original = n;
    long long reversed = 0;
    long long temp = n;
    
    // Reverse the digits of n
    while (temp > 0) {
        reversed = (reversed * 10) + (temp % 10);
        temp /= 10;
    }
    
    // Calculate absolute difference
    long long diff = original - reversed;
    
    // Using llabs for long long absolute value or simple ternary
    return (int)(diff < 0 ? -diff : diff);
}
