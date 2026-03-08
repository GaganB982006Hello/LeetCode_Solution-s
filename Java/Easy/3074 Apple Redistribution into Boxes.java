import java.util.Arrays;

class Solution {
    public int minimumBoxes(int[] apple, int[] capacity) {
        // 1. Calculate the total number of apples
        int totalApples = 0;
        for (int a : apple) {
            totalApples += a;
        }

        // 2. Sort capacities to use a greedy approach (largest boxes first)
        Arrays.sort(capacity);

        int boxesUsed = 0;
        // 3. Iterate from the end of the sorted capacity array
        for (int i = capacity.length - 1; i >= 0; i--) {
            totalApples -= capacity[i];
            boxesUsed++;

            // 4. If all apples are packed, return the count
            if (totalApples <= 0) {
                return boxesUsed;
            }
        }

        return boxesUsed;
    }
}