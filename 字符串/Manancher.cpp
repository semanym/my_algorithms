#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn=11000002;
char data[maxn<<1];
int p[maxn<<1],cnt,ans;

inline void qr() {
	char c=getchar();
	data[0]='~',data[cnt=1]='|';
	while(c<'a'||c>'z') c=getchar();
	while(c>='a'&&c<='z') data[++cnt]=c,data[++cnt]='|',c=getchar();
}

int main() {
	qr();
	for(int t=1,r=0,mid=0; t<=cnt; ++t) {
		if(t<=r) p[t]=min(p[(mid<<1)-t],r-t+1);
		while(data[t-p[t]]==data[t+p[t]]) ++p[t];
		//������չ��������,��t-p[t]==0ʱ������data[0]��'~'���Զ�ֹͣ���ʲ����±������
		//����������ɹ�������չ�ˣ�����ζ�ŵ�ʱ��r�ᵥ������������manacher�����Եġ�
		if(p[t]+t>r) r=p[t]+t-1,mid=t;
		//����mid��r,����r�����ҵĲ��ܱ�֤������ǰȷ���Ĳ��ֻ��İ뾶�����ࡣ
		if(p[t]>ans) ans=p[t];
	}
	cout<<ans-1<<"\n";//���

	//��ϸ��
	for(int i=0; i<=cnt; ++i) {
		cout<<data[i]<<" ";
	}
	for(int i=0; i<=cnt; ++i) {
		cout<<p[i]<<" ";
	}
	return 0;
}
