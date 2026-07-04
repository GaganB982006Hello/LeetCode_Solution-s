/*
You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.

The score of a path between two cities is defined as the minimum distance of a road in this path.

Return the minimum possible score of a path between cities 1 and n.

Note:

A path is a sequence of roads between two cities.
It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
The test cases are generated such that there is at least one path between 1 and n.
 

Example 1:


Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
Output: 5
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
It can be shown that no other path has less score.
Example 2:


Input: n = 4, roads = [[1,2,2],[1,3,4],[3,4,7]]
Output: 2
Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 1 -> 3 -> 4. The score of this path is min(2,2,4,7) = 2.
 

Constraints:

2 <= n <= 105
1 <= roads.length <= 105
roads[i].length == 3
1 <= ai, bi <= n
ai != bi
1 <= distancei <= 104
There are no repeated edges.
There is at least one path between 1 and n.
  */

#include <limits.h>

int parent[100005];

int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]); // Path compression
}

void uni(int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
        parent[root_i] = root_j;
    }
}

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    // Initialize Union-Find array
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    
    // Group all connected cities
    for (int i = 0; i < roadsSize; i++) {
        uni(roads[i][0], roads[i][1]);
    }
    
    int root_1 = find(1);
    int min_score = INT_MAX;
    
    // Find the minimum distance edge in the same component as city 1
    for (int i = 0; i < roadsSize; i++) {
        if (find(roads[i][0]) == root_1) {
            if (roads[i][2] < min_score) {
                min_score = roads[i][2];
            }
        }
    }
    
    return min_score;
}
