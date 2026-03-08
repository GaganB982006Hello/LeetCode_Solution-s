import java.util.*;

class Solution {
    public List<String> validateCoupons(String[] code, String[] businessLine, boolean[] isActive) {
        List<Integer> validIndices = new ArrayList<>();
        Map<String, Integer> priorityMap = new HashMap<>();
        priorityMap.put("electronics", 0);
        priorityMap.put("grocery", 1);
        priorityMap.put("pharmacy", 2);
        priorityMap.put("restaurant", 3);
        for (int i = 0; i < code.length; i++) {
            String c = code[i];
            String b = businessLine[i];
            boolean active = isActive[i];
            if (active && priorityMap.containsKey(b) && isValidCode(c)) {
                validIndices.add(i);
            }
        }
        Collections.sort(validIndices, (i, j) -> {
            int priority1 = priorityMap.get(businessLine[i]);
            int priority2 = priorityMap.get(businessLine[j]);

            if (priority1 != priority2) {
                return Integer.compare(priority1, priority2);
            } else {
                return code[i].compareTo(code[j]);
            }
        });
        List<String> result = new ArrayList<>();
        for (int index : validIndices) {
            result.add(code[index]);
        }

        return result;
    }
    private boolean isValidCode(String s) {
        if (s == null || s.isEmpty()) return false;
        
        for (char c : s.toCharArray()) {
            if (!Character.isLetterOrDigit(c) && c != '_') {
                return false;
            }
        }
        return true;
    }
}