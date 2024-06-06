#include <bits/stdc++.h>
using namespace std;

const int L = 1e6 + 5;
const int HASH_CNT = 2;

int hashBase[HASH_CNT] = {29, 31};
int hashMod[HASH_CNT] = {1000000009,998244353};
//1000000009,998244353,402653189,201326611,100663319,50331653,1000000007

struct StringWithHash {
	char s[L];//��1��ʼ��
	int ls;
	int hsh[HASH_CNT][L];
	int pwMod[HASH_CNT][L];

	void init() {  // ��ʼ��
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
		s[++ls] = c;                          // ��¼�ַ�����ÿһ���ַ�
		for (int i = 0; i < HASH_CNT; ++i) {  // ˫��ϣ��Ԥ����
			pwMod[i][ls] =
			    1ll * pwMod[i][ls - 1] * hashBase[i] % hashMod[i];  // �õ�b^ls
			hsh[i][ls] = (1ll * hsh[i][ls - 1] * hashBase[i] + c) % hashMod[i];
		}
	}

	vector<int> getHash(int l, int r) {  // �õ���ϣֵ��ע�⣡���±��0��ʼ����Ϊ���������++
		l++,r++;
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

bool equal(const vector<int> &h1, const vector<int> &h2) {
	assert(h1.size() == h2.size());
	for (unsigned i = 0; i < h1.size(); i++)
		if (h1[i] != h2[i]) return false;
	return true;
}

//������Ӧ��ʾ����

int n;
StringWithHash s, t;
char str[L];

void work() {
	int len = strlen(str);  // ȡ�ַ�������
	t.init();
	for (int j = 0; j < len; ++j) t.extend(str[j]);
	int d = 0;
	for (int j = min(len, s.ls); j >= 1; --j) {
		if (equal(t.getHash(1, j), s.getHash(s.ls - j + 1, s.ls))) {  // �ȽϹ�ϣֵ
			d = j;
			break;
		}
	}
	for (int j = d; j < len; ++j) s.extend(str[j]);  // ���´�����
}
