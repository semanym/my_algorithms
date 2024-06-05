#include<bits/stdc++.h> 
using namespace std;

long long x,y,ans,r,s;

//求1到q，闭区间，所有数字的因数的和 
//On做法 
long long wk(long long q){
	ans=0;
	for(long long i=1;i<=q;i++) ans+=q/i*i;//q/i代表有几个i的倍数,再*i代表它们的和.
	return ans;
} 
//更优 
long long wk(long long q){
	ans=0;
	for(long long l=1;l<=q;l=r+1){
		s=q/l;
		r=q/s;
		ans+=s*(l+r)*(r-l+1)/2;
	} 
	return ans;
} 

int main(){
	cin>>x>>y;
	cout<<wk(y)-wk(x-1);
	return 0;
}

int main(){
	for(int i=1;i<=100000;i++){
		long long sum=0;
		for(int j=1;j<=i;j++){
			if(i%j==0)sum+=j;
		}
		if(sum!=f[i]){
			cout<<sum<<" "<<f[i]<<'\n';
			cout<<i<<" "<<"cnmd!";
		}
		
	}
	cout<<"debug yes";

	return 0;
} 

