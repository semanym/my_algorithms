#include <bits/stdc++.h>

using namespace std;
//��λdpģ��

int countSpecialNumbers(int n) {
	auto s = to_string(n);
	int m = s.length(), memo[m][1 << 10];
	memset(memo, -1, sizeof(memo)); // -1 ��ʾû�м����
	function<int(int, int, bool, bool)> f = [&](int i, int mask, bool is_limit, bool is_num) -> int {
		if (i == m)
			return is_num; // is_num Ϊ true ��ʾ�õ���һ���Ϸ�����
		if (!is_limit && is_num && memo[i][mask] != -1)
			return memo[i][mask];
		int res = 0;
		if (!is_num) // ����������ǰ��λ
			res = f(i + 1, mask, false, false);
		int up = is_limit ? s[i] - '0' : 9; // ���ǰ��������ֶ��� n ��һ������ô��һλ���������� s[i]������ͳ��� n ����
		for (int d = 1 - is_num; d <= up; ++d) // ö��Ҫ��������� d
			if ((mask >> d & 1) == 0) // d ���� mask ��
				res += f(i + 1, mask | (1 << d), is_limit && d == up, true);
		if (!is_limit && is_num)
			memo[i][mask] = res;
		return res;
		};
	return f(0, 0, true, false);
}

//�Ը�
class Solution {
public:
	int f(int i, int mask, bool is_limit, bool is_num, const string& s, vector<vector<int>>& memo) {
		if (i == s.length())
			return is_num; // is_num Ϊ true ��ʾ�õ���һ���Ϸ�����
		if (!is_limit && is_num && memo[i][mask] != -1)
			return memo[i][mask];
		int res = 0;
		if (!is_num) // ����������ǰ��λ
			res = f(i + 1, mask, false, false, s, memo);
		int up = is_limit ? s[i] - '0' : 9; // ���ǰ��������ֶ��� n ��һ������ô��һλ���������� s[i]������ͳ��� n ����
		for (int d = 1 - is_num; d <= up; ++d) // ö��Ҫ��������� d
			if ((mask >> d & 1) == 0) // d ���� mask ��
				res += f(i + 1, mask | (1 << d), is_limit && d == up, true, s, memo);
		if (!is_limit && is_num)
			memo[i][mask] = res;
		return res;
	}

	int countSpecialNumbers(int n) {
		auto s = to_string(n);
		int m = s.length();
		vector<vector<int>> memo(m, vector<int>(1<<10, -1));// -1 ��ʾû�м����
		return f(0, 0, true, false, s, memo);
	}
};
