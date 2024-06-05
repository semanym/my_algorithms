#include<bits/stdc++.h>

using namespace std;


//ͨ��ǰ׺����ԭ���� [(x1,y1),(x2,y2)]�ľ����,�±��0��ʼ�����Ժ�������+1
int getRect(const vector<vector<int>>& P, int x1, int y1, int x2, int y2) {
	return P[x2+1][y2+1] - P[x1][y2+1] - P[x2+1][y1] + P[x1][y1];
}

//��ǰ׺�͸�ԭ��ǰ׺�±�1��ʼ����ԭ���±�0��ʼ
vector<vector<int>> restore(vector<vector<int>>& P) {
	int n=P.size(),m=P[0].size();
	vector<vector<int>> mat(n-1, vector<int>(m-1,0));
	for(int i=1; i<n; ++i) {
		for(int j=1; j<m; ++j) {
			mat[i-1][j-1]+=P[i][j]-P[i-1][j]-P[i][j-1]+P[i-1][j-1];
		}
	}
	return mat;
}

//���άǰ׺�ͣ���1��ʼ
vector<vector<int>> getPre(vector<vector<int>>& mat) {
	int n = mat.size(), m = mat[0].size();
	vector<vector<int>> P(n + 1, vector<int>(m + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
		}
	}
	return P;
}

//�Ӷ�ά��ָ�ԭ,����±��1��ʼ 
void restoreDiff(vector<vector<int>>& diff,vector<vector<int>>& g) {
	int n=g.size(),m=g[0].size();
	// �ö�άǰ׺�͸�ԭ��ԭ���޸ģ�
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			diff[i][j] += diff[i][j - 1] + diff[i - 1][j] - diff[i - 1][j - 1];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] += diff[i + 1][j + 1];
		}
	}
}

int main() {
	vector<vector<int>> y= {{1,2,3,4,5},{2,6,9,56,98},{48,94,4,62,56},{98,23,49,95,6}};
	auto p = getPre(y);
	for(auto r:p){
		for(int l:r){
			cout<<l<<" ";
		}
		cout<<"\n";
	}
	for(int i=0; i<3; ++i) {
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;

		auto ans=getRect(p,x1,y1,x2,y2);
		for(int i=x1; i<=x2; ++i) {
			for(int j=y1; j<=y2; ++j) {
				ans-=y[i][j];
			}
		}
		cout<<ans<<"\n";
	}
	auto m=restore(p);
	for(int i=0;i<4;++i){
		for(int j=0;j<5;++j){
			cout<<m[i][j]<<" ";
		}
		cout<<"\n";
	}

	return 0;
}

