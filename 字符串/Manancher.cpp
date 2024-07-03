#include <bits/stdc++.h>
using namespace std;

const int maxn = 500006;
//有的时候开大了，放在main函数里面可能爆内存
//只有小写字母
struct Manacher {
	char cstring[maxn];
	int p[maxn];
	// vector<char> cstring;
	// vector<int> p;
	int cnt = 0, ans = 0;

	Manacher() :cnt(0), ans(0) {}
	// Manacher(int n) :cstring(n*2+5), p(n*2+5), cnt(0), ans(0) {}

	void readS() {
		char c = getchar();
		cstring[0] = '~', cstring[cnt = 1] = '|';
		while (c<'a'||c>'z') c = getchar();
		while (c>='a'&&c<='z') cstring[++cnt] = c, cstring[++cnt] = '|', c = getchar();
	}

	void exchange(string& s) {
		cstring[0] = '~'; cstring[cnt = 1] = '|';
		for (auto c:s) {
			cstring[++cnt] = c;
			cstring[++cnt] = '|';
		}
	}

	int op() {
		ans = 0;
		for (int t = 1, r = 0, mid = 0; t<=cnt; ++t) {
			p[t] = 0;
			if (t<=r) p[t] = min(p[(mid<<1)-t], r-t+1);
			while (t+p[t]<=cnt && cstring[t-p[t]]==cstring[t+p[t]]) ++p[t];
			//暴力拓展左右两侧,当t-p[t]==0时，由于cstring[0]是'~'，自动停止。故不会下标溢出。
			//假若我这里成功暴力扩展了，就意味着到时候r会单调递增，所以manacher是线性的。
			if (p[t]+t>r) r = p[t]+t-1, mid = t;
			//更新mid和r,保持r是最右的才能保证我们提前确定的部分回文半径尽量多。
			if (p[t]>ans) ans = p[t];
		}
		return ans-1;
	}
};

Manacher m;

int main() {
	m.readS();
	cout<<m.op()<<"\n";

	//看细节
	for (int i = 0; i<=m.cnt; ++i) {
		cout<<m.cstring[i]<<" ";
	}
	for (int i = 0; i<=m.cnt; ++i) {
		cout<<m.p[i]<<" ";
	}
	return 0;
}
