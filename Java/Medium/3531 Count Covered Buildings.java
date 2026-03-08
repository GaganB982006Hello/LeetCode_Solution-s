class Solution {
    public int countCoveredBuildings(int n, int[][] buildings) {
        // Using 1-based indexing for convenience since 1 <= x, y <= n
        int[] rowMinY = new int[n + 1];
        int[] rowMaxY = new int[n + 1];
        int[] colMinX = new int[n + 1];
        int[] colMaxX = new int[n + 1];

        // Initialize mins and maxes
        final int INF = Integer.MAX_VALUE;
        for (int i = 1; i <= n; i++) {
            rowMinY[i] = INF;
            colMinX[i] = INF;
            rowMaxY[i] = -INF;
            colMaxX[i] = -INF;
        }

        // First pass: compute min/max for each row and column
        for (int[] b : buildings) {
            int x = b[0];
            int y = b[1];

            rowMinY[x] = Math.min(rowMinY[x], y);
            rowMaxY[x] = Math.max(rowMaxY[x], y);

            colMinX[y] = Math.min(colMinX[y], x);
            colMaxX[y] = Math.max(colMaxX[y], x);
        }

        // Second pass: count covered buildings
        int covered = 0;
        for (int[] b : buildings) {
            int x = b[0];
            int y = b[1];

            boolean hasLeft  = y > rowMinY[x];
            boolean hasRight = y < rowMaxY[x];
            boolean hasAbove = x > colMinX[y];
            boolean hasBelow = x < colMaxX[y];

            if (hasLeft && hasRight && hasAbove && hasBelow) {
                covered++;
            }
        }

        return covered;
    }
}