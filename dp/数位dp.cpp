#include <bits/stdc++.h>

using namespace std;
//数位dp模板

int countSpecialNumbers(int n) {
	auto s = to_string(n);
	int m = s.length(), memo[m][1 << 10];
	memset(memo, -1, sizeof(memo)); // -1 表示没有计算过
	function<int(int, int, bool, bool)> f = [&](int i, int mask, bool is_limit, bool is_num) -> int {
		if (i == m)
			return is_num; // is_num 为 true 表示得到了一个合法数字
		if (!is_limit && is_num && memo[i][mask] != -1)
			return memo[i][mask];
		int res = 0;
		if (!is_num) // 可以跳过当前数位
			res = f(i + 1, mask, false, false);
		int up = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
		for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
			if ((mask >> d & 1) == 0) // d 不在 mask 中
				res += f(i + 1, mask | (1 << d), is_limit && d == up, true);
		if (!is_limit && is_num)
			memo[i][mask] = res;
		return res;
		};
	return f(0, 0, true, false);
}

//自改
class Solution {
public:
	int f(int i, int mask, bool is_limit, bool is_num, const string& s, vector<vector<int>>& memo) {
		if (i == s.length())
			return is_num; // is_num 为 true 表示得到了一个合法数字
		if (!is_limit && is_num && memo[i][mask] != -1)
			return memo[i][mask];
		int res = 0;
		if (!is_num) // 可以跳过当前数位
			res = f(i + 1, mask, false, false, s, memo);
		int up = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
		for (int d = 1 - is_num; d <= up; ++d) // 枚举要填入的数字 d
			if ((mask >> d & 1) == 0) // d 不在 mask 中
				res += f(i + 1, mask | (1 << d), is_limit && d == up, true, s, memo);
		if (!is_limit && is_num)
			memo[i][mask] = res;
		return res;
	}

	int countSpecialNumbers(int n) {
		auto s = to_string(n);
		int m = s.length();
		vector<vector<int>> memo(m, vector<int>(1<<10, -1));// -1 表示没有计算过
		return f(0, 0, true, false, s, memo);
	}
};
