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
//二分做的，返回的数组下标0代表长度，从下标1开始代表第一个最长的子数组 
vector<int> lengthOfLIS(vector<int>& nums) {
	int n = nums.size();
	if (n == 0) {
		return {0};
	}
	vector<int> d(n + 1, 0);
	d[0] = 1; d[d[0]] = nums[0];
	for (int i = 1; i < n; ++i) {
		if (nums[i] > d[d[0]]) {//>=
			d[++d[0]] = nums[i];
		} else {
			int l = 1, r = d[0], pos = 0; 
			// 如果找不到说明所有的数都比 nums[i]
			// 大，此时要更新 d[1]，所以这里将 pos 设为 0
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (d[mid] < nums[i]) {//<=
					pos = mid;
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			d[pos + 1] = nums[i];
		}
	}
	return d;
}


int main(){
    int n;cin>>n;
    vector<int> nums(n);
    for(int i=0;i<n;++i){
        cin>>nums[i];
    }
    auto ans=lengthOfLIS(nums);
    cout<<ans[0]<<"\n";
    
    return 0;
}

