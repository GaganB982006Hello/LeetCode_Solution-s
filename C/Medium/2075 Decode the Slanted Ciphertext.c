#include <string.h>
#include <stdlib.h>

char* decodeCiphertext(char* encodedText, int rows) {
    int n = strlen(encodedText);
    if (n == 0) return "";
    
    int cols = n / rows;
    char* res = (char*)malloc((n + 1) * sizeof(char));
    int k = 0;
    
    for (int i = 0; i < cols; i++) {
        for (int r = 0, c = i; r < rows && c < cols; r++, c++) {
            res[k++] = encodedText[r * cols + c];
        }
    }
    res[k] = '\0';
    
    // Trim trailing spaces
    int last = k - 1;
    while (last >= 0 && res[last] == ' ') {
        res[last--] = '\0';
    }
    
    return res;
}
