/**
 * ax�����1(mod b),��x��Ϊa mod b����Ԫ������a^-1
 * ax�����1(mod b)���ݷ���С����
 * ax�����a^(b-1)
 * x�����a^(b-2)
 * 
 * 
*/
int MOD;
//���ǿ����ݶ���
int qpow(long long a, int b) {
    int ans = 1;
    a = (a % MOD + MOD) % MOD;
    for (; b; b >>= 1) {
        if (b & 1) ans = (a * ans) % MOD;
        a = (a * a) % MOD;
    }
    return ans;
}

int main(){
    //ʾ��
    long long a;
    int x=qpow(a,MOD-2);
}
