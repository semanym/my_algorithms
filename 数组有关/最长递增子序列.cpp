#include<bits/stdc++.h>
using namespace std;

/*
Ҳ����dp��
dp i�ĺ������� i��β�����������������еĳ���
dp i�ĸ���,jΪ0~i-1��nums[j]С�ڵ���nums[i]���±�
��ôdp[i]=max(dp[i],dp[j]+1)
��ʼ��ÿ������1
*/


//����Ƿǵݼ��͸�Ϊ�ӵ���
//��������


int lengthOfLIS(vector<int> &nums) {
	auto end = nums.begin();
	for (int x : nums) {
		auto it = lower_bound(nums.begin(), end, x);
		*it = x;
		if (it == end) { // >=x �� g[j] ������
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
			g.push_back(x); // >=x �� g[j] ������
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

