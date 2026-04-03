import java.util.*;

class Solution {
    public int maxWalls(int[] robots, int[] distance, int[] walls) {
        int n = robots.length;
        int[][] robotPairs = new int[n][2];
        for (int i = 0; i < n; i++) {
            robotPairs[i][0] = robots[i];
            robotPairs[i][1] = distance[i];
        }
        Arrays.sort(robotPairs, (a, b) -> Integer.compare(a[0], b[0]));
        Arrays.sort(walls);

        // dp[i][0] = max walls using first i robots, last robot fired Left or didn't fire
        // dp[i][1] = max walls using first i robots, last robot fired Right
        long[][] dp = new long[n + 1][2];

        for (int i = 0; i < n; i++) {
            int pos = robotPairs[i][0];
            int dist = robotPairs[i][1];

            // --- Option 1: Robot i fires LEFT ---
            int leftLimit = (i == 0) ? Integer.MIN_VALUE : robotPairs[i - 1][0] + 1;
            int leftReach = Math.max(leftLimit, pos - dist);
            int wallsLeft = countWallsInRange(walls, leftReach, pos);

            // If robot i-1 fired Right, we must only count walls NOT covered by i-1
            int prevRightReach = (i == 0) ? Integer.MIN_VALUE : Math.min(robotPairs[i][0] - 1, robotPairs[i-1][0] + robotPairs[i-1][1]);
            // Unique walls if prev was Right: walls in [max(leftReach, prevRightReach + 1), pos]
            int uniqueWallsLeftIfPrevRight = countWallsInRange(walls, Math.max(leftReach, prevRightReach + 1), pos);

            dp[i+1][0] = Math.max(dp[i][0] + wallsLeft, dp[i][1] + uniqueWallsLeftIfPrevRight);

            // --- Option 2: Robot i fires RIGHT ---
            int rightLimit = (i == n - 1) ? Integer.MAX_VALUE : robotPairs[i + 1][0] - 1;
            int rightReach = Math.min(rightLimit, pos + dist);
            int wallsRight = countWallsInRange(walls, pos, rightReach);

            // Firing right is always added to the best previous state
            dp[i+1][1] = Math.max(dp[i][0], dp[i][1]) + wallsRight;
            
            // Also consider the "don't fire" case to maintain the best base for next robot
            dp[i+1][0] = Math.max(dp[i+1][0], Math.max(dp[i][0], dp[i][1]));
        }

        return (int) Math.max(dp[n][0], dp[n][1]);
    }

    private int countWallsInRange(int[] walls, int start, int end) {
        if (start > end) return 0;
        int leftIdx = lowerBound(walls, start);
        int rightIdx = upperBound(walls, end);
        return Math.max(0, rightIdx - leftIdx);
    }

    private int lowerBound(int[] arr, int target) {
        int low = 0, high = arr.length;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] >= target) high = mid;
            else low = mid + 1;
        }
        return low;
    }

    private int upperBound(int[] arr, int target) {
        int low = 0, high = arr.length;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (arr[mid] <= target) low = mid + 1;
            else high = mid;
        }
        return low;
    }
}
