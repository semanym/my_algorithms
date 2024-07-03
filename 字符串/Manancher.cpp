#include <bits/stdc++.h>
using namespace std;

const int maxn = 500006;
//�е�ʱ�򿪴��ˣ�����main����������ܱ��ڴ�
//ֻ��Сд��ĸ
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
			//������չ��������,��t-p[t]==0ʱ������cstring[0]��'~'���Զ�ֹͣ���ʲ����±������
			//����������ɹ�������չ�ˣ�����ζ�ŵ�ʱ��r�ᵥ������������manacher�����Եġ�
			if (p[t]+t>r) r = p[t]+t-1, mid = t;
			//����mid��r,����r�����ҵĲ��ܱ�֤������ǰȷ���Ĳ��ֻ��İ뾶�����ࡣ
			if (p[t]>ans) ans = p[t];
		}
		return ans-1;
	}
};

Manacher m;

int main() {
	m.readS();
	cout<<m.op()<<"\n";

	//��ϸ��
	for (int i = 0; i<=m.cnt; ++i) {
		cout<<m.cstring[i]<<" ";
	}
	for (int i = 0; i<=m.cnt; ++i) {
		cout<<m.p[i]<<" ";
	}
	return 0;
}
