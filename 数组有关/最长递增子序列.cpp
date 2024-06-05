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
//�������ģ����ص������±�0�����ȣ����±�1��ʼ�����һ����������� 
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
			// ����Ҳ���˵�����е������� nums[i]
			// �󣬴�ʱҪ���� d[1]���������ｫ pos ��Ϊ 0
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

