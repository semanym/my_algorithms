#include <bits/stdc++.h>
using namespace std;


using i64 = long long;
std::vector<i64> M = { 1610612741, 0, 805306457, 402653189, 201326611, 100663319, 50331653, 1000000007, 1000000009 };

struct HASH {
	i64 h1 = 0, h2 = 0;

	HASH operator-(const HASH& x) const { return { h1 - x.h1, h2 - x.h2 }; }

	HASH operator+(const HASH& x) const { return { h1 + x.h1, h2 + x.h2 }; }

	HASH operator+(const std::pair<int, int>& x) const { return { h1 + x.first, h2 + x.second }; }

	HASH operator%(const std::pair<int, int>& x) const { return { h1 % x.first, h2 % x.second }; }

	bool operator==(const HASH& x) const { return h1 == x.h1 && h2 == x.h2; }

	bool operator<(const HASH& x) const { return h1 < x.h1 || (h1 == x.h1 && h2 < x.h2); }

	bool operator>(const HASH& x) const { return h1 > x.h1 || (h1 == x.h1 && h2 > x.h2); }

	friend std::ostream& operator<<(std::ostream& os, const HASH& hash) {
		os << "(" << hash.h1 << ", " << hash.h2 << ")";
		return os;
	}
};

template<class T>
struct Hash {
	using HASH = int;
	int n{};
	std::vector<i64> P1, P2;
	std::vector<HASH> H;
	i64 p1 = 131, p2 = 13331;

	Hash() {};

	Hash(std::string& s) { Init(s); }

	Hash(std::vector<T>& s) { Init(s); }

	void change() {
		std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
		while (M[1] == 0 || M[2] == 0) shuffle(M.begin(), M.end(), rng);
	}

	void deal(int st, int len, std::vector<T>& s) {
		P1.resize(len + 1);
		P2.resize(len + 1);
		H.resize(len + 1);
		P1[0] = 1;
		P2[0] = 1;
		for (int i = st; i <= len; i++) {
			P1[i] = (P1[i - 1] * p1) % M[1];
			P2[i] = (P2[i - 1] * p2) % M[2];
			H[i].h1 = (H[i - 1].h1 * p1 + s[i - st + 1]) % M[1];
			H[i].h2 = (H[i - 1].h2 * p2 + s[i - st + 1]) % M[2];
		}
	}

	void Init(std::string& s) {
		std::vector<char> str(1, ' ');
		for (char& c: s)str.push_back(c);
		Init(str);
	}

	void Init(std::vector<T>& s) {
		if (M[1] == 0) change();
		n = s.size() - 1;
		deal(1, n, s);
	}

	HASH get(int l, int r) {
		HASH res;
		res.h1 = ((H[r].h1 - H[l - 1].h1 * P1[r - l + 1]) % M[1] + M[1]) % M[1];
		res.h2 = ((H[r].h2 - H[l - 1].h2 * P2[r - l + 1]) % M[2] + M[2]) % M[2];
		return res;
	}

	HASH mul(int l1, int r1, int l2, int r2) {
		HASH it1 = get(l1, r1), it2 = get(l2, r2), it3;
		it1.h1 *= P1[r2 - l2 + 1] %= M[1];
		it1.h2 *= P2[r2 - l2 + 1] %= M[2];
		it3 = (it1 + it2) % getMod();
		return it3;
	}

	HASH mul(HASH l, HASH r, int len) {
		HASH res;
		l.h1 *= P1[len] %= M[1];
		l.h2 *= P2[len] %= M[2];
		res = (l + r) % getMod();
		return res;
	}

	void push_back(std::string s) { push_back(std::vector<char>(s.begin(), s.end())); }

	void push_back(std::vector<T> s) { deal(n + 1, s.size() + n, s), n += s.size(); }

	std::pair<i64, i64> getMod() { return std::make_pair(M[1], M[2]); }
};

int main() {
	string s = "abcdefg";
	Hash<char> sh(s);
	std::cout<<sh.get(4, 7)<<" ";//defg

	string s2 = "defg";
	Hash<char> sh2(s2);
	cout<<sh2.get(1, 4)<<"\n";//defg

	cout<<sh.get(1, 7)<<" ";//abcdefg
	cout<<sh.mul(sh.get(1, 3), sh2.get(1, 4), 4)<<" ";//abcdefg
	cout<<sh.mul(1, 3, 4, 7)<<"\n";//abcdefg

	cout<<" "<<(sh.get(4, 7)==sh2.get(1, 4))<<" ";
	cout<<(char)97;
	return 0;
}


const int L = 1e6 + 5;
const int HASH_CNT = 2;

int hashBase[HASH_CNT] = { 29, 31 };
int hashMod[HASH_CNT] = { 1000000009,998244353 };
//1000000009,998244353,402653189,201326611,100663319,50331653,1000000007

struct StringWithHash {
	char s[L];//从1开始的
	int ls;
	int hsh[HASH_CNT][L];
	int pwMod[HASH_CNT][L];

	void init() {  // 初始化
		ls = 0;
		for (int i = 0; i < HASH_CNT; ++i) {
			hsh[i][0] = 0;
			pwMod[i][0] = 1;
		}
	}

	StringWithHash() {
		init();
	}

	void extend(char c) {
		s[++ls] = c;                          // 记录字符数和每一个字符
		for (int i = 0; i < HASH_CNT; ++i) {  // 双哈希的预处理
			pwMod[i][ls] =
				1ll * pwMod[i][ls - 1] * hashBase[i] % hashMod[i];  // 得到b^ls
			hsh[i][ls] = (1ll * hsh[i][ls - 1] * hashBase[i] + c) % hashMod[i];
		}
	}

	vector<int> getHash(int l, int r) {  // 得到哈希值，注意！！下标从0开始，因为自行添加了++
		l++, r++;
		vector<int> res(HASH_CNT, 0);
		for (int i = 0; i < HASH_CNT; ++i) {
			int t =
				(hsh[i][r] - 1ll * hsh[i][l - 1] * pwMod[i][r - l + 1]) % hashMod[i];
			t = (t + hashMod[i]) % hashMod[i];
			res[i] = t;
		}
		return res;
	}
};

bool equal(const vector<int>& h1, const vector<int>& h2) {
	assert(h1.size() == h2.size());
	for (unsigned i = 0; i < h1.size(); i++)
		if (h1[i] != h2[i]) return false;
	return true;
}

//下面是应用示例；

int n;
StringWithHash s, t;
char str[L];

void work() {
	int len = strlen(str);  // 取字符串长度
	t.init();
	for (int j = 0; j < len; ++j) t.extend(str[j]);
	int d = 0;
	for (int j = min(len, s.ls); j >= 1; --j) {
		if (equal(t.getHash(1, j), s.getHash(s.ls - j + 1, s.ls))) {  // 比较哈希值
			d = j;
			break;
		}
	}
	for (int j = d; j < len; ++j) s.extend(str[j]);  // 更新答案数组
}
