#include<bits/stdc++.h>

using namespace std;


//通过前缀和求原矩阵 [(x1,y1),(x2,y2)]的矩阵和,下标从0开始，所以函数里面+1
int getRect(const vector<vector<int>>& P, int x1, int y1, int x2, int y2) {
	return P[x2+1][y2+1] - P[x1][y2+1] - P[x2+1][y1] + P[x1][y1];
}

//从前缀和复原，前缀下标1开始，复原的下标0开始
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

//求二维前缀和，从1开始
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

//从二维差分复原,差分下标从1开始 
void restoreDiff(vector<vector<int>>& diff,vector<vector<int>>& g) {
	int n=g.size(),m=g[0].size();
	// 用二维前缀和复原（原地修改）
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

