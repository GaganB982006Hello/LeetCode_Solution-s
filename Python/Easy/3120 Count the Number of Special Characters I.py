'''
You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.

Return the number of special letters in word.

 

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters in word are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

No character in word appears in uppercase.

Example 3:

Input: word = "abBCab"

Output: 1

Explanation:

The only special character in word is 'b'.

 

Constraints:

1 <= word.length <= 50
word consists of only lowercase and uppercase English letters.
'''

class Solution:
    def numberOfSpecialChars(self, word: str) -> int:
        # Store all unique characters present in the word
        char_set = set(word)
        special_count = 0
        
        # Iterate through the lowercase alphabet
        for i in range(26):
            lower_char = chr(ord('a') + i)
            upper_char = chr(ord('A') + i)
            
            # If both lowercase and uppercase forms exist, increment count
            if lower_char in char_set and upper_char in char_set:
                special_count += 1
                
        return special_count
