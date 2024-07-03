#include<bits/stdc++.h>

using namespace std;

const int N = 100005; const int M = 100005;

/*
������ͼ��ǿ��ͨ����
ǿ��ͨ������Strongly Connected Components��SCC��
�Ķ����ǣ������ǿ��ͨ��ͼ
*/

vector<int> g[N];
//dfn[x]�ڵ�x��һ�α����ʵ�˳�� ��dfncntʱ���
//tp top������������ջ
int dfn[N], low[N], dfncnt, s[N], in_stack[N], tp;
int scc[N], sc;  // ��� i ���� SCC �ı��
int sz[N];       // ǿ��ͨ i �Ĵ�С

void tarjan(int u) {
	//��xʱ���Ǵ�����ջ
	low[u] = dfn[u] = ++dfncnt, s[++tp] = u, in_stack[u] = 1;
	for (int v : g[u]) {
		if (!dfn[v]) { //��y��δ����
			tarjan(v);
			low[u] = min(low[u], low[v]);//��xʱ����low
		}
		else if (in_stack[v]) {//��v�ѷ�������ջ��
			low[u] = min(low[u], dfn[v]);//����low
		}
	}
	//��xʱ����¼SCC
	if (dfn[u] == low[u]) {//��x��SCC�ĸ�
		int v;
		++sc;
		do {
			v = s[tp--];
			in_stack[v] = 0;
			scc[v] = sc;//SCC���
			++sz[sc];//SCC��С
		} while (v!=u);
	}
}

/*
�� ˫��ͨ����
����ͼ�м���Ĳ��������ߵ���ͨ�鱻��Ϊ����˫��ͨ������
(edge Double Connected Components ,eDCC)
���仰˵��
��һ����ͨ������ͼ�У����������� u �� v��
�������ɾȥ�����ߣ�ֻ��ɾȥһ����������ʹ���ǲ���ͨ�����Ǿ�˵ u �� v ��˫��ͨ��
*/

//��ʹ����ʽǰ����
struct eDCC {
	int n, m, i = 1; //n�ǵ�ĸ��������Ǵ�1��ʼ�ġ�
	vector<vector<pair<int, int>>> e;
	vector<int> dfn, low, dcc;
	int tot = 0, cnt = 0;
	stack<int> stk;
	vector<int> bri;//����Ҫ���ã��ǵ�tarjan��ע��ȡ����

	eDCC(int n) :n(n), e(n+5), dfn(n+5, 0), low(n+5), dcc(n+5, 0) {}
	eDCC(int n, int m) :n(n), m(m), e(n+5), dfn(n+5, 0), low(n+5), dcc(n+5, 0), bri(m+5, 0) {}
	void addEdge(int a, int b) { e[a].emplace_back(b, i<<1); e[b].emplace_back(a, i<<1|1); ++i; }
	void build() { for (int i = 1; i<=n; ++i) { if (!dfn[i]) { tarjan(i, 0); } } }

	void tarjan(int x, int in_edg) {
		dfn[x] = low[x] = ++tot;
		stk.push(x);
		for (auto it:e[x]) {
			int y = it.first, i = it.second;
			if (!dfn[y]) {
				tarjan(y, i);
				low[x] = min(low[x], low[y]);
				//if (low[y]>dfn[x]) bri[i] = bri[i^1] = true;
			}
			else if (i!=(1^in_edg)) { //���Ƿ���
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
};


struct edge {
	int v, ne;
} e[M];
//hҪ��ʼ��Ϊ-1����
int h[N], idx = 1;//2,3��ʼ��ţ����߱��
int dfn[N], low[N], tot;
stack<int> stk;
int dcc[N], cnt;
int bri[M];

//�ǵ������Ҫadd����
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
		}
		else if (i!=(1^in_edg)) { //���Ƿ���
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
	memset(h, -1, sizeof(h));
	return 0;
}


/*
��һ��������ͨͼ�����ڸ�㣬�����Ϊ����˫��ͨͼ��
����ͼ�ļ����˫��ͨ��ͼ����Ϊ����˫��ͨ��������
(vertex Double Connected Components, vDCC)

��һ����ͨ������ͼ�У����������� u �� v��
�������ɾȥ�ĸ��㣨ֻ��ɾȥһ�����Ҳ���ɾ u �� v �Լ���
������ʹ���ǲ���ͨ�����Ǿ�˵ u �� v ��˫��ͨ��

vDCC����
*/
struct vDCC {
	int n, tot = 0, root, cnt = 0, num;//n��1��ʼ
	vector<vector<int>> dcc, e, ne;//new e��ͼ����������֮���ͼ
	vector<int> dfn, low, id;
	stack<int> stk;
	vector<bool> cut;

	vDCC() {}
	vDCC(int n) :n(n), tot(0), cnt(0), e(n+5), ne(n+5), dfn(n+5, 0), low(n+5), dcc(n+5), id(n+5), cut(n+5) {}
	void addEdge(int a, int b) { e[a].push_back(b); e[b].push_back(a); }
	void build() {
		for (root = 1; root<=n; ++root) {
			if (!dfn[root]) Tarjan(root);
		}
	}

	void tarjan(int x) {
		root = x;
		Tarjan(x);
	}

	void Tarjan(int x) {
		dfn[x] = low[x] = ++tot;
		stk.push(x);
		if (!e[x].size()) { //�µ�
			dcc[++cnt].push_back(x);
			return;
		}
		int child = 0;
		for (int y : e[x]) {
			if (!dfn[y]) { //��y��δ����
				Tarjan(y);
				low[x] = min(low[x], low[y]);
				if (low[y]>=dfn[x]) {
					child++;
					if (x!=root||child>1) {
						cut[x] = true;
					}
					cnt++;
					int z;
					do { //��¼vDCC
						z = stk.top();
						stk.pop();
						dcc[cnt].push_back(z);
					} while (z!=y);
					dcc[cnt].push_back(x);
				}
			}
			else { //��y�Ѿ��ü�
				low[x] = min(low[x], dfn[y]);
			}
		}
	}

	//û����
	void buildNe() {
		//��ÿ�����һ���±�ţ�cnt+1��ʼ��
		num = cnt;
		for (int i = 1; i<=n; ++i) {
			if (cut[i])id[i]==++num;
		}
		//�½�ͼ����ÿ��vDCC���Ӧ�������
		for (int i = 1; i<=cnt; ++i) {
			for (int j = 0; j<dcc[i].size(); ++j) {
				int x = dcc[i][j];
				if (cut[x]) {
					ne[i].push_back(id[x]);
					ne[id[x]].push_back(i);
				}
			}
		}
	}
};

int n, m;

int main() {
	vDCC vdcc(n);
	cin>>n>>m;
	while (m--) {
		int a, b;
		cin>>a>>b;
		if (a==b)continue;
		vdcc.addEdge(a, b);
	}
	vdcc.build();
	cout<<vdcc.cnt<<"\n";

	for (int i = 1; i<=vdcc.cnt; ++i) {
		cout<<vdcc.dcc[i].size()<<" ";
		for (auto n:vdcc.dcc[i])cout<<n<<" ";
		cout<<"\n";
	}

	vdcc.buildNe();
	return 0;
}
