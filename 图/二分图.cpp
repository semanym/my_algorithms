//二分图 Dinic模板 O(sqrt(n)*m)
#include <bits/stdc++.h>
using namespace std;

#define N 1010
#define M 2000010

int n, m, k, S, T;
//Dinic算法板子
void add(int a, int b, int c);
int dinic(); 

//核心思想就是添加一个虚拟源点和汇点跑最大流,每条边的容量都是1
int main() {
    int a, b, c;
    scanf("%d%d%d", &n, &m, &k);
    while (k--) {
        scanf("%d%d", &a, &b);
        add(a, b+n, 1); add(b+n, a, 0);
    }
    S = 0; T = n+m+1;
    for (int i = 1; i<=n; i++)
        add(S, i, 1), add(i, S, 0);
    for (int i = 1; i<=m; i++)
        add(i+n, T, 1), add(T, i+n, 0);
    printf("%lld\n", dinic());
    return 0;
}