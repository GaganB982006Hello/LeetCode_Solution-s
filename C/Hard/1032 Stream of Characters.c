/*
Design an algorithm that accepts a stream of characters and checks if a suffix of these characters is a string of a given array of strings words.

For example, if words = ["abc", "xyz"] and the stream added the four characters (one by one) 'a', 'x', 'y', and 'z', your algorithm should detect that the suffix "xyz" of the characters "axyz" matches "xyz" from words.

Implement the StreamChecker class:

StreamChecker(String[] words) Initializes the object with the strings array words.
boolean query(char letter) Accepts a new character from the stream and returns true if any non-empty suffix from the stream forms a word that is in words.
 

Example 1:

Input
["StreamChecker", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query", "query"]
[[["cd", "f", "kl"]], ["a"], ["b"], ["c"], ["d"], ["e"], ["f"], ["g"], ["h"], ["i"], ["j"], ["k"], ["l"]]
Output
[null, false, false, false, true, false, true, false, false, false, false, false, true]

Explanation
StreamChecker streamChecker = new StreamChecker(["cd", "f", "kl"]);
streamChecker.query("a"); // return False
streamChecker.query("b"); // return False
streamChecker.query("c"); // return False
streamChecker.query("d"); // return True, because 'cd' is in the wordlist
streamChecker.query("e"); // return False
streamChecker.query("f"); // return True, because 'f' is in the wordlist
streamChecker.query("g"); // return False
streamChecker.query("h"); // return False
streamChecker.query("i"); // return False
streamChecker.query("j"); // return False
streamChecker.query("k"); // return False
streamChecker.query("l"); // return True, because 'kl' is in the wordlist
 

Constraints:

1 <= words.length <= 2000
1 <= words[i].length <= 200
words[i] consists of lowercase English letters.
letter is a lowercase English letter.
At most 4 * 104 calls will be made to query.
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    struct TrieNode* children[26];
    bool isWord;
} TrieNode;

typedef struct {
    TrieNode* root;
    char* stream;
    int stream_size;
    int stream_capacity;
} StreamChecker;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isWord = false;
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    return node;
}

StreamChecker* streamCheckerCreate(char** words, int wordsSize) {
    StreamChecker* obj = (StreamChecker*)malloc(sizeof(StreamChecker));
    obj->root = createNode();
    
    // Allocate space for the maximum number of queries
    obj->stream_capacity = 40005; 
    obj->stream = (char*)malloc(sizeof(char) * obj->stream_capacity);
    obj->stream_size = 0;

    // Build the Trie in reverse
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        TrieNode* node = obj->root;
        for (int j = len - 1; j >= 0; j--) {
            int index = words[i][j] - 'a';
            if (node->children[index] == NULL) {
                node->children[index] = createNode();
            }
            node = node->children[index];
        }
        node->isWord = true;
    }
    return obj;
}

bool streamCheckerQuery(StreamChecker* obj, char letter) {
    obj->stream[obj->stream_size++] = letter;
    TrieNode* node = obj->root;
    
    // Iterate backward through the stream, limiting to the max word length (200)
    int limit = obj->stream_size - 200;
    if (limit < 0) limit = 0;

    for (int i = obj->stream_size - 1; i >= limit; i--) {
        int index = obj->stream[i] - 'a';
        if (node->children[index] == NULL) {
            return false;
        }
        node = node->children[index];
        if (node->isWord) {
            return true;
        }
    }
    return false;
}

void freeTrie(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < 26; i++) {
        if (node->children[i]) {
            freeTrie(node->children[i]);
        }
    }
    free(node);
}

void streamCheckerFree(StreamChecker* obj) {
    if (obj) {
        freeTrie(obj->root);
        free(obj->stream);
        free(obj);
    }
}
