import java.util.*;

class Solution {
    private List<List<Integer>> adj;
    private int[] present;
    private int[] future;
    private int budget;

    public int maxProfit(int n, int[] present, int[] future, int[][] hierarchy, int budget) {
        this.present = present;
        this.future = future;
        this.budget = budget;
        
        // Build the tree (Adjacency List)
        // Adjust 1-based IDs to 0-based indices for implementation
        adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }
        
        // hierarchy[i] = [boss, subordinate]
        // Since input IDs are 1-based, we map to 0-based
        for (int[] relation : hierarchy) {
            int u = relation[0] - 1;
            int v = relation[1] - 1;
            adj.get(u).add(v);
        }

        // Run Tree DP starting from CEO (Employee 1 -> Index 0)
        // Result is dp[budget] assuming the "super-parent" of CEO didn't buy (context 0)
        int[][] result = dfs(0);
        
        // The answer is the max profit found in the context where the CEO's parent 
        // (which doesn't exist) didn't buy.
        int maxProfit = 0;
        for (int p : result[0]) {
            maxProfit = Math.max(maxProfit, p);
        }
        return maxProfit;
    }

    // Returns int[2][budget + 1]
    // res[0] = DP table if parent of u did NOT buy
    // res[1] = DP table if parent of u DID buy
    private int[][] dfs(int u) {
        // Base arrays for children merging
        // We start with 0 cost and 0 profit.
        // We use -1 or effectively ignore unreached states, but since we want to maximize,
        // initialized 0s (default) work for reachable states if we carefully handle iteration.
        // Better: Initialize valid states. Here standard knapsack array is fine.
        
        int[] childrenNoBuy = new int[budget + 1]; // Combined children DP if u NOT bought
        int[] childrenBuy = new int[budget + 1];   // Combined children DP if u BOUGHT
        
        // To optimize, we can track the max cost seen so far to bound loops, 
        // but typically budget <= 2000 allows O(Budget) inner loops.
        
        // Process all children
        for (int v : adj.get(u)) {
            int[][] childRes = dfs(v);
            
            // Merge child v's results into our accumulated children arrays
            // This is the standard "Knapsack Merge" operation: dp[w] = max(dp[w], dp[w-k] + child[k])
            
            int[] nextChildrenNoBuy = Arrays.copyOf(childrenNoBuy, budget + 1);
            int[] nextChildrenBuy = Arrays.copyOf(childrenBuy, budget + 1);
            
            for (int w = budget; w >= 0; w--) {
                for (int k = 0; k <= w; k++) {
                    // Merging for "u not bought" context -> child sees parent not bought (childRes[0])
                    nextChildrenNoBuy[w] = Math.max(nextChildrenNoBuy[w], childrenNoBuy[w - k] + childRes[0][k]);
                    
                    // Merging for "u bought" context -> child sees parent bought (childRes[1])
                    nextChildrenBuy[w] = Math.max(nextChildrenBuy[w], childrenBuy[w - k] + childRes[1][k]);
                }
            }
            childrenNoBuy = nextChildrenNoBuy;
            childrenBuy = nextChildrenBuy;
        }

        int[][] res = new int[2][budget + 1];
        
        // Costs and profits for current node u
        int costFull = present[u];
        int profitFull = future[u] - present[u];
        
        int costDisc = present[u] / 2;
        int profitDisc = future[u] - costDisc;

        // Fill res[0] (Parent did NOT buy u)
        for (int w = 0; w <= budget; w++) {
            // Option 1: Don't buy u
            // Cost 0 added to childrenNoBuy
            int val = childrenNoBuy[w];
            
            // Option 2: Buy u (Full Price)
            // Cost 'costFull' added to childrenBuy
            if (w >= costFull) {
                val = Math.max(val, profitFull + childrenBuy[w - costFull]);
            }
            res[0][w] = val;
        }

        // Fill res[1] (Parent DID buy u)
        for (int w = 0; w <= budget; w++) {
            // Option 1: Don't buy u
            // Cost 0 added to childrenNoBuy (Identical to above case)
            int val = childrenNoBuy[w];
            
            // Option 2: Buy u (Discounted Price)
            // Cost 'costDisc' added to childrenBuy
            if (w >= costDisc) {
                val = Math.max(val, profitDisc + childrenBuy[w - costDisc]);
            }
            res[1][w] = val;
        }
        
        return res;
    }
}