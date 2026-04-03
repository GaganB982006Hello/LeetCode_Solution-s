import bisect

class Solution:
    def maxWalls(self, robots, distance, walls):
        # Sort walls for binary search
        walls.sort()
        
        # Sort robots by position and keep distances paired
        robot_data = sorted(zip(robots, distance))
        n = len(robot_data)
        
        # dp[i][0] -> last robot fired Left or Idle
        # dp[i][1] -> last robot fired Right
        dp = [[0, 0] for _ in range(n + 1)]
        
        for i in range(n):
            pos, dist = robot_data[i]
            
            # --- Option 1: Fire Left ---
            left_limit = robot_data[i-1][0] + 1 if i > 0 else -float('inf')
            l_reach = max(pos - dist, left_limit)
            walls_l = bisect.bisect_right(walls, pos) - bisect.bisect_left(walls, l_reach)
            
            # If previous robot fired Right, we only count unique walls
            prev_r_reach = min(pos - 1, robot_data[i-1][0] + robot_data[i-1][1]) if i > 0 else -float('inf')
            unique_l = bisect.bisect_right(walls, pos) - bisect.bisect_left(walls, max(l_reach, prev_r_reach + 1))
            
            dp[i+1][0] = max(dp[i][0] + walls_l, dp[i][1] + unique_l)
            
            # --- Option 2: Fire Right ---
            right_limit = robot_data[i+1][0] - 1 if i < n - 1 else float('inf')
            r_reach = min(pos + dist, right_limit)
            walls_r = bisect.bisect_right(walls, r_reach) - bisect.bisect_left(walls, pos)
            
            dp[i+1][1] = max(dp[i][0], dp[i][1]) + walls_r
            
            # Maintain the best "not firing right" state
            dp[i+1][0] = max(dp[i+1][0], dp[i][0], dp[i][1])
            
        return max(dp[n])
