class Solution {
    public int[] countMentions(int numberOfUsers, List<List<String>> events) {
        int n = numberOfUsers;
        int m = events.size();

        // Convert timestamps to ints and pair with original index
        int[][] idxTime = new int[m][2];
        for (int i = 0; i < m; i++) {
            int t = Integer.parseInt(events.get(i).get(1));
            idxTime[i][0] = t;
            idxTime[i][1] = i;
        }

        // Sort events by (timestamp, originalIndex) to keep stable order within same timestamp
        Arrays.sort(idxTime, (a, b) -> {
            if (a[0] != b[0]) return Integer.compare(a[0], b[0]);
            return Integer.compare(a[1], b[1]);
        });

        boolean[] online = new boolean[n];
        Arrays.fill(online, true);

        // For each user, we may have multiple offline intervals; store as list of [start, end)
        List<int[]>[] offlineIntervals = new ArrayList[n];
        for (int i = 0; i < n; i++) offlineIntervals[i] = new ArrayList<>();

        // First pass: record offline intervals according to OFFLINE events
        for (int k = 0; k < m; k++) {
            int idx = idxTime[k][1];
            List<String> e = events.get(idx);
            String type = e.get(0);
            int t = Integer.parseInt(e.get(1));
            if (type.equals("OFFLINE")) {
                int id = Integer.parseInt(e.get(2));
                offlineIntervals[id].add(new int[]{t, t + 60});
            }
        }

        int[] mentions = new int[n];

        // Helper to refresh online status at current time
        // Users are online unless current time is inside any of their offline intervals.
        // Intervals are disjoint and sorted by construction order per problem guarantee.
        for (int k = 0; k < n; k++) {
            final List<int[]> list = offlineIntervals[k];
            list.sort(Comparator.comparingInt(a -> a[0]));
        }

        for (int kk = 0; kk < m; kk++) {
            int idx = idxTime[kk][1];
            List<String> e = events.get(idx);
            String type = e.get(0);
            int t = Integer.parseInt(e.get(1));

            // Update online array for all users at time t
            for (int u = 0; u < n; u++) {
                online[u] = true;
                for (int[] interval : offlineIntervals[u]) {
                    if (t >= interval[0] && t < interval[1]) {
                        online[u] = false;
                        break;
                    }
                    if (t < interval[0]) break;
                }
            }

            if (type.equals("MESSAGE")) {
                String msg = e.get(2);
                if (msg.equals("ALL")) {
                    // ALL: mention everyone, regardless of online
                    for (int u = 0; u < n; u++) {
                        mentions[u]++;
                    }
                } else if (msg.equals("HERE")) {
                    // HERE: mention all online users only
                    for (int u = 0; u < n; u++) {
                        if (online[u]) mentions[u]++;
                    }
                } else {
                    // List of explicit ids, space separated, possibly repeated
                    String[] tokens = msg.split(" ");
                    for (String token : tokens) {
                        if (token.startsWith("id")) {
                            int id = Integer.parseInt(token.substring(2));
                            mentions[id]++; // duplicates count multiple times
                        }
                    }
                }
            }
        }

        return mentions;
    }
}