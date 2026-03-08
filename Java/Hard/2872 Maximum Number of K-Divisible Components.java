import java.util.*;

class Solution {
    private long kGlobal;
    private int ans;

    private long dfs(int u, int parent, List<List<Integer>> adj, int[] values) {
        long sum = values[u];
        for (int v : adj.get(u)) {
            if (v == parent) continue;
            sum += dfs(v, u, adj, values);
        }
        if (sum % kGlobal == 0) {
            ans++;       // this subtree can be cut as a component
            return 0;    // cut here, so contribute 0 to parent
        }
        return sum;      // pass partial sum up
    }

    public int maxKDivisibleComponents(int n, int[][] edges, int[] values, int k) {
        kGlobal = k;
        ans = 0;

        List<List<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        for (int[] e : edges) {
            int a = e[0], b = e[1];
            adj.get(a).add(b);
            adj.get(b).add(a);
        }

        dfs(0, -1, adj, values);
        return ans;
    }
}
