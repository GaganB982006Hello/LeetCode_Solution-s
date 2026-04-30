/*
You are given an m x n grid where each cell contains one of the values 0, 1, or 2. You are also given an integer k.

You start from the top-left corner (0, 0) and want to reach the bottom-right corner (m - 1, n - 1) by moving only right or down.

Each cell contributes a specific score and incurs an associated cost, according to their cell values:

0: adds 0 to your score and costs 0.
1: adds 1 to your score and costs 1.
2: adds 2 to your score and costs 1. ​​​​​​​
Return the maximum score achievable without exceeding a total cost of k, or -1 if no valid path exists.

Note: If you reach the last cell but the total cost exceeds k, the path is invalid.

 

Example 1:

Input: grid = [[0, 1],[2, 0]], k = 1

Output: 2

Explanation:​​​​​​​

The optimal path is:

Cell	grid[i][j]	Score	Total
Score	Cost	Total
Cost
(0, 0)	0	0	0	0	0
(1, 0)	2	2	2	1	1
(1, 1)	0	0	2	0	1
Thus, the maximum possible score is 2.

Example 2:

Input: grid = [[0, 1],[1, 2]], k = 1

Output: -1

Explanation:

There is no path that reaches cell (1, 1)​​​​​​​ without exceeding cost k. Thus, the answer is -1.

 

Constraints:

1 <= m, n <= 200
0 <= k <= 103​​​​​​​
​​​​​​​grid[0][0] == 0
0 <= grid[i][j] <= 2
*/

class Solution {
    public int maxPathScore(int[][] grid, int k) {
        int m = grid.length, n = grid[0].length;
        int[][] dp = new int[n][k + 1];
        for (int[] row : dp) Arrays.fill(row, -1);

        int startVal = grid[0][0];
        int startCost = (startVal > 0) ? 1 : 0;
        if (startCost <= k) dp[0][startCost] = startVal;

        for (int i = 0; i < m; i++) {
            int[][] nextDp = new int[n][k + 1];
            for (int[] row : nextDp) Arrays.fill(row, -1);
            
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                int cInc = (val > 0) ? 1 : 0;
                
                for (int c = 0; c <= k; c++) {
                    int prev = -1;
                    if (i == 0 && j == 0) {
                        if (c == 0) prev = 0;
                    } else {
                        if (i > 0) prev = Math.max(prev, dp[j][c]);
                        if (j > 0) prev = Math.max(prev, nextDp[j-1][c]);
                    }
                    
                    if (prev != -1 && c + cInc <= k) {
                        nextDp[j][c + cInc] = Math.max(nextDp[j][c + cInc], prev + val);
                    }
                }
            }
            dp = nextDp;
        }

        int maxScore = -1;
        for (int score : dp[n - 1]) maxScore = Math.max(maxScore, score);
        return maxScore;
    }
}
