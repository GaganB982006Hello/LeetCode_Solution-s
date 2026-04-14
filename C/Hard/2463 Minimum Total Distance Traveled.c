/*
There are some robots and factories on the X-axis. You are given an integer array robot where robot[i] is the position of the ith robot. You are also given a 2D integer array factory where factory[j] = [positionj, limitj] indicates that positionj is the position of the jth factory and that the jth factory can repair at most limitj robots.

The positions of each robot are unique. The positions of each factory are also unique. Note that a robot can be in the same position as a factory initially.

All the robots are initially broken; they keep moving in one direction. The direction could be the negative or the positive direction of the X-axis. When a robot reaches a factory that did not reach its limit, the factory repairs the robot, and it stops moving.

At any moment, you can set the initial direction of moving for some robot. Your target is to minimize the total distance traveled by all the robots.

Return the minimum total distance traveled by all the robots. The test cases are generated such that all the robots can be repaired.

Note that

All robots move at the same speed.
If two robots move in the same direction, they will never collide.
If two robots move in opposite directions and they meet at some point, they do not collide. They cross each other.
If a robot passes by a factory that reached its limits, it crosses it as if it does not exist.
If the robot moved from a position x to a position y, the distance it moved is |y - x|
Input: robot = [0,4,6], factory = [[2,2],[6,2]]
Output: 4
Explanation: As shown in the figure:
- The first robot at position 0 moves in the positive direction. It will be repaired at the first factory.
- The second robot at position 4 moves in the negative direction. It will be repaired at the first factory.
- The third robot at position 6 will be repaired at the second factory. It does not need to move.
The limit of the first factory is 2, and it fixed 2 robots.
The limit of the second factory is 2, and it fixed 1 robot.
The total distance is |2 - 0| + |2 - 4| + |6 - 6| = 4. It can be shown that we cannot achieve a better total distance than 4.
Input: robot = [1,-1], factory = [[-2,1],[2,1]]
Output: 2
Explanation: As shown in the figure:
- The first robot at position 1 moves in the positive direction. It will be repaired at the second factory.
- The second robot at position -1 moves in the negative direction. It will be repaired at the first factory.
The limit of the first factory is 1, and it fixed 1 robot.
The limit of the second factory is 1, and it fixed 1 robot.
The total distance is |2 - 1| + |(-2) - (-1)| = 2. It can be shown that we cannot achieve a better total distance than 2.
 

Constraints:

1 <= robot.length, factory.length <= 100
factory[j].length == 2
-109 <= robot[i], positionj <= 109
0 <= limitj <= robot.length
The input will be generated such that it is always possible to repair every robot
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

// Comparator for sorting integers
int compareInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparator for sorting the 2D factory array
int compareFactories(const void* a, const void* b) {
    int* f1 = *(int**)a;
    int* f2 = *(int**)b;
    return (f1[0] - f2[0]);
}

long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    // 1. Sort robots and factories by position
    qsort(robot, robotSize, sizeof(int), compareInts);
    qsort(factory, factorySize, sizeof(int*), compareFactories);

    // 2. Initialize DP array
    // dp[i] = minimum distance for the first i robots
    long long* dp = (long long*)malloc((robotSize + 1) * sizeof(long long));
    long long INF = 1e15; // Sufficiently large value
    
    for (int i = 0; i <= robotSize; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    // 3. Process each factory one by one
    for (int j = 0; j < factorySize; j++) {
        int pos = factory[j][0];
        int cap = factory[j][1];
        
        // Use a temporary DP array to update current factory contributions
        // This prevents using the same factory instance for the same robot multiple times
        for (int i = robotSize; i >= 0; i--) {
            if (dp[i] == INF) continue;

            long long current_dist = 0;
            // Try assigning k robots to the current factory j
            for (int k = 1; k <= cap && (i + k) <= robotSize; k++) {
                current_dist += llabs((long long)robot[i + k - 1] - pos);
                if (dp[i] + current_dist < dp[i + k]) {
                    dp[i + k] = dp[i] + current_dist;
                }
            }
        }
    }

    long long result = dp[robotSize];
    free(dp);
    return result;
}
