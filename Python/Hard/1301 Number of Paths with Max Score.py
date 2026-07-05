# You are given a square board of characters. You can move on the board starting at the bottom right square marked with the character 'S'.

# You need to reach the top left square marked with the character 'E'. The rest of the squares are labeled either with a numeric character 1, 2, ..., 9 or with an obstacle 'X'. In one move you can go up, left or up-left (diagonally) only if there is no obstacle there.

#Return a list of two integers: the first integer is the maximum sum of numeric characters you can collect, and the second is the number of such paths that you can take to get that maximum sum, taken modulo 10^9 + 7.

#In case there is no path, return [0, 0].

 

#Example 1:

#Input: board = ["E23","2X2","12S"]
#Output: [7,1]
#Example 2:

#Input: board = ["E12","1X1","21S"]
#Output: [4,2]
#Example 3:

#Input: board = ["E11","XXX","11S"]
#Output: [0,0]
 

#Constraints:

#2 <= board.length == board[i].length <= 100

class Solution:
    def pathsWithMaxScore(self, board: List[str]) -> List[int]:
        n = len(board)
        MOD = 10**9 + 7
        
        # dp[r][c] stores the max score from (n-1, n-1) to (r, c)
        # Pad with an extra row and column to easily handle boundaries
        dp = [[-1] * (n + 1) for _ in range(n + 1)]
        
        # count[r][c] stores the number of paths achieving dp[r][c]
        count = [[0] * (n + 1) for _ in range(n + 1)]
        
        # Start at the bottom right
        dp[n-1][n-1] = 0
        count[n-1][n-1] = 1
        
        # Iterate from bottom-right to top-left
        for r in range(n - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                # Skip the starting point as it's already initialized
                if r == n - 1 and c == n - 1:
                    continue
                
                # Obstacles cannot be visited
                if board[r][c] == 'X':
                    continue
                
                # Find the maximum score among valid previous steps (Down, Right, Down-Right)
                max_prev = max(dp[r+1][c], dp[r][c+1], dp[r+1][c+1])
                
                if max_prev != -1:
                    # Treat 'E' as 0, otherwise convert the string digit to an integer
                    val = int(board[r][c]) if board[r][c] not in "SE" else 0
                    dp[r][c] = max_prev + val
                    
                    # Accumulate path counts from neighbors that yielded the max_prev
                    if max_prev == dp[r+1][c]:
                        count[r][c] = (count[r][c] + count[r+1][c]) % MOD
                    if max_prev == dp[r][c+1]:
                        count[r][c] = (count[r][c] + count[r][c+1]) % MOD
                    if max_prev == dp[r+1][c+1]:
                        count[r][c] = (count[r][c] + count[r+1][c+1]) % MOD
                        
        # If the destination cell dp[0][0] is still -1, it means there's no valid path
        return [dp[0][0] if dp[0][0] != -1 else 0, count[0][0]]
