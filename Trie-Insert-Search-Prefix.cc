struct TrieNode {
    TrieNode* child[26];
    bool isEnd;
};

class Trie {
public:
    TrieNode* starts;
    Trie() {
        starts = newNode();
    }

    TrieNode* newNode() {
        TrieNode* node = new TrieNode();
        for(int i=0; i < 26; i++) {
            node->child[i] = NULL;
        }
        node->isEnd = false;
        return node;
    }    

    void insert(string word) {
        int n = word.length();
        TrieNode* cur = starts;
        for(int i=0; i < n; i++) {
            if(cur->child[word[i]-'a'] == NULL) {
                cur->child[word[i]-'a'] = newNode();
            }
            cur = cur->child[word[i]-'a'];
        }
        cur->isEnd = true;
    }
    
    bool search(string word) {
        int n = word.length();
        TrieNode* cur = starts;
        for(int i=0; i < n; i++) {
            if(cur->child[word[i]-'a'] == NULL)     return false;
            cur = cur->child[word[i]-'a'];
        }
        if(cur->isEnd == false) return false;
        return true;
    }
    
    bool startsWith(string word) {
        int n = word.length();
        TrieNode* cur = starts;
        for(int i=0; i < n; i++) {
            if(cur->child[word[i]-'a'] == NULL)     return false;
            cur = cur->child[word[i]-'a'];
        }        
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
