#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
std::vector<i64>  M = { 1610612741,0,805306457,402653189,201326611,984295877,50331653,1384295981,1011123517 };
struct stringHash {
	int n;
	std::vector<i64> P1, P2, h1, h2;
	i64 p1 = 131, p2 = 13331;

	stringHash() :n(0) {};
	stringHash(std::string& s) :n(0) {
		Init(s);
	}
	void change() {
		std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
		while (M[1]==0||M[2]==0) shuffle(M.begin(), M.end(), rng);
		// srand(time(nullptr)); // 用当前时间作为种子
		// M[0] += rand() % 500;M[1] += rand() % 500;
	}
	void deal(int st, int len, std::string& s) {
		P1.resize(len+1);
		P2.resize(len+1);
		h1.resize(len+1);
		h2.resize(len+1);
		P1[0] = 1; P2[0] = 1;
		for (int i = st; i<=len; i++) {
			P1[i] = (P1[i-1]*p1)%M[1];
			h1[i] = (h1[i-1]*p1+s[i-st])%M[1];
			P2[i] = (P2[i-1]*p2)%M[2];
			h2[i] = (h2[i-1]*p2+s[i-st])%M[2];
		}
	}
	void Init(std::string& s) {
		if (M[1]==0) change();
		n = s.size();
		deal(1, n, s);
	}
	std::pair<i64, i64> get(int l, int r) {//闭区间，从1开始
		i64 t1 = ((h1[r]-h1[l-1]*P1[r-l+1])%M[1]+M[1])%M[1];
		i64 t2 = ((h2[r]-h2[l-1]*P2[r-l+1])%M[2]+M[2])%M[2];
		return { t1,t2 };
	}

	std::pair<i64, i64> add(int l1, int r1, int l2, int r2) {//前面的在前面
		std::pair<i64, i64> it1 = get(l1, r1), it2 = get(l2, r2), it3;
		it1.first *= P1[r2-l2+1] %= M[1];
		it1.second *= P2[r2-l2+1] %= M[2];
		it3.first = (it1.first+it2.first)%M[1];
		it3.second = (it1.second+it2.second)%M[2];
		return it3;
	}
	std::pair<i64, i64> add(std::pair<i64, i64> l, std::pair<i64, i64> r, i64 len) {//len是后面的长度
		std::pair<i64, i64> it;
		l.first *= P1[len] %= M[1];
		l.second *= P2[len] %= M[2];
		it.first = (l.first+r.first)%M[1];
		it.second = (l.second+r.second)%M[2];
		return it;
	}
	void push_back(std::string s) {
		int tn = (int)s.size();
		deal(n+1, tn+n, s);
		n = n+tn;
	}

	bool equal(std::pair<i64, i64> a, std::pair<i64, i64> b) {
		return a.first == b.first && a.second == b.second;
	}
};

int main() {
	string s = "abcdefg";
	stringHash sh(s);
	std::cout<<sh.get(4, 7).first<<" ";//defg

	string s2 = "defg";
	stringHash sh2(s2);
	cout<<sh2.get(1, 4).first<<"\n";//defg

	cout<<sh.get(1, 7).first<<" ";//abcdefg
	cout<<sh.add(sh.get(1, 3), sh2.get(1, 4), 4).first<<" ";//abcdefg
	cout<<sh.add(1, 3, 4, 7).first<<"\n";//abcdefg

	cout<<" "<<sh2.equal(sh.get(4, 7), sh2.get(1, 4))<<" ";
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
