/*
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
*/

#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    struct TrieNode* children[26];
    int bestIndex;
} TrieNode;

TrieNode* createNode(int defaultIdx) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->bestIndex = defaultIdx;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// Helper function to safely free allocated Trie memory
void freeTrie(TrieNode* root) {
    if (!root) return;
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            freeTrie(root->children[i]);
        }
    }
    free(root);
}

int* stringIndices(char** wordsContainer, int wordsContainerSize, char** wordsQuery, int wordsQuerySize, int* returnSize) {
    int globalBestIndex = 0;
    int minLen = strlen(wordsContainer[0]);

    // Find the default global minimum length string
    for (int i = 1; i < wordsContainerSize; i++) {
        int len = strlen(wordsContainer[i]);
        if (len < minLen) {
            minLen = len;
            globalBestIndex = i;
        }
    }

    TrieNode* root = createNode(globalBestIndex);

    // Build the Trie
    for (int i = 0; i < wordsContainerSize; i++) {
        char* word = wordsContainer[i];
        int len = strlen(word);
        TrieNode* curr = root;

        for (int j = len - 1; j >= 0; j--) {
            int charIdx = word[j] - 'a';
            if (curr->children[charIdx] == NULL) {
                curr->children[charIdx] = createNode(i);
            }
            curr = curr->children[charIdx];

            // Compare lengths to preserve the shortest/earliest index
            int currBestLen = strlen(wordsContainer[curr->bestIndex]);
            if (len < currBestLen) {
                curr->bestIndex = i;
            }
        }
    }

    // Process Queries
    int* ans = (int*)malloc(wordsQuerySize * sizeof(int));
    *returnSize = wordsQuerySize;

    for (int i = 0; i < wordsQuerySize; i++) {
        char* query = wordsQuery[i];
        int len = strlen(query);
        TrieNode* curr = root;
        int lastValidBestIndex = root->bestIndex;

        for (int j = len - 1; j >= 0; j--) {
            int charIdx = query[j] - 'a';
            if (curr->children[charIdx] == NULL) {
                break;
            }
            curr = curr->children[charIdx];
            lastValidBestIndex = curr->bestIndex;
        }
        ans[i] = lastValidBestIndex;
    }

    freeTrie(root);
    return ans;
}
