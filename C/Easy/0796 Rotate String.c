/*
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.
 

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true
Example 2:

Input: s = "abcde", goal = "abced"
Output: false
 

Constraints:

1 <= s.length, goal.length <= 100
s and goal consist of lowercase English letters.
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool rotateString(char* s, char* goal) {
    int n = strlen(s);
    int m = strlen(goal);
    
    // If lengths differ, rotation is impossible
    if (n != m) return false;
    
    // Allocate memory for s + s + null terminator
    char* doubled = (char*)malloc(sizeof(char) * (2 * n + 1));
    
    // Create the doubled string
    strcpy(doubled, s);
    strcat(doubled, s);
    
    // Check if goal exists within the doubled string
    char* ptr = strstr(doubled, goal);
    
    bool result = (ptr != NULL);
    
    free(doubled); // Always clean up your memory!
    return result;
}
