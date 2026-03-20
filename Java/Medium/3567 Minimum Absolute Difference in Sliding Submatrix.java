import java.util.*;

class Solution {
    public int[][] minAbsDiff(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        int[][] ans = new int[m - k + 1][n - k + 1];

        for (int i = 0; i <= m - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                List<Integer> elements = new ArrayList<>();
                for (int r = i; r < i + k; r++) {
                    for (int c = j; c < j + k; c++) {
                        elements.add(grid[r][c]);
                    }
                }
                Collections.sort(elements);
                
                int minDiff = Integer.MAX_VALUE;
                boolean foundDistinct = false;
                for (int l = 0; l < elements.size() - 1; l++) {
                    int diff = Math.abs(elements.get(l) - elements.get(l + 1));
                    if (diff > 0) {
                        minDiff = Math.min(minDiff, diff);
                        foundDistinct = true;
                    }
                }
                ans[i][j] = foundDistinct ? minDiff : 0;
            }
        }
        return ans;
    }
}
