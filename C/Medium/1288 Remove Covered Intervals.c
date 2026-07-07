/*
Given an array intervals where intervals[i] = [li, ri] represent the interval [li, ri), remove all intervals that are covered by another interval in the list.

The interval [a, b) is covered by the interval [c, d) if and only if c <= a and b <= d.

Return the number of remaining intervals.

 

Example 1:

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2
Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
Example 2:

Input: intervals = [[1,4],[2,3]]
Output: 1
 

Constraints:

1 <= intervals.length <= 1000
intervals[i].length == 2
0 <= li < ri <= 105
All the given intervals are unique.
  */

#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    int* intervalA = *(int**)a;
    int* intervalB = *(int**)b;
    
    if (intervalA[0] == intervalB[0]) {
        // Sort by end time descending if start times are equal
        return intervalB[1] - intervalA[1];
    }
    // Sort by start time ascending
    return intervalA[0] - intervalB[0];
}

int removeCoveredIntervals(int** intervals, int intervalsSize, int* intervalsColSize) {
    // Sort the intervals array
    qsort(intervals, intervalsSize, sizeof(int*), compare);
    
    int coveredCount = 0;
    int maxEnd = -1;
    
    for (int i = 0; i < intervalsSize; i++) {
        if (intervals[i][1] <= maxEnd) {
            coveredCount++;
        } else {
            maxEnd = intervals[i][1];
        }
    }
    
    return intervalsSize - coveredCount;
}
