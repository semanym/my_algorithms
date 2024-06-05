/**
 * ax恒等于1(mod b),则x称为a mod b的逆元，记作a^-1
 * ax恒等于1(mod b)根据费马小定理
 * ax恒等于a^(b-1)
 * x恒等于a^(b-2)
 * 
 * 
*/
int MOD;
//就是快速幂而已
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
    //示例
    long long a;
    int x=qpow(a,MOD-2);
}
