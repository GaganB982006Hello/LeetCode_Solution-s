#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* generateString(char* str1, char* str2) {
    int n = strlen(str1);
    int m = strlen(str2);
    int total_len = n + m - 1;

    // Allocate memory for the result string and a tracking array
    char* res = (char*)malloc((total_len + 1) * sizeof(char));
    bool* fixed = (bool*)calloc(total_len, sizeof(bool));

    // Initialize res with a null character to track unassigned slots
    for (int i = 0; i < total_len; i++) res[i] = '\0';
    res[total_len] = '\0';

    // Step 1: Satisfy 'T' conditions
    for (int i = 0; i < n; i++) {
        if (str1[i] == 'T') {
            for (int j = 0; j < m; j++) {
                if (res[i + j] != '\0' && res[i + j] != str2[j]) {
                    free(fixed);
                    free(res);
                    return ""; // Contradiction
                }
                res[i + j] = str2[j];
                fixed[i + j] = true;
            }
        }
    }

    // Step 2: Fill empty slots with 'a'
    for (int i = 0; i < total_len; i++) {
        if (res[i] == '\0') {
            res[i] = 'a';
        }
    }

    // Step 3: Satisfy 'F' conditions
    for (int i = 0; i < n; i++) {
        if (str1[i] == 'F') {
            // Check if current substring matches str2
            if (strncmp(&res[i], str2, m) == 0) {
                bool changed = false;
                // Try changing the rightmost non-fixed character to 'b'
                for (int j = m - 1; j >= 0; j--) {
                    if (!fixed[i + j]) {
                        res[i + j] = 'b';
                        changed = true;
                        break;
                    }
                }
                if (!changed) {
                    free(fixed);
                    free(res);
                    return ""; // Impossible to satisfy 'F'
                }
            }
        } else {
            // Re-verify 'T' conditions (safety check)
            if (strncmp(&res[i], str2, m) != 0) {
                free(fixed);
                free(res);
                return "";
            }
        }
    }

    free(fixed);
    return res;
}
