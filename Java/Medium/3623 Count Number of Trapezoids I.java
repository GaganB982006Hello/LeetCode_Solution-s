class Solution {
    private static final long MOD = 1_000_000_007L;
    
    public int countTrapezoids(int[][] points) {
        // Group points by y-coordinate
        Map<Integer, Integer> countByY = new HashMap<>();
        for (int[] p : points) {
            int y = p[1];
            countByY.put(y, countByY.getOrDefault(y, 0) + 1);
        }
        
        // Get sorted y-levels
        List<Integer> yLevels = new ArrayList<>(countByY.keySet());
        Collections.sort(yLevels);
        
        long result = 0;
        long sum = 0;        // Sum of all C(count, 2) for previous levels
        
        for (int y : yLevels) {
            int count = countByY.get(y);
            // C(count, 2) = count * (count - 1) / 2
            long segments = (long) count * (count - 1) / 2;
            
            // Add combinations: segments * sum (multiply with all previous)
            result = (result + segments * sum % MOD) % MOD;
            
            // Update for next iteration
            sum = (sum + segments) % MOD;
        }
        
        return (int) result;
    }
}