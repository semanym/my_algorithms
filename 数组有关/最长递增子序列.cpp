#include<bits/stdc++.h>
using namespace std;

/*
也可以dp做
dp i的含义是以 i结尾的数组的最长递增子序列的长度
dp i的更新,j为0~i-1中nums[j]小于等于nums[i]的下标
那么dp[i]=max(dp[i],dp[j]+1)
初始化每个都是1
*/


//如果是非递减就改为加等于
//二分做的


int lengthOfLIS(vector<int> &nums) {
	auto end = nums.begin();
	for (int x : nums) {
		auto it = lower_bound(nums.begin(), end, x);
		*it = x;
		if (it == end) { // >=x 的 g[j] 不存在
			++end;
		}
	}
	return end - nums.begin();
}


int lengthOfLIS(vector<int> &nums) {
	vector<int> g;
	for (int x : nums) {
		auto it = ranges::lower_bound(g, x);
		if (it == g.end()) {
			g.push_back(x); // >=x 的 g[j] 不存在
		} else {
			*it = x;
		}
	}
	return g.size();
}

int main() {
	int n;
	cin>>n;
	vector<int> nums(n);
	for(int i=0; i<n; ++i) {
		cin>>nums[i];
	}
	cout<<lengthOfLIS(nums)<<"\n";

	return 0;
}

