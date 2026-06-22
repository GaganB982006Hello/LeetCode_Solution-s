/*
Given a string text, you want to use the characters of text to form as many instances of the word "balloon" as possible.

You can use each character in text at most once. Return the maximum number of instances that can be formed.

 

Example 1:
Input: text = "nlaebolko"
Output: 1
Example 2:
Input: text = "loonbalxballpoon"
Output: 2
Example 3:
Input: text = "leetcode"
Output: 0
Constraints:
1 <= text.length <= 104
text consists of lower case English letters only.
  */

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxNumberOfBalloons(char * text) {
    int b = 0, a = 0, l = 0, o = 0, n = 0;
    
    // Count occurrences of each relevant character
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == 'b') b++;
        else if (text[i] == 'a') a++;
        else if (text[i] == 'l') l++;
        else if (text[i] == 'o') o++;
        else if (text[i] == 'n') n++;
    }
    
    // Divide 'l' and 'o' by 2 since "balloon" requires two of each
    l /= 2;
    o /= 2;
    
    // Find and return the minimum
    int min1 = MIN(b, a);
    int min2 = MIN(l, o);
    int min3 = MIN(min1, min2);
    
    return MIN(min3, n);
}
