class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rx, ry = self.find(x), self.find(y)
        if rx == ry: 
            return False
        if self.rank[rx] > self.rank[ry]:
            self.parent[ry] = rx
        elif self.rank[rx] < self.rank[ry]:
            self.parent[rx] = ry
        else:
            self.parent[ry] = rx
            self.rank[rx] += 1
        return True

class Solution:
    def maxStability(self, n: int, edges: list[list[int]], k: int) -> int:
        uf = UnionFind(n)
        cnt = 0
        min_s = float('inf')
        
        # Pass 1: Add all mandatory edges
        for u, v, s, m in edges:
            if m == 0: 
                continue
            if not uf.union(u, v): 
                return -1 # Cycle detected in mandatory edges
            cnt += 1
            min_s = min(min_s, s)
            
        # Pass 2: Sort optional edges descending
        edges.sort(key=lambda x: x[2], reverse=True)
        
        for u, v, s, m in edges:
            if m == 1: 
                continue
            if not uf.union(u, v): 
                continue
            cnt += 1
            
            # Tracking the bottleneck of un-upgraded vs upgraded edges
            if cnt == (n - 1) - k:
                min_s = min(min_s, s)
            elif cnt == n - 1:
                min_s = min(min_s, 2 * s)
                
        return min_s if cnt == n - 1 else -1
