#include<bits/stdc++.h>

using namespace std;

const int N = 100005;const int M = 100005;

/*
求有向图的强连通分量
强连通分量（Strongly Connected Components，SCC）
的定义是：极大的强连通子图
*/

vector<int> g[N];
//dfn[x]节点x第一次被访问的顺序 ，dfncnt时间戳
//tp top，后面三个是栈
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // 结点 i 所在 SCC 的编号
int sz[N];       // 强连通 i 的大小

void tarjan(int u) {
	//入x时，盖戳，入栈
	low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
	for (int v:g[u]) {
		if (!dfn[v]) { //若y尚未访问
			tarjan(v);
			low[u] = min(low[u], low[v]);//回x时更新low
		} else if (in_stack[v]) {//若v已访问且在栈中
			low[u] = min(low[u], dfn[v]);//更新low
		}
	}
	//离x时，记录SCC
	if (dfn[u] == low[u]) {//若x是SCC的根
		int v;
		++sc;
		do {
			v=s[tp--];
			in_stack[v]=0;
			scc[v]=sc;//SCC编号
			++sz[sc];//SCC大小
		} while(v!=u);
	}
}

/*
边 双连通分量
无向图中极大的不包含隔边的连通块被称为“边双连通分量”
(edge Double Connected Components ,eDCC)
换句话说：
在一张连通的无向图中，对于两个点 u 和 v，
如果无论删去哪条边（只能删去一条）都不能使它们不连通，我们就说 u 和 v 边双连通。
*/


//不使用链式前向星
class eDCC {

int n,m;
vector<pair<int, int>> e[N];
int dfn[N], low[N], tot;
stack<int> stk;
int dcc[N], cnt;
int bri[M];


void tarjan(int x, int in_edg) {
	dfn[x] = low[x] = ++tot;
	stk.push(x);
	for (auto it:e[x]) {
		int y = it.first,i=it.second;
		if (!dfn[y]) {
			tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y]>dfn[x]) {
				bri[i] = bri[i^1] = true;
			}
		} else if (i!=(1^in_edg)) { //不是反边
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (dfn[x]==low[x]) {
		++cnt;
		int y;
		do {
			y = stk.top();
			stk.pop();
			dcc[y] = cnt;
		} while (y!=x);
	}
}

int main() {
	cin>>n>>m;
	for(int i=1; i<=m; ++i) {
		int a,b;
		cin>>a>>b;
		e[a].emplace_back(b,i<<1);
		e[b].emplace_back(a,i<<1|1);
	}

	return 0;
}

};


struct edge {
	int v, ne;
} e[M];
//h要初始化为-1！！
int h[N], idx = 1;//2,3开始编号，给边编号
int dfn[N], low[N], tot;
stack<int> stk;
int dcc[N], cnt;
int bri[M];

//记得无向边要add两次
void add(int a, int b) {
	e[++idx].v = b;
	e[idx].ne = h[a];
	h[a] = idx;
}

void tarjan(int x, int in_edg) {
	dfn[x] = low[x] = ++tot;
	stk.push(x);
	for (int i = h[x]; ~i; i = e[i].ne) {
		int y = e[i].v;
		if (!dfn[y]) {
			tarjan(y, i);
			low[x] = min(low[x], low[y]);
			if (low[y]>dfn[x]) {
				bri[i] = bri[i^1] = true;
			}
		} else if (i!=(1^in_edg)) { //不是反边
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (dfn[x]==low[x]) {
		++cnt;
		int y;
		do {
			y = stk.top();
			stk.pop();
			dcc[y] = cnt;
		} while (y!=x);
	}
}

int main(){
	memset(h,-1,sizeof(h));
	return 0;
}


/*
若一张无向连通图不存在割点，则称它为“点双连通图”
无向图的极大点双连通子图被称为“点双连通分量”。
(vertex Double Connected Components, vDCC)

在一张连通的无向图中，对于两个点 u 和 v，
如果无论删去哪个点（只能删去一个，且不能删 u 和 v 自己）
都不能使它们不连通，我们就说 u 和 v 点双连通。

vDCC缩点
*/
class vDCC {

int n, m;
vector<int> e[N], ne[N];//new e新图，就是缩点之后的图
int dfn[N], low[N], tot;
stack<int> stk;
vector<int> dcc[N];
int cut[N], root, cnt, num, id[N];

void Tarjan(int x);

void tarjan(int x){
	root = x;
	Tarjan(x);
}

void Tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk.push(x);
    if (!e[x].size()) { //孤点
        dcc[++cnt].push_back(x);
        return;
    }
    int child = 0;
    for (int y : e[x]) {
        if (!dfn[y]) { //若y尚未访问
            Tarjan(y);
            low[x] = min(low[x], low[y]);
            if (low[y]>=dfn[x]) {
                child++;
                if (x!=root||child>1) {
                    cut[x] = true;
                }
                cnt++;
                int z;
                do { //记录vDCC
                    z = stk.top();
                    stk.pop();
                    dcc[cnt].push_back(z);
                } while (z!=y);
                dcc[cnt].push_back(x);
            }
        }
        else { //若y已经访间
            low[x] = min(low[x], dfn[y]);
        }
    }
}


int main() {
	cin>>n>>m;
	while(m--) {
		int a,b;
		cin>>a>>b;
		if(a==b)continue;
		e[a].push_back(b),e[b].push_back(a);
	}
	for(root=1; root<=n; ++root) {
		if(!dfn[root]) tarjan(root);
	}

	//给每个割点一个新编号（cnt+1开始）
	num=cnt;
	for(int i=1; i<=n; ++i) {
		if(cut[i])id[i]==++num;
	}

	//新建图，从每个vDCC向对应割点连边
	for(int i=1; i<=cnt; ++i) {
		for(int j=0; j<dcc[i].size(); ++j) {
			int x=dcc[i][j];
			if(cut[x]) {
				ne[i].push_back(id[x]);
				ne[id[x]].push_back(i);
			}
		}
	}
	return 0;
}

};
