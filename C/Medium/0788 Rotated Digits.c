/*
An integer x is a good if after rotating each digit individually by 180 degrees, we get a valid number that is different from x. Each digit must be rotated - we cannot choose to leave it alone.

A number is valid if each digit remains a digit after rotation. For example:

0, 1, and 8 rotate to themselves,
2 and 5 rotate to each other (in this case they are rotated in a different direction, in other words, 2 or 5 gets mirrored),
6 and 9 rotate to each other, and
the rest of the numbers do not rotate to any other number and become invalid.
Given an integer n, return the number of good integers in the range [1, n].

 

Example 1:

Input: n = 10
Output: 4
Explanation: There are four good numbers in the range [1, 10] : 2, 5, 6, 9.
Note that 1 and 10 are not good numbers, since they remain unchanged after rotating.
Example 2:

Input: n = 1
Output: 0
Example 3:

Input: n = 2
Output: 1
 

Constraints:

1 <= n <= 104
  */

#include <stdbool.h>

bool isGood(int x) {
    bool hasChangedDigit = false;
    while (x > 0) {
        int d = x % 10;
        // If it contains 3, 4, or 7, it's invalid
        if (d == 3 || d == 4 || d == 7) return false;
        // If it contains 2, 5, 6, or 9, it will differ from the original
        if (d == 2 || d == 5 || d == 6 || d == 9) hasChangedDigit = true;
        x /= 10;
    }
    return hasChangedDigit;
}

int rotatedDigits(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (isGood(i)) count++;
    }
    return count;
}
