class Solution:
    def twoSum(self, nums: list[int], target: int) -> list[int]:
        # Dictionary to store the number and its corresponding index
        num_map = {}
        
        for i, num in enumerate(nums):
            complement = target - num
            
            # If the complement exists in our map, we have our answer
            if complement in num_map:
                return [num_map[complement], i]
            
            # Otherwise, add the current number and index to the map
            num_map[num] = i
            
        return [] # Fallback (though the problem guarantees one valid answer)
