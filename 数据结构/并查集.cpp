#include<bits/stdc++.h>

using namespace std;

struct DSU {
	std::vector<int> fa, siz;
	
	DSU() {}
	
	DSU(int n) {
		init(n);
	}
	
	void init(int n) {
		fa.resize(n);
		std::iota(fa.begin(), fa.end(), 0);
		siz.assign(n, 1);
	}
	
	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	
	bool same(int x, int y) {
		return find(x) == find(y);
	}
	
	bool merge(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		siz[x] += siz[y];
		fa[y] = x;
		return true;
	}
	
	int size(int x) {
		return siz[find(x)];
	}
};

