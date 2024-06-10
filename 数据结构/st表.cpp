#include <bits/stdc++.h>
using namespace std;
/**
ST[i][j]��ʾ����[i,i+2^j-1]�����ֵ

���������ֵ����λ���Ҳ����
�� RMQ ���⣬���������ġ����ظ��������⡹��
���硸���䰴λ�͡��������䰴λ�򡹡������� GCD����
ST ���ܸ�Ч�ؽ����

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
		//����ֵ������������[l,r]
		T query(int l, int r) {
			int lt = r - l + 1;
			int q = floor(log2(lt));
			return op(ST[l][q], ST[r - (1 << q) + 1][q]);
		}
		
};

		/* �����init ��lg�Ļ�Ҫ�������
		T query(int l, int r) {
			if(l == r) return ST[l][0];
			int length = r - l + 1;
			int q = lg[length] - 1;
			return op(ST[l][q], ST[r - (1 << q) + 1][q]);
		}
		*/
