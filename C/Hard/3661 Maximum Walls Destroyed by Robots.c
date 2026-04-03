#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pos;
    int dist;
} Robot;

int cmpInt(const void* a, const void* b) { return (*(int*)a - *(int*)b); }
int cmpRobot(const void* a, const void* b) { return (((Robot*)a)->pos - ((Robot*)b)->pos); }

int countWalls(int* walls, int m, int start, int end) {
    if (start > end) return 0;
    int l = 0, r = m;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (walls[mid] >= start) r = mid; else l = mid + 1;
    }
    int leftIdx = l;
    l = 0; r = m;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (walls[mid] <= end) l = mid + 1; else r = mid;
    }
    return l - leftIdx;
}

int maxWalls(int* robots, int n, int* distance, int distSize, int* walls, int m) {
    Robot* rData = malloc(n * sizeof(Robot));
    for (int i = 0; i < n; i++) {
        rData[i].pos = robots[i];
        rData[i].dist = distance[i];
    }
    qsort(rData, n, sizeof(Robot), cmpRobot);
    qsort(walls, m, sizeof(int), cmpInt);

    long** dp = malloc((n + 1) * sizeof(long*));
    for (int i = 0; i <= n; i++) dp[i] = calloc(2, sizeof(long));

    for (int i = 0; i < n; i++) {
        int pos = rData[i].pos;
        int dist = rData[i].dist;

        // Left
        int lLimit = (i == 0) ? -2e9 : rData[i-1].pos + 1;
        int lReach = (pos - dist > lLimit) ? pos - dist : lLimit;
        int wallsL = countWalls(walls, m, lReach, pos);

        int prevRReach = (i == 0) ? -2e9 : (rData[i-1].pos + rData[i-1].dist < pos - 1 ? rData[i-1].pos + rData[i-1].dist : pos - 1);
        int uniqueL = countWalls(walls, m, (lReach > prevRReach + 1 ? lReach : prevRReach + 1), pos);

        dp[i+1][0] = (dp[i][0] + wallsL > dp[i][1] + uniqueL) ? dp[i][0] + wallsL : dp[i][1] + uniqueL;

        // Right
        int rLimit = (i == n - 1) ? 2e9 : rData[i+1].pos - 1;
        int rReach = (pos + dist < rLimit) ? pos + dist : rLimit;
        int wallsR = countWalls(walls, m, pos, rReach);

        long prevMax = (dp[i][0] > dp[i][1]) ? dp[i][0] : dp[i][1];
        dp[i+1][1] = prevMax + wallsR;

        if (prevMax > dp[i+1][0]) dp[i+1][0] = prevMax;
    }

    long res = (dp[n][0] > dp[n][1]) ? dp[n][0] : dp[n][1];
    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp); free(rData);
    return (int)res;
}
