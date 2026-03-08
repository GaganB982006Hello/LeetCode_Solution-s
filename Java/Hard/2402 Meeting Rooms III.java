import java.util.*;

class Solution {
    public int mostBooked(int n, int[][] meetings) {
        // Sort meetings by start time
        Arrays.sort(meetings, (a, b) -> Long.compare(a[0], b[0]));  // use Long.compare to be safe [page:1]

        // Min-heap of free rooms by index
        PriorityQueue<Integer> free = new PriorityQueue<>();
        for (int i = 0; i < n; i++) free.offer(i);  // initially all rooms free [page:1]

        // Min-heap of ongoing meetings: [endTime, roomIndex]
        PriorityQueue<long[]> busy = new PriorityQueue<>(
            (a, b) -> a[0] == b[0] ? Long.compare(a[1], b[1]) : Long.compare(a[0], b[0])
        );  // tie on endTime -> smaller room index [page:1]

        long[] count = new long[n];  // number of meetings per room [page:1]

        for (int[] m : meetings) {
            long start = m[0];
            long end = m[1];
            long duration = end - start;  // meeting duration [page:1]

            // Free all rooms whose meeting has finished by 'start'
            while (!busy.isEmpty() && busy.peek()[0] <= start) {
                long[] finished = busy.poll();
                free.offer((int) finished[1]);  // that room becomes free [page:1]
            }

            if (!free.isEmpty()) {
                // Assign to smallest-index free room, starting at original start
                int room = free.poll();
                long newEnd = start + duration;
                busy.offer(new long[]{newEnd, room});
                count[room]++;  // increment usage [page:1]
            } else {
                // No room free; delay meeting to earliest finishing room
                long[] earliest = busy.poll();
                long curEnd = earliest[0];
                int room = (int) earliest[1];

                long newEnd = curEnd + duration;  // delayed, same duration [page:1]
                busy.offer(new long[]{newEnd, room});
                count[room]++;
            }
        }

        // Find room with maximum number of meetings, tie -> smaller index
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (count[i] > count[ans]) {
                ans = i;
            }
        }
        return ans;
    }
}