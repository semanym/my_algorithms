#include<bits/stdc++.h> 
using namespace std;

long long x,y,ans,r,s;

//��1��q�������䣬�������ֵ������ĺ� 
//On���� 
long long wk(long long q){
	ans=0;
	for(long long i=1;i<=q;i++) ans+=q/i*i;//q/i�����м���i�ı���,��*i�������ǵĺ�.
	return ans;
} 
//���� 
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

