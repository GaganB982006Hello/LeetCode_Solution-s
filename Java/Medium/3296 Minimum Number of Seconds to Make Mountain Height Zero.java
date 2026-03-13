class Solution {
    public long minNumberOfSeconds(int mountainHeight, int[] workerTimes) {
        long l = 1;
        long minWorkerTime = workerTimes[0];
        for (int t : workerTimes) {
            minWorkerTime = Math.min(minWorkerTime, t);
        }
        
        // Worst-case upper bound assuming the fastest worker does all the work
        long r = minWorkerTime * (long) mountainHeight * (mountainHeight + 1) / 2;
        
        while (l < r) {
            long mid = l + (r - l) / 2;
            if (getReducedHeight(workerTimes, mid) < mountainHeight) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        return l;
    }
    
    private long getReducedHeight(int[] workerTimes, long m) {
        long reducedHeight = 0;
        for (int w : workerTimes) {
            // Using the quadratic formula to find the max height reduced in 'm' seconds
            reducedHeight += (long) ((-1 + Math.sqrt(1 + 8.0 * (double) m / w)) / 2);
        }
        return reducedHeight;
    }
}
