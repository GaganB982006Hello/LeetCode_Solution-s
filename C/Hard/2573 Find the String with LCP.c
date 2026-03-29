#include <stdlib.h>
#include <string.h>

char* findTheString(int** lcp, int lcpSize, int* lcpColSize) {
    int n = lcpSize;
    int* s = (int*)calloc(n, sizeof(int));
    int charValue = 1;

    // 1. Greedy assignment of characters
    for (int i = 0; i < n; i++) {
        if (s[i] > 0) continue;
        // If we need more than 26 characters, it's impossible
        if (charValue > 26) {
            free(s);
            return "";
        }
        for (int j = i; j < n; j++) {
            if (lcp[i][j] > 0) {
                s[j] = charValue;
            }
        }
        charValue++;
    }

    // 2. Verification of the constructed string against the LCP matrix
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int expected = 0;
            if (s[i] == s[j]) {
                expected = (i == n - 1 || j == n - 1) ? 1 : 1 + lcp[i + 1][j + 1];
            }
            if (lcp[i][j] != expected) {
                free(s);
                return "";
            }
        }
    }

    // 3. Convert integer array to character string
    char* res = (char*)malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
        res[i] = (char)('a' + s[i] - 1);
    }
    res[n] = '\0';

    free(s);
    return res;
}
