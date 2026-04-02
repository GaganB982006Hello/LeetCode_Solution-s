class Solution {
    public List<Integer> survivedRobotsHealths(int[] positions, int[] healths, String directions) {
        int n = positions.length;
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) indices[i] = i;

        // Sort indices based on their positions
        Arrays.sort(indices, (a, b) -> Integer.compare(positions[a], positions[b]));

        Deque<Integer> stack = new ArrayDeque<>();
        for (int i : indices) {
            if (directions.charAt(i) == 'R') {
                stack.push(i);
            } else {
                // Robot moving Left: check for collisions with Right-moving robots in stack
                while (!stack.isEmpty() && healths[i] > 0) {
                    int top = stack.peek();
                    if (healths[top] < healths[i]) {
                        // Right-moving robot destroyed
                        healths[i]--;
                        healths[top] = 0;
                        stack.pop();
                    } else if (healths[top] > healths[i]) {
                        // Left-moving robot destroyed
                        healths[top]--;
                        healths[i] = 0;
                    } else {
                        // Both destroyed
                        healths[i] = 0;
                        healths[top] = 0;
                        stack.pop();
                    }
                }
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int h : healths) {
            if (h > 0) result.add(h);
        }
        return result;
    }
}
