// Code by rickyxrc | https://www.luogu.com.cn/record/115706921
#include <bits/stdc++.h>
using namespace std;

#define maxn 2000005

char s[maxn];
int n, cnt, vis[maxn], rev[maxn], ind[maxn], ans;
//ind是入度，失配指针优化要用，vis的统计每个模式串在文本串中出现的次数！！
//rev就跟并查集一样，所以一样的字符串共用一个flag值

struct trie_node {
    int son[27];
    int fail;//失配指针
    int flag;//结束标志，多少个
    int ans;//失配指针复杂度优化

    void init() {
        memset(son, 0, sizeof(son));
        fail = flag= ans = 0;
    }
} trie[maxn];//不使用指针，用数组模拟链式结构,根节点是1

queue<int> q;

void init() {
    for (int i = 0; i <= cnt; i++) trie[i].init();
    for (int i = 1; i <= n; i++) vis[i] = 0;
    cnt = 1;
    ans = 0;
}

void insert(char* s) {
    int u = 1, len = strlen(s);
    for (int i = 0; i < len; i++) {
        int v = s[i] - 'a';
        if (!trie[u].son[v]) trie[u].son[v] = ++cnt;
        u = trie[u].son[v];
    }
    trie[u].flag++;
    return;
}


void insert(char* s, int num) {
    int u = 1, len = strlen(s);
    for (int i = 0; i < len; i++) {
        int v = s[i] - 'a';
        if (!trie[u].son[v]) trie[u].son[v] = ++cnt;
        u = trie[u].son[v];
    }
    //相当于所以相同的字符串都指向同一个flag值
    if (!trie[u].flag) trie[u].flag = num;
    rev[num] = trie[u].flag;
    return;
}

void getfail(void) {
    for (int i = 0; i < 26; i++) trie[0].son[i] = 1;
    q.push(1);
    trie[1].fail = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int Fail = trie[u].fail;
        for (int i = 0; i < 26; i++) {
            int v = trie[u].son[i];
            if (v) {
                trie[v].fail = trie[Fail].son[i];
                ind[trie[Fail].son[i]]++;
                q.push(v);
            }
            else {
                trie[u].son[i] = trie[Fail].son[i];
            }
        }
    }
}

void tuopu() {
    for (int i = 1; i <= cnt; i++)
        if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int fr = q.front();
        q.pop();
        vis[trie[fr].flag] = trie[fr].ans;
        int u = trie[fr].fail;
        trie[u].ans += trie[fr].ans;
        if (!(--ind[u])) q.push(u);
    }
}

void query(char* s) {
    int u = 1, len = strlen(s);
    for (int i = 0; i < len; i++) u = trie[u].son[s[i] - 'a'], trie[u].ans++;
}

int main() {
    cin>>n;
    init();
    for (int i = 1; i <= n; i++) scanf("%s", s), insert(s, i);
    getfail();
    scanf("%s", s);
    query(s);
    tuopu();
    for (int i = 1; i <= n; i++) cout << vis[rev[i]] << "\n";
    return 0;
}

/*************************************

以上是求每个模式串出现的次数，并且不保证模式串不相同

以下是求有多少个模式串出现了，并且没有对失配指针优化
*/
namespace AC {

    const int N = 500010;
    int n; char str[1000010];
    int ch[N][26], cnt[N], idx;
    int fail[N];
    //ch是son，fail是fail,cnt是结束标志，有多少个

    void insert(char* s) {//建树
        int p = 0;
        for (int i = 0; s[i]; i++) {
            int j = s[i]-'a';
            if (!ch[p][j])ch[p][j] = ++idx;
            p = ch[p][j];
        }
        cnt[p]++;
    }
    void getfail() {//建AC自动机
        queue<int> q;
        for (int i = 0; i<26; i++)
            if (ch[0][i])q.push(ch[0][i]);
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = 0; i<26; i++) {
                int v = ch[u][i];
                if (v)fail[v] = ch[fail[u]][i], q.push(v);
                else ch[u][i] = ch[fail[u]][i];
            }
        }
    }

    int query(char* s) {
        int ans = 0;
        for (int k = 0, i = 0; s[k]; k++) {
            i = ch[i][s[k]-'a'];
            for (int j = i; j&&~cnt[j]; j = fail[j])
                ans += cnt[j], cnt[j] = -1;//避免重复统计
        }
        return ans;
    }

    int main() {
        cin>>n;
        for (int i = 0; i<n; i++)
            cin>>str, insert(str);
        getfail();
        cin>>str;
        cout<<query(str)<<endl;
        return 0;
    }

}

struct Node {
    Node* son[26]{};
    Node* fail; // 当 cur.son[i] 不能匹配 target 中的某个字符时，cur.fail.son[i] 即为下一个待匹配节点（等于 root 则表示没有匹配）
    Node* last; // 后缀链接（suffix link），用来快速跳到一定是某个 words[k] 的最后一个字母的节点（等于 root 则表示没有）
    int len = 0;
};

struct AhoCorasick {
    Node* root = new Node();

    void put(string& s) {
        auto cur = root;
        for (char b : s) {
            b -= 'a';
            if (cur->son[b] == nullptr) {
                cur->son[b] = new Node();
            }
            cur = cur->son[b];
        }
        cur->len = s.length();
    }

    void build_fail() {
        root->fail = root->last = root;
        queue<Node*> q;
        for (auto& son : root->son) {
            if (son == nullptr) {
                son = root;
            }
            else {
                son->fail = son->last = root; // 第一层的失配指针，都指向根节点 ∅
                q.push(son);
            }
        }
        // BFS
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                auto& son = cur->son[i];
                if (son == nullptr) {
                    // 虚拟子节点 cur.son[i]，和 cur.fail.son[i] 是同一个
                    // 方便失配时直接跳到下一个可能匹配的位置（但不一定是某个 words[k] 的最后一个字母）
                    son = cur->fail->son[i];
                    continue;
                }
                son->fail = cur->fail->son[i]; // 计算失配位置
                // 沿着 last 往上走，可以直接跳到一定是某个 words[k] 的最后一个字母的节点（如果跳到 root 表示没有匹配）
                son->last = son->fail->len ? son->fail : son->fail->last;
                q.push(son);
            }
        }
    }

    void query(const string& s) {
        auto cur = root;
        for (int i = 0; i < s.size(); i++) {
            cur = cur->son[s[i] - 'a']; // 如果没有匹配相当于移动到 fail 的 son[target[i-1]-'a']
            if (cur->len) { // 匹配到了一个尽可能长的 words[k]
                //f[i] = min(f[i], f[i - cur->len] + cur->cost);
            }
            // 还可能匹配其余更短的 words[k]，要在 last 链上找
            for (auto match = cur->last; match != root; match = match->last) {
                //f[i] = min(f[i], f[i - match->len] + match->cost);
            }
        }
        //return f[n] == INT_MAX / 2 ? -1 : f[n];
    }
};
