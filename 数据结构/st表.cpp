#include <bits/stdc++.h>
using namespace std;
/**
ST[i][j]表示区间[i,i+2^j-1]的最大值

求区间最大值，按位与或也可以
除 RMQ 以外，还有其它的「可重复贡献问题」。
例如「区间按位和」、「区间按位或」、「区间 GCD」，
ST 表都能高效地解决。

*/
int lg[200005];
void init(int n) {
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[(i + 1) / 2] + 1;
    }
    return;
}


template <typename T>
class SparseTable {
		using VT = vector<T>;
		using VVT = vector<VT>;
		using func_type = function<T(const T &, const T &)>;

		VVT ST;

		static T default_func(const T &t1, const T &t2) {
			return max(t1, t2);
		}

		func_type op;

	public:
		SparseTable(const vector<T> &v, func_type _func = default_func) {
			op = _func;
			int len = v.size(), l1 = ceil(log2(len)) + 1;//l1 = lg[len] + 1;
			ST.assign(len, VT(l1, 0));
			for (int i = 0; i < len; ++i) {
				ST[i][0] = v[i];
			}
			for (int j = 1; j < l1; ++j) {
				int pj = (1 << (j - 1));
				for (int i = 0; i + pj < len; ++i) {
					ST[i][j] = op(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]);
				}
			}
		}
		//返回值，并且区间是[l,r]
		T query(int l, int r) {
			int lt = r - l + 1;
			int q = floor(log2(lt));
			return op(ST[l][q], ST[r - (1 << q) + 1][q]);
		}
		
};

		/* 如果用init 的lg的话要换成这个
		T query(int l, int r) {
			if(l == r) return ST[l][0];
			int length = r - l + 1;
			int q = lg[length] - 1;
			return op(ST[l][q], ST[r - (1 << q) + 1][q]);
		}
		*/
