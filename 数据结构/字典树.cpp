#include<bits/stdc++.h>
using namespace std;
/**
* ¹þÏ£±í 
*/
typedef struct Node{    
    unordered_map<char,Node *> data;
    int cnt;

    Node() : cnt(0) {}
};

class Trie {
    Node *root;

public:
    Trie() {
        root=new Node();
    }
    
    void insert(string word) {
        Node *cur=root;

        for (auto i:word){
            if (cur->data.count(i) ==0){
                cur->data[i]=new Node();
            }
            cur=cur->data[i];
        }
        cur->cnt++;
    }
    
    bool search(string word) {
        Node *cur=root;

        for (auto i:word){
            if (cur->data.count(i) ==0){
                return false;
            }
            cur=cur->data[i];
        }

        return cur->cnt>0;
    }
    
    bool startsWith(string prefix) {
        Node *cur=root;

        for (auto i:prefix){
            if (cur->data.count(i) ==0){
                return false;
            }
            cur=cur->data[i];
        }

        return true;
    }
};

/**

*/
class Trie {
    bool isEnd;
    vector<Trie*> next;
public:
    Trie() : next(26), isEnd(false) {
    }
    
    void insert(string word) {
        auto node = this;
        for(auto& c : word){
            if (node->next[c-'a'] == nullptr) node->next[c-'a'] = new Trie();
            node = node->next[c-'a'];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        auto node = this;
        for(auto& c : word){
            if (node->next[c-'a'] == nullptr) return false;
            node = node->next[c-'a'];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        auto node = this;
        for(auto& c : prefix){
            if (node->next[c-'a'] == nullptr) return false;
            node = node->next[c-'a'];
        }
        return true;
    }
};


