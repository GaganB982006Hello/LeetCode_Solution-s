class Solution {
    private Map<String, List<Character>> transitions = new HashMap<>();
    
    public boolean pyramidTransition(String bottom, List<String> allowed) {
        // Build transition map: key = bottom two chars, value = possible top chars
        for (String pattern : allowed) {
            String key = pattern.substring(0, 2);
            char top = pattern.charAt(2);
            transitions.computeIfAbsent(key, k -> new ArrayList<>()).add(top);
        }
        
        // Start building from bottom row
        return canBuild(bottom);
    }
    
    private boolean canBuild(String row) {
        // Base case: single block reaches the top
        if (row.length() == 1) {
            return true;
        }
        
        // Try all possible next rows
        List<String> nextRows = generateNextRows(row);
        for (String nextRow : nextRows) {
            if (canBuild(nextRow)) {
                return true;
            }
        }
        return false;
    }
    
    private List<String> generateNextRows(String row) {
        List<String> nextRows = new ArrayList<>();
        generateNextRows(row, 0, new StringBuilder(), nextRows);
        return nextRows;
    }
    
    private void generateNextRows(String row, int index, StringBuilder nextRow, List<String> result) {
        // If we've built the entire next row
        if (index == row.length() - 1) {
            result.add(nextRow.toString());
            return;
        }
        
        // Get the two bottom blocks for this position
        String key = row.substring(index, index + 2);
        List<Character> possibleTops = transitions.getOrDefault(key, new ArrayList<>());
        
        // Try each possible top block
        for (char top : possibleTops) {
            nextRow.append(top);
            generateNextRows(row, index + 1, nextRow, result);
            nextRow.deleteCharAt(nextRow.length() - 1); // backtrack
        }
    }
}