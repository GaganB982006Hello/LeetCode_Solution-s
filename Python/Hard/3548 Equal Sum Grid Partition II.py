from collections import Counter

class Solution:
    def canPartitionGrid(self, grid: list[list[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        total_sum = sum(sum(row) for row in grid)

        def check_section(s1, s2, freq, h, w, r_range, c_range):
            if s1 == s2: return True
            diff = s1 - s2
            if diff not in freq: return False
            
            # Connectivity Rule:
            # 1. If 2D (h > 1 and w > 1), any cell can be discounted.
            if h > 1 and w > 1: return True
            # 2. If 1D, only the two endpoints of the strip can be discounted.
            r1, r2 = r_range
            c1, c2 = c_range
            return grid[r1][c1] == diff or grid[r2][c2] == diff

        # --- Horizontal Cuts ---
        top_sum = 0
        top_freq = Counter()
        bot_freq = Counter(val for row in grid for val in row)
        
        for i in range(m - 1):
            for j in range(n):
                val = grid[i][j]
                top_sum += val
                top_freq[val] += 1
                bot_freq[val] -= 1
                if bot_freq[val] == 0: del bot_freq[val]
            
            bot_sum = total_sum - top_sum
            # Check if discounting from top or bottom works
            if check_section(top_sum, bot_sum, top_freq, i + 1, n, (0, i), (0, n - 1)): return True
            if check_section(bot_sum, top_sum, bot_freq, m - 1 - i, n, (i + 1, m - 1), (0, n - 1)): return True

        # --- Vertical Cuts ---
        left_sum = 0
        left_freq = Counter()
        right_freq = Counter(val for row in grid for val in row)

        for j in range(n - 1):
            for i in range(m):
                val = grid[i][j]
                left_sum += val
                left_freq[val] += 1
                right_freq[val] -= 1
                if right_freq[val] == 0: del right_freq[val]
            
            right_sum = total_sum - left_sum
            if check_section(left_sum, right_sum, left_freq, m, j + 1, (0, m - 1), (0, j)): return True
            if check_section(right_sum, left_sum, right_freq, m, n - 1 - j, (0, m - 1), (j + 1, n - 1)): return True

        return False
