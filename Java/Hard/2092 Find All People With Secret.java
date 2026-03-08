import java.util.*;

class Solution {

    static class DSU {
        int[] parent;
        int[] rank;

        DSU(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }

        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        void union(int x, int y) {
            int px = find(x);
            int py = find(y);
            if (px == py) return;

            if (rank[px] < rank[py]) {
                parent[px] = py;
            } else if (rank[px] > rank[py]) {
                parent[py] = px;
            } else {
                parent[py] = px;
                rank[px]++;
            }
        }

        void reset(int x) {
            parent[x] = x;
            rank[x] = 0;
        }
    }

    public List<Integer> findAllPeople(int n, int[][] meetings, int firstPerson) {
        DSU dsu = new DSU(n);

        // Person 0 shares the secret with firstPerson at time 0
        dsu.union(0, firstPerson);

        // Group meetings by time
        Map<Integer, List<int[]>> timeToMeetings = new HashMap<>();
        for (int[] m : meetings) {
            int x = m[0], y = m[1], t = m[2];
            timeToMeetings.computeIfAbsent(t, k -> new ArrayList<>()).add(new int[]{x, y});
        }

        // Process times in increasing order
        List<Integer> times = new ArrayList<>(timeToMeetings.keySet());
        Collections.sort(times);

        for (int t : times) {
            List<int[]> ms = timeToMeetings.get(t);

            // Track all people who participate at this time
            Set<Integer> participants = new HashSet<>();
            for (int[] m : ms) {
                int x = m[0], y = m[1];
                dsu.union(x, y);
                participants.add(x);
                participants.add(y);
            }

            // Roll back connections that are not connected to 0
            for (int p : participants) {
                if (dsu.find(p) != dsu.find(0)) {
                    dsu.reset(p);
                }
            }
        }

        List<Integer> ans = new ArrayList<>();
        int root0 = dsu.find(0);
        for (int i = 0; i < n; i++) {
            if (dsu.find(i) == root0) {
                ans.add(i);
            }
        }
        return ans;
    }
}