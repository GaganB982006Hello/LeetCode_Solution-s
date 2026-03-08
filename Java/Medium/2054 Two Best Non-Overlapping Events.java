import java.util.*;

class Solution {
    public int maxTwoEvents(int[][] events) {
        int n = events.length;

        // Sort by start time
        Arrays.sort(events, (a, b) -> Integer.compare(a[0], b[0]));

        int[] starts = new int[n];
        for (int i = 0; i < n; i++) {
            starts[i] = events[i][0];
        }

        // suffixMax[i] = max value from event i to n-1
        int[] suffixMax = new int[n + 1];
        suffixMax[n] = 0;
        for (int i = n - 1; i >= 0; i--) {
            suffixMax[i] = Math.max(suffixMax[i + 1], events[i][2]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            int end = events[i][1];
            int val = events[i][2];

            // Binary search for first event with start > end
            int j = upperBound(starts, end);

            // Take current event alone
            ans = Math.max(ans, val);

            // Take current + best non-overlapping event
            if (j < n) {
                ans = Math.max(ans, val + suffixMax[j]);
            }
        }

        return ans;
    }

    // First index with array[idx] > target
    private int upperBound(int[] arr, int target) {
        int l = 0, r = arr.length; // [l, r)
        while (l < r) {
            int m = l + (r - l) / 2;
            if (arr[m] <= target) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        return l;
    }
}