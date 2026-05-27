/*
You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.

Return the number of special letters in word.

 

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

There are no special characters in word.

Example 3:

Input: word = "AbBCab"

Output: 0

Explanation:

There are no special characters in word.

 

Constraints:

1 <= word.length <= 2 * 105
word consists of only lowercase and uppercase English letters.
  */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int numberOfSpecialChars(char* word) {
    // Arrays to store the last lowercase index and first uppercase index
    // Initialized to -1 to represent "not found"
    int lastLower[26];
    int firstUpper[26];
    
    for (int i = 0; i < 26; i++) {
        lastLower[i] = -1;
        firstUpper[i] = -1;
    }
    
    // Iterate through the string to track indices
    for (int i = 0; word[i] != '\0'; i++) {
        char ch = word[i];
        if (islower(ch)) {
            int idx = ch - 'a';
            lastLower[idx] = i;
        } else if (isupper(ch)) {
            int idx = ch - 'A';
            // Only update if it's the first time seeing this uppercase letter
            if (firstUpper[idx] == -1) {
                firstUpper[idx] = i;
            }
        }
    }
    
    // Count special characters
    int specialCount = 0;
    for (int i = 0; i < 26; i++) {
        if (lastLower[i] != -1 && firstUpper[i] != -1) {
            if (lastLower[i] < firstUpper[i]) {
                specialCount++;
            }
        }
    }
    
    return specialCount;
}
