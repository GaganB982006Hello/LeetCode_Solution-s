import java.util.*;

class Solution {
    public String generateString(String str1, String str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        char[] res = new char[len];
        boolean[] fixed = new boolean[len];
        
        // Initialize with a placeholder
        Arrays.fill(res, '\0');

        // Step 1: Fill all 'T' conditions
        for (int i = 0; i < n; i++) {
            if (str1.charAt(i) == 'T') {
                for (int j = 0; j < m; j++) {
                    if (res[i + j] != '\0' && res[i + j] != str2.charAt(j)) {
                        return ""; // Contradiction between two 'T's
                    }
                    res[i + j] = str2.charAt(j);
                    fixed[i + j] = true;
                }
            }
        }

        // Step 2: Fill remaining slots with 'a' to keep it lexicographically smallest
        for (int i = 0; i < len; i++) {
            if (res[i] == '\0') {
                res[i] = 'a';
            }
        }

        // Step 3: Check and fix 'F' conditions
        // We iterate from left to right, but when an 'F' is violated, 
        // we try to change the rightmost possible (non-fixed) character to 'b'
        for (int i = 0; i < n; i++) {
            if (str1.charAt(i) == 'F') {
                if (isMatch(res, i, str2)) {
                    boolean changed = false;
                    // Try to change a character from the end of the substring to keep it small
                    for (int j = m - 1; j >= 0; j--) {
                        if (!fixed[i + j]) {
                            res[i + j] = 'b';
                            changed = true;
                            break; 
                        }
                    }
                    // If we couldn't change any character, this configuration is impossible
                    if (!changed) return "";
                }
            } else {
                // Double check 'T' conditions after 'F' fixes
                if (!isMatch(res, i, str2)) return "";
            }
        }

        return new String(res);
    }

    private boolean isMatch(char[] res, int start, String str2) {
        for (int j = 0; j < str2.length(); j++) {
            if (res[start + j] != str2.charAt(j)) return false;
        }
        return true;
    }
}
