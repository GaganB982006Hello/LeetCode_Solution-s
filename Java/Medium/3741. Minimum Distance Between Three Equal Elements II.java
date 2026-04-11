import java.util.*;

class Solution {
    public int minimumDistance(int[] nums) {
        // Map to store value -> list of indices where it appears
        Map<Integer, List<Integer>> indexMap = new HashMap<>();
        
        for (int i = 0; i < nums.length; i++) {
            indexMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        
        long minDistance = Long.MAX_VALUE;
        boolean found = false;
        
        for (List<Integer> indices : indexMap.values()) {
            // A "good tuple" requires at least 3 occurrences
            if (indices.size() < 3) continue;
            
            // Check every three consecutive indices
            for (int i = 0; i <= indices.size() - 3; i++) {
                int first = indices.get(i);
                int third = indices.get(i + 2);
                
                // Formula: 2 * (max_index - min_index)
                long currentDist = 2L * (third - first);
                minDistance = Math.min(minDistance, currentDist);
                found = true;
            }
        }
        
        return found ? (int) minDistance : -1;
    }
}
