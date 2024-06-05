#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

/*
sa[i]表示将所有后缀排序后第[i]小的后缀的编号，也是所说的后缀数组。 
rk[i]表示从[i]开始的后缀的排名，是重要的辅助数组，后文也称排名数组 [rk] 。
*/
const int N = 1000005;

char s[N];
int n;
int m, p, rk[N * 2], oldrk[N], sa[N * 2], id[N], cnt[N];
int height[N]; //根据需求来 

void SA(){
	for (int i = 1; i <= n; ++i) cnt[rk[i] = s[i]]++;
	for (int i = 2; i <= m; ++i) cnt[i] += cnt[i - 1];
	for (int i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;

	for (int w = 1;; w <<= 1, m = p) {  // m = p 即为值域优化
		int cur = 0;
		for (int i = n - w + 1; i <= n; ++i) id[++cur] = i;
		for (int i = 1; i <= n; ++i)
			if (sa[i] > w) id[++cur] = sa[i] - w;

		for (int i = 1; i <= m; ++i) cnt[i]=0;
		for (int i = 1; i <= n; i++) cnt[rk[i]]++;
		for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
		for (int i = n; i >= 1; i--) sa[cnt[rk[id[i]]]--] = id[i];

		p = 0;
		memcpy(oldrk, rk, sizeof(int)*(n+3));
		for (int i = 1; i <= n; i++) {
			if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
			        oldrk[sa[i] + w] == oldrk[sa[i - 1] + w])
				rk[sa[i]] = p;
			else
				rk[sa[i]] = ++p;
		}

		if (p == n) break;  // p = n 时无需再排序
	}
}

/**
* lcp(最长公共前缀)
* height数组的定义：
	height[i]=lcp(sa[i],sa[i-1]),第i名的后缀与它前一名
	的后缀的最长公共前缀
	height[1]可以视作0
*  O(n) 求 height 数组的代码实现
*/
void Height(){
	for (int i = 1, k = 0; i <= n; ++i) {
		if (rk[i] == 0) continue;
		if (k) --k;
		while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
		height[rk[i]] = k;
	}
}
/**
* lcp(sa[i],sa[j]) = min{height[i+1...j]}
*/

int main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	m = 128;

	SA();
	Height();
	
	for (int i = 1; i <= n; i++) printf("%d ", sa[i]);//从1开始的 
	cout<<"\n";
	for (int i = 1; i <= n; i++) printf("%d ", height[i]);

	return 0;
}




