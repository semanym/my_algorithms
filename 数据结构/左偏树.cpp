#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000010;
//val是value，ch是children，d是dist 
//有些地方的ch会写开，lc，rc 
struct Node {
	int val, ch[2], d;
} t[N];

int& rs(int x);
int merge(int x, int y);

int find(int x);

/**
* 应用示例 
*/
int n, m, f[N];
bool killed[N];
char op[10];
int read(){}

int main() {
	int i, x, y;

	n = read();

	for (i = 1; i <= n; ++i) {
		t[i].val = read();
		f[i] = i;
	}

	m = read();

	while (m--) {
		scanf("%s", op);
		if (op[0] == 'M') {
			x = read();
			y = read();
			if (killed[x] || killed[y] || find(x) == find(y)) continue;  // 这是题意
			
			//合并操作 
			f[find(x)] = f[find(y)] = merge(find(x), find(y));
		} else {
			x = read();
			if (!killed[x]) {
				x = find(x);
				
				//删除根节点操作 
				killed[x] = true;
				f[x] = f[t[x].ch[0]] = f[t[x].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
				// 由于堆中的点会 find 到 x，所以 f[x] 也要修改
				
				printf("%d\n", t[x].val);
			} else
				puts("0");
		}
	}

	return 0;
}

int& rs(int x) {
	return t[x].ch[t[t[x].ch[1]].d < t[t[x].ch[0]].d];
}

int merge(int x, int y) {  // 左偏树并堆
	if (!x || !y) return x | y;
	if (t[x].val > t[y].val) swap(x, y);
	rs(x) = merge(rs(x), y);
	t[x].d = t[rs(x)].d + 1;
	return x;
}

int find(int x) {
	return x == f[x] ? x : f[x] = find(f[x]);    // 查找
}
