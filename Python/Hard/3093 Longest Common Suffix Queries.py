'''
You are given two arrays of strings wordsContainer and wordsQuery.

For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.

Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].

 

Example 1:

Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]

Output: [1,1,1]

Explanation:

Let's look at each wordsQuery[i] separately:

For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
Example 2:

Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]

Output: [2,0,2]

Explanation:

Let's look at each wordsQuery[i] separately:

For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
 

Constraints:

1 <= wordsContainer.length, wordsQuery.length <= 104
1 <= wordsContainer[i].length <= 5 * 103
1 <= wordsQuery[i].length <= 5 * 103
wordsContainer[i] consists only of lowercase English letters.
wordsQuery[i] consists only of lowercase English letters.
Sum of wordsContainer[i].length is at most 5 * 105.
Sum of wordsQuery[i].length is at most 5 * 105.
'''

class TrieNode:
    def __init__(self, best_index=-1):
        self.children = {}
        self.best_index = best_index

class Solution:
    def stringIndices(self, wordsContainer: list[str], wordsQuery: list[str]) -> list[int]:
        # Find the universal default fallback index
        global_best_index = 0
        for i in range(1, len(wordsContainer)):
            if len(wordsContainer[i]) < len(wordsContainer[global_best_index]):
                global_best_index = i
                
        root = TrieNode(global_best_index)

        # Build Trie with reversed strings
        for i, word in enumerate(wordsContainer):
            curr = root
            word_len = len(word)
            
            for char in reversed(word):
                if char not in curr.children:
                    curr.children[char] = TrieNode(i)
                curr = curr.children[char]
                
                # Update if the current word is shorter than the tracked best word
                if word_len < len(wordsContainer[curr.best_index]):
                    curr.best_index = i

        # Query Trie
        ans = []
        for query in wordsQuery:
            curr = root
            last_valid_best = root.best_index
            
            for char in reversed(query):
                if char not in curr.children:
                    break
                curr = curr.children[char]
                last_valid_best = curr.best_index
                
            ans.append(last_valid_best)
            
        return ans
