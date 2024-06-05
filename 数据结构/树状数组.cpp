//ע�⣡��
//tree���±�1��ʼ��nums���±�0��ʼ������
class NumArray {
	private:
		vector<int> nums;
		vector<long long> tree;

		long long prefixSum(int i) {
			long long s = 0;
			for (; i > 0; i &= i - 1) { // i -= i & -i ����һ��д��
				s += tree[i];
			}
			return s;
		}

	public:
		NumArray(vector<int> &nums) : nums(nums), tree(nums.size() + 1) {
			for (int i = 1; i <= nums.size(); i++) {
				tree[i] += nums[i - 1];
				int nxt = i + (i & -i); // ��һ���ؼ�������Ҷ˵�
				if (nxt <= nums.size()) {
					tree[nxt] += tree[i];
				}
			}
		}

		void add(int index, int val) {
			nums[index] += val;
			for (int i = index + 1; i < tree.size(); i += i & -i) {
				tree[i] += val;
			}
		}

		void update(int index, int val) {
			int delta = val - nums[index];
			add(index,delta);
		}
//����ұ�
		long long sumRange(int left, int right) {
			return prefixSum(right + 1) - prefixSum(left);
		}
};

