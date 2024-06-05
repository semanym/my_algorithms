/**
����l r t,�����l<=i<=r a[i]=min(a[i],t)
���[l,r]���ֵ
����[l,r]��
*/
#include<bits/stdc++.h>
#include<iostream>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;
const int N = 1e6 + 6;

/*
mx[u]: ��ʾ�Խڵ� u Ϊ���������е����ֵ��
se[u]: ��ʾ�Խڵ� u Ϊ���������еĴδ�ֵ��
cn[u]: ��ʾ�Խڵ� u Ϊ�������������ֵ���ֵĴ�����
tag[u]: ��ʾ�ڵ� u �������ǣ������ӳٸ��²�����

ע�⣺a�����С���1��ʼ�����ҵ��±�Ҳ�Ǵ�1��ʼ
*/

int n;
int a[N];
int mx[N << 2], tag[N << 2], cn[N << 2];
//int se[N << 2];
long long sum[N << 2];

void pushup(int u) {  // ���ϸ��±��
	const int ls = u << 1, rs = u << 1 | 1;
	sum[u] = sum[ls] + sum[rs];
	if (mx[ls] == mx[rs]) {
		mx[u] = mx[rs];
		//se[u] = max(se[ls], se[rs]);
		cn[u] = cn[ls] + cn[rs];
	} else if (mx[ls] > mx[rs]) {
		mx[u] = mx[ls];
		//se[u] = max(se[ls], mx[rs]);
		cn[u] = cn[ls];
	} else {
		mx[u] = mx[rs];
		//se[u] = max(mx[ls], se[rs]);
		cn[u] = cn[rs];
	}
}

void pushtag(int u, int tg) {  // �����ش��ǣ�������
	if (mx[u] <= tg) return;
	sum[u] += (1ll * tg - mx[u]) * cn[u];
	mx[u] = tag[u] = tg;
}

void pushdown(int u) {  // �´����
	if (tag[u] == -1) return;
	pushtag(u << 1, tag[u]), pushtag(u << 1 | 1, tag[u]);
	tag[u] = -1;
}

void build(int u = 1, int l = 1, int r = n) {  // ����
	tag[u] = -1;
	if (l == r) {
		sum[u] = mx[u] = a[l], cn[u] = 1;
		//se[u] = -1
		return;
	}
	int mid = (l + r) >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
	pushup(u);
}

int query_max(int L, int R, int u = 1, int l = 1, int r = n) {  // ��ѯ��ֵ
	if (L <= l && r <= R) return mx[u];
	int mid = (l + r) >> 1, r1 = -1, r2 = -1;
	pushdown(u);
	if (L <= mid) r1 = query_max(L, R, u << 1, l, mid);
	if (mid < R) r2 = query_max(L, R, u << 1 | 1, mid + 1, r);
	return max(r1, r2);
}

long long query_sum(int L, int R, int u = 1, int l = 1, int r = n) {  // ��ֵ
	if (L <= l && r <= R) return sum[u];
	int mid = (l + r) >> 1;
	long long res = 0;
	pushdown(u);
	if (L <= mid) res += query_sum(L, R, u << 1, l, mid);
	if (mid < R) res += query_sum(L, R, u << 1 | 1, mid + 1, r);
	return res;
}

/*
void modify_min(int L, int R, int v, int u = 1, int l = 1, int r = n) {
  if (mx[u] <= v) return;
  if (L <= l && r <= R && se[u] < v) return pushtag(u, v);
  int mid = (l + r) >> 1;
  pushdown(u);
  if (L <= mid) modify_min(L, R, v, u << 1, l, mid);
  if (mid < R) modify_min(L, R, v, u << 1 | 1, mid + 1, r);
  pushup(u);
}
*/
/*
void go() {  // ��������
  int m;cin>>n>>m;
  for (int i = 1; i <= n; i++) cin>>a[i];
  build();
  for (int i = 1; i <= m; i++) {
    int op, x, y, z;
    cin>>op>>x>>y;
    if (op == 0){
    	cin>>z;modify_min(x, y, z);
	}
    else if (op == 1)
      printf("%d\n", query_max(x, y));
    else
      printf("%lld\n", query_sum(x, y));
  }
}

signed main() {
  int t;cin>>t;
  while (t--) go();
  return 0;
}
*/
int main() {
	return 0;
}
