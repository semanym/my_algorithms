#include<bits/stdc++.h> 
using namespace std;

const int N = 2e8+5;

int n;
int prime[N], cnt;
bool st[N];

void get_primes(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!st[i]) prime[cnt ++] = i;
		for (int j = 0; prime[j] <= n / i; ++j) {
			st[prime[j] * i] = true;
			if (i % prime[j] == 0) break;
		}
	}
}


// i % pri_j == 0
// 换言之，i 之前被 pri_j 筛过了
// 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
// pri_j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
// 掉就好了
vector<int> pri;
bool not_prime[N];

void pre(int n) {
	for (int i = 2; i <= n; ++i) {
		if (!not_prime[i]) {
			pri.push_back(i);
		}
		for (int pri_j : pri) {
			if (i * pri_j > n) break;
			not_prime[i * pri_j] = true;
			if (i % pri_j == 0) {
				break;
			}
		}
	}
}

int _sum=0;
int32_t main(){
	pre(2e8+2);
	for(auto a:pri){
        string temp=to_string(a);
        string b=temp;
        reverse(b.begin(),b.end());
        if(b==temp){
        	++_sum;
            cout<<a<<",";
        }
    }
    cout<<"\n"<<_sum;
	return 0;
}
