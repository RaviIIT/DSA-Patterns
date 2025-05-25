#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <algorithm>

using namespace std;

class Trie {
public:
    string name;
    bool isFile = false;
    string content;
    unordered_map<string, Trie*> children;

    Trie* insert(const string& path, bool isFileFlag) {
        Trie* node = this;
        vector<string> ps = split(path, '/');
        for (const string& p : ps) {
            if (!node->children.count(p)) {
                node->children[p] = new Trie();
            }
            node = node->children[p];
        }
        node->isFile = isFileFlag;
        if (isFileFlag) {
            node->name = ps.back();
        }
        return node;
    }

    Trie* search(const string& path) {
        Trie* node = this;
        vector<string> ps = split(path, '/');
        for (const string& p : ps) {
            if (!node->children.count(p)) {
                return nullptr;
            }
            node = node->children[p];
        }
        return node;
    }

private:
    vector<string> split(const string& str, char delimiter) {
        vector<string> tokens;
        string token;
        istringstream ss(str);
        while (getline(ss, token, delimiter)) {
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }
};

class FileSystem {
private:
    Trie* root;

public:
    FileSystem() {
        root = new Trie();
    }

    vector<string> ls(string path) {
        vector<string> ans;
        Trie* node = root->search(path);
        if (!node) return ans;
        if (node->isFile) {
            ans.push_back(node->name);
            return ans;
        }
        for (auto& [key, _] : node->children) {
            ans.push_back(key);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }

    void mkdir(string path) {
        root->insert(path, false);
    }

    void addContentToFile(string filePath, string content) {
        Trie* node = root->insert(filePath, true);
        node->content += content;
    }

    string readContentFromFile(string filePath) {
        Trie* node = root->search(filePath);
        return node->content;
    }
};
