/**
������ 
*/

long long pow(long long x, int n) {
    long long res = 1;
    for (; n; n /= 2) {
        if (n % 2) {
            res = res * x % MOD;
        }
        x = x * x % MOD;
    }
    return res;
}

class Solution {
public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        // ���׵ĳ�ʼֵΪ x
        double x_contribute = x;
        // �ڶ� N ���ж����Ʋ�ֵ�ͬʱ�����
        while (N > 0) {
            if (N % 2 == 1) {
                // ��� N �����Ʊ�ʾ�����λΪ 1����ô��Ҫ���빱��
                ans *= x_contribute;
            }
            // �����ײ��ϵ�ƽ��
            x_contribute *= x_contribute;
            // ���� N �����Ʊ�ʾ�����λ����������ÿ��ֻҪ�ж����λ����
            N /= 2;
        }
        return ans;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};


