#include <bits/stdc++.h>

using namespace std;
#define int long long

//主席树二维数点
struct chairTree {
	int tot = 0, n, maxn;
	int *sum,*rt,*ls,*rs,*ind,len;

	chairTree() {}
	//都是只new一次，如果已经设置了maxn的值，在设置一遍要加入delete[] sum......
	void setMaxn(int _maxn) {
		maxn = _maxn;
		sum = new int[(maxn << 5) + 10], rt = new int[maxn + 10],
		ls = new int[(maxn << 5) + 10], rs = new int[(maxn << 5) + 10],
		ind = new int[maxn + 10];
	}

	chairTree(int _maxn):maxn(_maxn) {
		sum = new int[(maxn << 5) + 10], rt = new int[maxn + 10],
		ls = new int[(maxn << 5) + 10], rs = new int[(maxn << 5) + 10],
		ind = new int[maxn + 10];
	}

	int getid(const int &val) {  // 离散化，大于等于
		return lower_bound(ind + 1, ind + len + 1, val) - ind;
	}
	int getid_loe(const int&val) {  //小于等于
		return upper_bound(ind + 1, ind + len + 1, val) - 1 - ind;
	}

	int build(int l, int r) {  // 建树
		int root = ++tot;
		if (l == r) return root;
		int mid = (l + r) >> 1;
		ls[root] = build(l, mid);
		rs[root] = build(mid + 1, r);
		return root;  // 返回该子树的根节点
	}

	int update(int k, int l, int r, int root, int cnt) {  // 插入操作,cnt默认是1
		int dir = ++tot;
		ls[dir] = ls[root], rs[dir] = rs[root], sum[dir] = sum[root] + cnt;//这里可以改，传个参数cnt就好，代表这一点有cnt个
		if (l == r) return dir;
		int mid = (l + r) >> 1;
		if (k <= mid)
			ls[dir] = update(k, l, mid, ls[dir], cnt);
		else
			rs[dir] = update(k, mid + 1, r, rs[dir], cnt);
		return dir;
	}

	void update(int i, int j, int p, int cnt = 1) { //j是上一棵线段树,p是当前插入的离散值,i是当前的线段树
		rt[i] = update(p , 1, len, rt[j], cnt);
	}

	int query(int u, int l, int r, int ql, int qr) {  // 查询第u个线段树在ql到qr中间的数个数
		if(!u || ql > r ||qr < l) return 0;
		if(ql <= l && qr >= r) return sum[u];
		int mid = (l + r) >> 1, ans = 0;
		if(ql <= mid) ans += query(ls[u], l, mid, ql, qr);
		if(qr > mid) ans += query(rs[u], mid + 1, r, ql, qr);
		return ans;
	}
	int query(int u, int ql, int qr) {
		return query(u, 1, len, ql, qr);
	}

	void init(int* a,int _n) {
		n = _n;
		memcpy(ind, a, sizeof(int)*n);
		sort(ind + 1, ind + n + 1);
		len = unique(ind + 1, ind + n + 1) - ind - 1;
		rt[0] = build(1, len);
		for (int i = 1; i <= n; ++i) update(i, i - 1, getid(a[i]));
	}

	void init(vector<vector<int>>&a) {
		n = a.size()-1;
        for(int i=1;i<=n;++i){
            ind[i]=a[i][1];
        }
		sort(ind + 1, ind + n + 1);
		len = unique(ind + 1, ind + n + 1) - ind - 1;
		rt[0] = build(1, len);
		for (int i = 1; i <= n; ++i) update(i, i - 1, getid(a[i][1]),a[i][2]);
	}

};
/*
这是查询第k小值的版本
    int query(int u, int v, int l, int r, int k) {  // 查询操作
		int mid = l + r >> 1,
		    x = sum[ls[v]] - sum[ls[u]];  // 通过区间减法得到左儿子中所存储的数值个数
		if (l == r) return l;
		if (k <= x)  // 若 k 小于等于 x ，则说明第 k 小的数字存储在在左儿子中
			return query(ls[u], ls[v], l, mid, k);
		else  // 否则说明在右儿子中
			return query(rs[u], rs[v], mid + 1, r, k - x);
	}

	int query(int l, int r, int k) {
		return ind[query(rt[l - 1], rt[r], 1, len, k)];
	}

	void init(vector<int>&a) {
		n = a.size() - 1;
		memcpy(ind, a.data(), sizeof(int)*a.size());
		sort(ind + 1, ind + n + 1);
		len = unique(ind + 1, ind + n + 1) - ind - 1;
		rt[0] = build(1, len);
		for (int i = 1; i <= n; ++i) update(i, i - 1, getid(a[i]));
	}
	void init(vector<pair<int,int>>&a, int index) {
		n = a.size() - 1;
		if(index)for(int i=1; i<=n; ++i) ind[i]=a[i].second;
		else for(int i=1; i<=n; ++i) ind[i]=a[i].first;
		sort(ind + 1, ind + n + 1);
		len = unique(ind + 1, ind + n + 1) - ind - 1;
		rt[0] = build(1, len);
		if(index) for (int i = 1; i <= n; ++i) update(i, i - 1, getid(a[i].second));
		else for (int i = 1; i <= n; ++i) update(i, i - 1, getid(a[i].first));
	}
*/

//二维数点示例p3755洛谷
int n,m;
chairTree ct(100005);

void solve()
{
    cin>>n>>m;
    vector<vector<int>> a(n+1,vector<int>(3));
    for(int i=1;i<=n;++i){
        cin>>a[i][0]>>a[i][1]>>a[i][2];
    }
    sort(a.begin()+1,a.end());
    ct.init(a);
    while(m--){
        int x,y,c,d;
        cin>>x>>y>>c>>d;
        vector<int> sb1={x,-1LL,0LL},sb2={c,(int)1e9,(int)1e9};
        int l= lower_bound(a.begin()+1, a.end(),sb1) - a.begin() -1;
        int r= upper_bound(a.begin()+1, a.end(),sb2) - a.begin()-1;
        y=ct.getid(y),d=ct.getid_loe(d);
        int ans = ct.query(ct.rt[r],y,d)-ct.query(ct.rt[l],y,d);
        cout<<ans<<"\n";
    }

}

int32_t main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ =1;
    while (_--)
    {
        solve();
    }
    return 0;
}

