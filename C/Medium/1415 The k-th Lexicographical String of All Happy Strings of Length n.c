#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void backtrack(int n, int* k, char* current, int len, char* res) {
    if (len == n) {
        (*k)--;
        if (*k == 0) {
            strncpy(res, current, n);
            res[n] = '\0';
        }
        return;
    }

    for (char ch = 'a'; ch <= 'c'; ch++) {
        if (strlen(res) > 0) return; // Found result

        if (len == 0 || current[len - 1] != ch) {
            current[len] = ch;
            backtrack(n, k, current, len + 1, res);
            if (strlen(res) > 0) return;
        }
    }
}

char* getHappyString(int n, int k) {
    char* res = (char*)calloc(n + 1, sizeof(char));
    char* current = (char*)malloc((n + 1) * sizeof(char));
    
    backtrack(n, &k, current, 0, res);
    
    free(current);
    // If res is empty string, calloc already handled it; 
    // but the problem expects "" if k is too large.
    return res;
}
