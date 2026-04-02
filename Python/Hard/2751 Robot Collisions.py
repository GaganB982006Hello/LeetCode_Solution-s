class Solution:
    def survivedRobotsHealths(self, positions: List[int], healths: List[int], directions: str) -> List[int]:
        n = len(positions)
        # Create a list of indices and sort them based on their positions
        robots = sorted(range(n), key=lambda i: positions[i])
        
        stack = []  # To store indices of robots moving 'R'
        
        for i in robots:
            if directions[i] == 'R':
                stack.append(i)
            else:
                # Robot is moving 'L', check for collisions with 'R' robots in stack
                while stack and healths[i] > 0:
                    top_idx = stack[-1]
                    
                    if healths[top_idx] < healths[i]:
                        # Left robot wins, Right robot destroyed
                        healths[top_idx] = 0
                        healths[i] -= 1
                        stack.pop()
                    elif healths[top_idx] > healths[i]:
                        # Right robot wins, Left robot destroyed
                        healths[top_idx] -= 1
                        healths[i] = 0
                    else:
                        # Both destroyed
                        healths[top_idx] = 0
                        healths[i] = 0
                        stack.pop()
        
        # Return healths of survivors in their original input order
        return [h for h in healths if h > 0]
