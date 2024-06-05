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


int lengthOfLIS1(vector<int> &nums) {
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


/*
很遗憾我尝试返回最前的一个数组，但是fail了 
vector<int> lengthOfLIS(vector<int>& nums) {
	int n = nums.size();
	if (n == 0) return {0};
	vector<int> d(n + 1, 0),from(n, -1),index(n + 1);int final = 0;
	d[0] = 1; d[d[0]] = nums[0];index[1] = 0;index[0] = -1;
	for (int i = 1; i < n; ++i) {
		if (nums[i] > d[d[0]]) {//>=
			d[++d[0]] = nums[i];index[d[0]] = i;final=i;
			if(from[i] == -1) from[i] = index[d[0]-1];
		} else {
			int l = 1, r = d[0], pos = 0;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (d[mid] < nums[i]) {//<=
					pos = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			d[pos + 1] = nums[i]; index[pos + 1] = i;
			if(pos > 0) from[i] = index[pos];
		} 
	}
	d.resize(d[0] + 1);
	for(int i=d[0];i>=1;--i){
		d[i]=nums[final];final=from[final];
	}
	return d;
}
*/

int main() {
	int n;
	cin>>n;
	vector<int> nums(n);
	for(int i=0; i<n; ++i) {
		cin>>nums[i];
	}
	auto ans=lengthOfLIS(nums);
	for(auto a:ans){
		cout<<a<<" ";
	}

	return 0;
}

