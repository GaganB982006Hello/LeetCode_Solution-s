#include <stdio.h>
#include <limits.h>
#include <math.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
    int m = coinsSize;
    int n = coinsColSize[0];
    long long dp[m][n][3];

    // Initialize with a very small value
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = LLONG_MIN;
            }
        }
    }

    // Base case
    dp[0][0][0] = coins[0][0];
    if (coins[0][0] < 0) {
        dp[0][0][1] = 0;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 3; k++) {
                if (dp[i][j][k] == LLONG_MIN) continue;

                // Move Down
                if (i + 1 < m) {
                    dp[i + 1][j][k] = MAX(dp[i + 1][j][k], dp[i][j][k] + coins[i + 1][j]);
                    if (k + 1 < 3 && coins[i + 1][j] < 0) {
                        dp[i + 1][j][k + 1] = MAX(dp[i + 1][j][k + 1], dp[i][j][k]);
                    }
                }

                // Move Right
                if (j + 1 < n) {
                    dp[i][j + 1][k] = MAX(dp[i][j + 1][k], dp[i][j][k] + coins[i][j + 1]);
                    if (k + 1 < 3 && coins[i][j + 1] < 0) {
                        dp[i][j + 1][k + 1] = MAX(dp[i][j + 1][k + 1], dp[i][j][k]);
                    }
                }
            }
        }
    }

    long long result = dp[m - 1][n - 1][0];
    result = MAX(result, dp[m - 1][n - 1][1]);
    result = MAX(result, dp[m - 1][n - 1][2]);
    
    return (int)result;
}
