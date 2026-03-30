#include <stdbool.h>
#include <string.h>

bool checkStrings(char* s1, char* s2) {
    int n = strlen(s1);
    // Frequency arrays for even and odd positions
    // Initialize with 0
    int evenFreq[26] = {0};
    int oddFreq[26] = {0};

    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            // Increment for s1, decrement for s2 at even positions
            evenFreq[s1[i] - 'a']++;
            evenFreq[s2[i] - 'a']--;
        } else {
            // Increment for s1, decrement for s2 at odd positions
            oddFreq[s1[i] - 'a']++;
            oddFreq[s2[i] - 'a']--;
        }
    }

    // If all counts are 0, s1 and s2 have identical characters at 
    // respective parities and can be made equal.
    for (int i = 0; i < 26; i++) {
        if (evenFreq[i] != 0 || oddFreq[i] != 0) {
            return false;
        }
    }

    return true;
}
