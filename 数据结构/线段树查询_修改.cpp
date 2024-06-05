#include <bits/stdc++.h>
using namespace std;
/*
区间加用这个
void maintain(int cl, int cr, int p) {
	int cm = cl + (cr - cl) / 2;
	if (cl != cr && lazy[p]) {
		lazy[p * 2] += lazy[p];
		lazy[p * 2 + 1] += lazy[p];
		mx[p * 2] += lazy[p];
		mx[p * 2 + 1] += lazy[p];
		sum[p * 2] += lazy[p] * (cm - cl + 1);
		sum[p * 2 + 1] += lazy[p] * (cr - cm);
		lazy[p] = 0;
	}
}
*/
const int N = 200005;

int n4;
int n, root=1;
int arr[N];//下标从1开始
int lazy[N<<2], mx[N<<2]，mn[N<<2];
long long sum[N<<2];

void maintain(int cl, int cr, int p) {
	int cm = cl + (cr - cl) / 2;
	if (cl != cr && lazy[p]) {
		lazy[p * 2] = lazy[p];
		lazy[p * 2 + 1] = lazy[p];
		mx[p * 2] = lazy[p];
		mx[p * 2 + 1] = lazy[p];
		mn[p * 2] = lazy[p];
		mn[p * 2 + 1] = lazy[p];
		sum[p * 2] = lazy[p] * (cm - cl + 1);
		sum[p * 2 + 1] = lazy[p] * (cr - cm);
		lazy[p] = 0;
	}
}

long long query_sum(int l, int r, int cl, int cr, int p) {
	if (l <= cl && cr <= r) return sum[p];
	int m = cl + (cr - cl) / 2;
	long long sum = 0;
	maintain(cl, cr, p);
	if (l <= m) sum += query_sum(l, r, cl, m, p * 2);
	if (r > m) sum += query_sum(l, r, m + 1, cr, p * 2 + 1);
	return sum;
}

int query_max(int l, int r, int cl, int cr, int p) {
	if (l <= cl && cr <= r) return mx[p];
	int m = cl + (cr - cl) / 2;
	int max_num = INT_MIN;
	maintain(cl, cr, p);
	if (l <= m) max_num = max(max_num , query_max(l, r, cl, m, p * 2));
	if (r > m) max_num = max(max_num , query_max(l, r, m + 1, cr, p * 2 + 1));
	return max_num;
}
int query_min(int l, int r, int cl, int cr, int p) {
	if (l <= cl && cr <= r) return mn[p];
	int m = cl + (cr - cl) / 2;
	int min_num = INT_MAX;
	maintain(cl, cr, p);
	if (l <= m) min_num = min(min_num , query_min(l, r, cl, m, p * 2));
	if (r > m) min_num = min(min_num , query_min(l, r, m + 1, cr, p * 2 + 1));
	return min_num;
}

void range_set(int l, int r, int val, int cl, int cr, int p) {
	if (l <= cl && cr <= r) {
		lazy[p] = val;
		sum[p] = (cr - cl + 1) * val;
		mx[p] = val;
		mn[p] = val;
		return;
	}
	int m = cl + (cr - cl) / 2;
	maintain(cl, cr, p);
	if (l <= m) range_set(l, r, val, cl, m, p * 2);
	if (r > m) range_set(l, r, val, m + 1, cr, p * 2 + 1);
	sum[p] = sum[p * 2] + sum[p * 2 + 1];
	mx[p] = max(mx[p * 2] , mx[p * 2 + 1]);
	mn[p] = min(mn[p * 2] , mn[p * 2 + 1]);
}

//val是要加上的数字
void range_add(int l, int r, int val, int cl, int cr, int p) {
	if (l <= cl && cr <= r) {
		lazy[p] += val;
		sum[p] += (cr - cl + 1) * val;
		mx[p] += val;
		mn[p] += val;
		return;
	}
	int m = cl + (cr - cl) / 2;
	maintain(cl, cr, p);
	if (l <= m) range_add(l, r, val, cl, m, p * 2);
	if (r > m) range_add(l, r, val, m + 1, cr, p * 2 + 1);
	sum[p] = sum[p * 2] + sum[p * 2 + 1];
	mx[p] = max(mx[p * 2] , mx[p * 2 + 1]);
	mn[p] = min(mn[p * 2] , mn[p * 2 + 1]);
}

void build(int l = 1, int r = n , int p = 1) {
	if (l == r) {
		mn[p] = arr[l];
		mx[p] = arr[l];
		sum[p] = arr[l];
		return;
	}
	int m = l + (r - l) / 2;
	build(l, m, p * 2);
	build(m + 1, r, p * 2 + 1);
	sum[p] = sum[p * 2] + sum[p * 2 + 1];
	mx[p] = max(mx[p * 2] , mx[p * 2 + 1]);
	mn[p] = min(mn[p * 2] , mn[p * 2 + 1]);
}

void show(int p, int depth = 0) {
	if (p > n4 || sum[p] == 0) return;
	show(p * 2, depth + 1);
	for (int i = 0; i < depth; ++i) putchar('\t');
	printf("%d:%d\n", sum[p], lazy[p]);
	show(p * 2 + 1, depth + 1);
}

long long query_sum(int l, int r) {
	return query_sum(l, r, 1, n, root);
}

int query_max(int l, int r) {
	return query_max(l, r, 1, n, root);
}

int query_min(int l, int r) {
	return query_min(l, r, 1, n, root);
}

void range_set(int l, int r, int val) {
	range_set(l, r, val, 1, n, root);
}

void range_add(int l, int r, int val) {
	range_add(l,r,val,1,n,root);
}


/**
* 返回最大最小值的下标，但支持单点修改
*/
void build(int l = 1, int r = n , int p = 1) {
	if (l == r) {
		mn[p] = l;
		mx[p] = l;
		sum[p] = arr[l];
		return;
	}
	int m = l + (r - l) / 2;
	build(l, m, p * 2);
	build(m + 1, r, p * 2 + 1);
	sum[p] = sum[p * 2] + sum[p * 2 + 1];
	mx[p] = arr[mx[2 * p]] >= arr[mx[2 * p + 1]] ? mx[2 * p] : mx[2 * p + 1];
	mn[p] = arr[mn[2 * p]] <= arr[mn[2 * p + 1]] ? mn[2 * p] : mn[2 * p + 1];
}

int query_min(int l, int r, int cl, int cr, int p) {
	if (l <= cl && cr <= r)
		return mn[p];
	int m = cl + (cr - cl) / 2;
	if (r <= m)
		return query_min(l, r, cl, m, p * 2);
	if (l >= m + 1)
		return query_min(l, r, m + 1, cr, p * 2 + 1);
	int res1 = query_min(l, r, cl, m, p * 2),
	    res2 = query_min(l, r, m + 1, cr, p * 2 + 1);
	return arr[res1] <= arr[res2] ? res1 : res2;
}

int query_max(int l, int r, int cl, int cr, int p) {
	if (l <= cl && cr <= r)
		return mx[p];
	int m = cl + (cr - cl) / 2;
	if (r <= m)
		return query_max(l, r, cl, m, p * 2);
	if (l >= m + 1)
		return query_max(l, r, m + 1, cr, p * 2 + 1);
	int res1 = query_max(l, r, cl, m, p * 2),
	    res2 = query_max(l, r, m + 1, cr, p * 2 + 1);
	return arr[res1] >= arr[res2] ? res1 : res2;
}
/**
* 写不出来懒更新的区间修改 ，这是单点修改
*/
void single_set(int i, int val, int cl, int cr, int p) {
	if (cl == cr) {
		mn[p] = i;
		mx[p] = i;
		sum[p] = val;
		arr[i] = val;
		return;
	}
	int m = cl + (cr - cl) / 2;
	if (i <= m)
		range_set(i, val, cl, m, p * 2);
	if (i > m)
		range_set(i, val, m + 1, cr, p * 2 + 1);
	mn[p] = arr[mn[p * 2]] <= arr[mn[p * 2 + 1]] ? mn[p * 2] : mn[p * 2 + 1];
	mx[p] = arr[mx[p * 2]] >= arr[mx[p * 2 + 1]] ? mx[p * 2] : mx[p * 2 + 1];
	sum[p] = sum[p * 2] + sum[p * 2 + 1];
}
void single_set(int i, int val) {
	single_set(i, val, 1, n, root);
}
