import java.util.Arrays;

class Solution {
    public long maxRunTime(int n, int[] batteries) {
        // Total sum of all battery capacities
        long sum = 0;
        for (int b : batteries) {
            sum += b;
        }

        // Sort batteries to process the largest ones last
        Arrays.sort(batteries);

        int m = batteries.length;
        int i = m - 1;

        // Greedily remove overly large batteries
        // If the largest battery is greater than the current average sum/n,
        // it cannot be fully used without wasting some capacity.
        // So, treat that largest battery as powering a computer alone and
        // reduce the problem size.
        while (n > 0 && batteries[i] > sum / n) {
            sum -= batteries[i];
            i--;
            n--;
        }

        // Now every remaining battery is <= sum/n,
        // so we can distribute total capacity evenly.
        return sum / n;
    }
}
