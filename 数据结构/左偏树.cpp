#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1000010;
//val��value��ch��children��d��dist 
//��Щ�ط���ch��д����lc��rc 
struct Node {
	int val, ch[2], d;
} t[N];

int& rs(int x);
int merge(int x, int y);

int find(int x);

/**
* Ӧ��ʾ�� 
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
			if (killed[x] || killed[y] || find(x) == find(y)) continue;  // ��������
			
			//�ϲ����� 
			f[find(x)] = f[find(y)] = merge(find(x), find(y));
		} else {
			x = read();
			if (!killed[x]) {
				x = find(x);
				
				//ɾ�����ڵ���� 
				killed[x] = true;
				f[x] = f[t[x].ch[0]] = f[t[x].ch[1]] = merge(t[x].ch[0], t[x].ch[1]);
				// ���ڶ��еĵ�� find �� x������ f[x] ҲҪ�޸�
				
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

int merge(int x, int y) {  // ��ƫ������
	if (!x || !y) return x | y;
	if (t[x].val > t[y].val) swap(x, y);
	rs(x) = merge(rs(x), y);
	t[x].d = t[rs(x)].d + 1;
	return x;
}

int find(int x) {
	return x == f[x] ? x : f[x] = find(f[x]);    // ����
}
