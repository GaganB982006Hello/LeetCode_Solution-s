import java.util.*;

class Solution {
    public boolean canPartitionGrid(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        long totalSum = 0;
        for (int[] row : grid) {
            for (int val : row) totalSum += val;
        }

        // --- 1. Horizontal Cuts ---
        long topSum = 0;
        Map<Integer, Integer> topMap = new HashMap<>();
        Map<Integer, Integer> botMap = new HashMap<>();
        for (int[] row : grid) {
            for (int val : row) botMap.put(val, botMap.getOrDefault(val, 0) + 1);
        }

        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                int val = grid[i][j];
                topSum += val;
                topMap.put(val, topMap.getOrDefault(val, 0) + 1);
                botMap.put(val, botMap.get(val) - 1);
                if (botMap.get(val) == 0) botMap.remove(val);
            }
            
            long botSum = totalSum - topSum;
            // Check Top Section (Height: i+1, Width: n)
            if (checkSection(topSum, botSum, topMap, i + 1, n, grid, 0, i, 0, n - 1, true)) return true;
            // Check Bottom Section (Height: m-1-i, Width: n)
            if (checkSection(botSum, topSum, botMap, m - 1 - i, n, grid, i + 1, m - 1, 0, n - 1, true)) return true;
        }

        // --- 2. Vertical Cuts ---
        long leftSum = 0;
        Map<Integer, Integer> leftMap = new HashMap<>();
        Map<Integer, Integer> rightMap = new HashMap<>();
        // Re-init maps for vertical
        for (int[] row : grid) {
            for (int val : row) rightMap.put(val, rightMap.getOrDefault(val, 0) + 1);
        }

        for (int j = 0; j < n - 1; j++) {
            for (int i = 0; i < m; i++) {
                int val = grid[i][j];
                leftSum += val;
                leftMap.put(val, leftMap.getOrDefault(val, 0) + 1);
                rightMap.put(val, rightMap.get(val) - 1);
                if (rightMap.get(val) == 0) rightMap.remove(val);
            }

            long rightSum = totalSum - leftSum;
            // Check Left Section (Height: m, Width: j+1)
            if (checkSection(leftSum, rightSum, leftMap, m, j + 1, grid, 0, m - 1, 0, j, false)) return true;
            // Check Right Section (Height: m, Width: n-1-j)
            if (checkSection(rightSum, leftSum, rightMap, m, n - 1 - j, grid, 0, m - 1, j + 1, n - 1, false)) return true;
        }

        return false;
    }

    private boolean checkSection(long s1, long s2, Map<Integer, Integer> freq, int h, int w, 
                                 int[][] grid, int r1, int r2, int c1, int c2, boolean isHorCut) {
        if (s1 == s2) return true;
        long diff = s1 - s2;
        if (diff < 0 || diff > Integer.MAX_VALUE) return false;
        int d = (int) diff;

        if (!freq.containsKey(d)) return false;

        // Connectivity Rule
        if (h > 1 && w > 1) return true; // 2D: any cell works
        
        // 1D strip: only endpoints work
        if (h == 1) return grid[r1][c1] == d || grid[r1][c2] == d;
        if (w == 1) return grid[r1][c1] == d || grid[r2][c1] == d;
        
        return false;
    }
}
