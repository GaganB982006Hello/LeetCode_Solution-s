import java.util.Arrays;

class Solution {
    static class UnionFind {
        int[] parent;
        int[] rank;

        public UnionFind(int n) {
            parent = new int[n];
            rank = new int[n];
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        public int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        public boolean union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX == rootY) return false;
            
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return true;
        }
    }

    public int maxStability(int n, int[][] edges, int k) {
        UnionFind uf = new UnionFind(n);
        int cnt = 0;
        int minStrength = Integer.MAX_VALUE;

        // Pass 1: Add all mandatory edges
        for (int[] edge : edges) {
            if (edge[3] == 0) continue;
            if (!uf.union(edge[0], edge[1])) return -1;
            cnt++;
            minStrength = Math.min(minStrength, edge[2]);
        }

        // Sort remaining optional edges in descending order by strength
        Arrays.sort(edges, (a, b) -> Integer.compare(b[2], a[2]));

        // Pass 2: Fill in the remaining needed components 
        for (int[] edge : edges) {
            if (edge[3] == 1) continue;
            if (!uf.union(edge[0], edge[1])) continue;
            cnt++;
            
            if (cnt == (n - 1) - k) {
                minStrength = Math.min(minStrength, edge[2]);
            } else if (cnt == n - 1) {
                minStrength = Math.min(minStrength, 2 * edge[2]);
            }
        }

        return (cnt == n - 1) ? minStrength : -1;
    }
}
