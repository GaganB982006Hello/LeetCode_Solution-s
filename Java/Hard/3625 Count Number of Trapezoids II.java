import java.util.*;

class Solution {
    public int countTrapezoids(int[][] points) {
        int n = points.length;
        if (n < 4) return 0;

        // 1. Map for Trapezoids: Slope -> Intercept -> Count
        Map<String, Map<Long, Integer>> slopeMap = new HashMap<>();
        
        // 2. Map for Parallelograms: Midpoint -> Slope -> Count
        // We need the inner map (Slope->Count) to filter out collinear segments sharing a midpoint
        Map<String, Map<String, Integer>> midpointMap = new HashMap<>();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];

                // --- Slope Calculation ---
                int dy = y1 - y2;
                int dx = x1 - x2;
                
                int g = gcd(Math.abs(dy), Math.abs(dx));
                dy /= g;
                dx /= g;

                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }
                String slopeKey = dy + "_" + dx;

                // --- Trapezoid Logic (Intercept) ---
                long intercept = (long) dy * x1 - (long) dx * y1;
                slopeMap.putIfAbsent(slopeKey, new HashMap<>());
                Map<Long, Integer> linesForSlope = slopeMap.get(slopeKey);
                linesForSlope.put(intercept, linesForSlope.getOrDefault(intercept, 0) + 1);

                // --- Parallelogram Logic (Midpoint) ---
                // Key: "sumX_sumY" (representing 2 * midpoint)
                String midKey = (x1 + x2) + "_" + (y1 + y2);
                midpointMap.putIfAbsent(midKey, new HashMap<>());
                Map<String, Integer> slopesAtMidpoint = midpointMap.get(midKey);
                slopesAtMidpoint.put(slopeKey, slopesAtMidpoint.getOrDefault(slopeKey, 0) + 1);
            }
        }

        long totalTrapezoids = 0;

        // 1. Calculate Trapezoids (counts each parallelogram TWICE)
        for (Map<Long, Integer> lines : slopeMap.values()) {
            if (lines.size() < 2) continue; // Need at least 2 distinct parallel lines
            
            long sum = 0;
            long sqSum = 0;

            for (int count : lines.values()) {
                sum += count;
                sqSum += (long) count * count;
            }
            // Sum of products of all pairs
            totalTrapezoids += (sum * sum - sqSum) / 2;
        }

        // 2. Calculate Valid Parallelograms (to subtract)
        long parallelogramCount = 0;
        for (Map<String, Integer> slopes : midpointMap.values()) {
            long totalSegmentsAtMidpoint = 0;
            long collinearPairs = 0;

            for (int count : slopes.values()) {
                totalSegmentsAtMidpoint += count;
                // These are pairs of segments sharing midpoint AND slope -> Collinear (Degenerate)
                collinearPairs += (long) count * (count - 1) / 2;
            }

            // Total pairs sharing this midpoint
            long totalPairs = totalSegmentsAtMidpoint * (totalSegmentsAtMidpoint - 1) / 2;
            
            // Valid parallelograms = Total Pairs - Collinear Pairs
            parallelogramCount += (totalPairs - collinearPairs);
        }

        return (int) (totalTrapezoids - parallelogramCount);
    }

    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}