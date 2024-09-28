#include<bits/stdc++.h>
using namespace std;

template <class T>
constexpr T power(T a, long long b) {
    T res{ 1 };
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr long long mul(long long a, long long b, long long p) {
    long long res = a * b - (long long)(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template <long long P>
struct MInt {
    long long x;

    constexpr MInt() : x{ 0 } {}

    constexpr MInt(long long x) : x{ norm(x % getMod()) } {}

    static long long Mod;

    constexpr static long long getMod() {
        if (P > 0) {
            return P;
        }
        else {
            return Mod;
        }
    }

    constexpr static void setMod(long long Mod_) {
        Mod = Mod_;
    }

    [[nodiscard]] constexpr long long norm(long long v) const {
        if (v < 0) {
            v += getMod();
        }
        if (v >= getMod()) {
            v -= getMod();
        }
        return v;
    }

    [[nodiscard]] constexpr long long val() const {
        return x;
    }

    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }

    [[nodiscard]] constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }

    constexpr MInt& operator*=(MInt rhs)& {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        }
        else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }

    constexpr MInt& operator+=(MInt rhs)& {
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr MInt& operator-=(MInt rhs)& {
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr MInt& operator/=(MInt rhs)& {
        return *this *= rhs.inv();
    }

    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }

    friend constexpr std::istream& operator>>(std::istream& is, MInt& a) {
        long long v;
        is >> v;
        a = MInt(v);
        return is;
    }

    friend constexpr std::ostream& operator<<(std::ostream& os, const MInt& a) {
        return os << a.val();
    }

    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }

    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }

    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};

template <>
long long MInt<0>::Mod = 998244353;

constexpr int P = 998244353;
using Z = MInt<P>;
