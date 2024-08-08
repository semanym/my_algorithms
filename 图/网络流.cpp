
#include <bits/stdc++.h>
using namespace std;

// Luogu P3376 [模板]网络最大流
/*
* EK算法,类似挤牙膏,O(n m^2),实际远远达不到
*/
namespace ek {

#define N 10010
#define M 200010
    int n, m, S, T;//S是源点,T是汇点
    struct edge { long long j, val, ne; }e[M];//链式前向星,h[u]存u的最后（第）一条出边,h必须初始化
    int h[N], idx = 1;
    long long mf[N], pre[N];//mf存流量上限,pre存v的前驱路

    void add(int a, int b, int val) {
        e[++idx] = { b,val,h[a] };
        h[a] = idx;
    }

    bool bfs() {
        memset(mf, 0, sizeof mf);
        queue<int> q;
        q.push(S); mf[S] = 1e9;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = h[u]; i; i = e[i].ne) {
                long long j = e[i].j;
                if (mf[j]==0 && e[i].val) {
                    mf[j] = min(mf[u], e[i].val);
                    pre[j] = i;
                    q.push(j);
                    if (j==T)return true;
                }
            }
        }
        return false;
    }
    long long EK() {
        long long flow = 0;
        while (bfs()) {//找增广路,就是一直找新路,然后更新图
            int j = T;
            while (j!=S) {//更新残留网
                int i = pre[j];
                e[i].val -= mf[T];
                e[i^1].val += mf[T];
                j = e[i^1].j;
            }
            flow += mf[T];
        }
        return flow;
    }
    int main() {
        int a, b, c;
        scanf("%d%d%d%d", &n, &m, &S, &T);
        while (m--) {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
            add(b, a, 0);//反向边
        }
        printf("%lld\n", EK());
        return 0;
    }
}

/*
Dinic算法 O(n^2m)
*/
namespace Dinic {

#define N 10010
#define M 200010

    int n, m, S, T;
    struct edge { long long j, val, ne; }e[M];
    int h[N], idx = 1; //从2,3开始配对
    int d[N], cur[N];//d存u点所在的图层;cur存u点的当前出边,方便下一次dfs进行多路增广

    void add(int a, int b, int c) {
        e[++idx] = { b,c,h[a] };
        h[a] = idx;
    }
    bool bfs() { //对点分层，找增广路
        memset(d, 0, sizeof d);
        queue<int>q;
        q.push(S); d[S] = 1;
        while (q.size()) {
            int u = q.front(); q.pop();
            for (int i = h[u]; i; i = e[i].ne) {
                int v = e[i].j;
                if (d[v]==0 && e[i].val) {
                    d[v] = d[u]+1;
                    q.push(v);
                    if (v==T)return true;
                }
            }
        }
        return false;
    }
    long long dfs(int u, long long mf) { //多路增广
        if (u==T) return mf;
        long long sum = 0;
        for (int i = cur[u]; i; i = e[i].ne) {
            cur[u] = i; //当前弧优化
            int v = e[i].j;
            if (d[v]==d[u]+1 && e[i].val) {
                long long f = dfs(v, min(mf, e[i].val));
                e[i].val -= f;
                e[i^1].val += f; //更新残留网
                sum += f; //累加u的流出流量
                mf -= f;  //减少u的剩余流量
                if (mf==0)break;//余量优化
            }
        }
        if (sum==0) d[u] = 0; //残枝优化,走不到汇点
        return sum;
    }
    long long dinic() { //累加可行流
        long long flow = 0;
        while (bfs()) {
            memcpy(cur, h, sizeof h);
            flow += dfs(S, LLONG_MAX);//如果答案最大可能值大于1e9就要小心
        }
        return flow;
    }
    int main() {
        int a, b, c;
        scanf("%d%d%d%d", &n, &m, &S, &T);
        while (m--) {
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c); add(b, a, 0);
        }
        printf("%lld\n", dinic());
        return 0;
    }
}

//Luogu P1344 [模板]最小割
/*
最小割等于最大流
1.求最小割
2.求最小割的划分
3.求最小割的最少边数
*/
namespace mincut {
    #define N 10010
    #define M 200010

    int n, m, S, T;
    int a[N], b[N], vis[N], c;

    //这里是Dinic算法板子

    void mincut(int u) {
        vis[u] = 1;
        for (int i = Dinic::h[u]; i; i = Dinic::e[i].ne) {
            int v = Dinic::e[i].j;
            if (!vis[v] && Dinic::e[i].val)mincut(v);
        }
    }

    int main() {
        scanf("%d%d", &n, &m);
        S = 1, T = n;
        for (int i = 1; i<=m; i++) {
            scanf("%d%d%d", &a[i], &b[i], &c);
            Dinic::add(a[i], b[i], c);
            Dinic::add(b[i], a[i], 0);
        }
        printf("%d ", Dinic::dinic());

        //最小割的划分
        mincut(S);//在残留网里面找，把残留的当作一个点集，剩下的一个点集
        for (int i = 1; i<=n; ++i) {
            if (vis[i])printf("%d", i);
        }
        puts(" ");
        for (int i = 1; i<=n; ++i) {
            if (!vis[i])printf("%d", i);
        }
        puts(" ");

        //最小割的最少边数,把所有边当作流量为1的变，最小割就是最大流
        Dinic::idx = 1;
        memset(Dinic::h, 0, sizeof Dinic::h);
        for (int i = 1; i<=m; i++) {
            Dinic::add(a[i], b[i], 1);
            Dinic::add(b[i], a[i], 0);
        }
        printf("%d\n", Dinic::dinic());
        return 0;
    }
}