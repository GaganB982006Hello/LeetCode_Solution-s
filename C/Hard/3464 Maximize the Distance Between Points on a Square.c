/*
You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.

You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.

You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.

Return the maximum possible minimum Manhattan distance between the selected k points.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

 

Example 1:

Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

Output: 2

Explanation:



Select all four points.

Example 2:

Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

Output: 1

Explanation:



Select the points (0, 0), (2, 0), (2, 2), and (2, 1).

Example 3:

Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

Output: 1

Explanation:



Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).

 

Constraints:

1 <= side <= 109
4 <= points.length <= min(4 * side, 15 * 103)
points[i] == [xi, yi]
The input is generated such that:
points[i] lies on the boundary of the square.
All points[i] are unique.
4 <= k <= min(25, points.length)
*/

#include <stdlib.h>

int compare(const void* a, const void* b) {
    long long arg1 = *(const long long*)a;
    long long arg2 = *(const long long*)b;
    return (arg1 > arg2) - (arg1 < arg2);
}

int lowerBound(long long* arr, int low, int high, long long target) {
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] < target) low = mid + 1;
        else high = mid;
    }
    return low;
}

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize, int k) {
    long long* nums = (long long*)malloc(pointsSize * sizeof(long long));
    long long perimeter = 4LL * side;

    for (int i = 0; i < pointsSize; i++) {
        int x = points[i][0], y = points[i][1];
        if (y == 0) nums[i] = x;
        else if (x == side) nums[i] = (long long)side + y;
        else if (y == side) nums[i] = 3LL * side - x;
        else nums[i] = 3LL * side + (side - y);
    }
    qsort(nums, pointsSize, sizeof(long long), compare);

    int low = 1, high = side, ans = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int possible = 0;
        for (int i = 0; i < pointsSize; i++) {
            if (nums[i] - nums[0] > perimeter / k) break;
            
            int count = 1;
            int currIdx = i;
            for (int j = 1; j < k; j++) {
                int nextIdx = lowerBound(nums, currIdx + 1, pointsSize, nums[currIdx] + mid);
                if (nextIdx == pointsSize) {
                    count = -1;
                    break;
                }
                currIdx = nextIdx;
                count++;
            }
            if (count == k && (nums[i] + perimeter - nums[currIdx]) >= mid) {
                possible = 1;
                break;
            }
        }

        if (possible) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    free(nums);
    return ans;
}
