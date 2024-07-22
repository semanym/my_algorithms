#include <bits/stdc++.h>
using namespace std;

template <class T, size_t size = tuple_size<T>::value>
string to_debug(T, string s = "") requires(not ranges::range<T>);
string to_debug(auto x) requires requires(ostream& os) { os<<x; }
{
    return static_cast<ostringstream>(ostringstream()<<x).str();
}
string to_debug(ranges::range auto x, string s = "") requires(not is_same_v<decltype(x), string>)
{
    for (auto xi:x) s += ", "+to_debug(xi);
    return "["+s.substr(s.empty() ? 0 : 2)+"]";
}
template <class T, size_t size>
string to_debug(T x, string s) requires(not ranges::range<T>)
{
    [&] <size_t... I>(index_sequence<I...>) { ((s += ", "+to_debug(get<I>(x))), ...); }(make_index_sequence<size>());
    return "("+s.substr(s.empty() ? 0 : 2)+")";
}
#define dbg(...) cout << __LINE__ << ": (" #__VA_ARGS__ ") = " << to_debug(tuple(__VA_ARGS__)) << endl

using ll = long long;
using i64 = long long;
#define fast_read ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define all(x) x.begin(), x.end()
#define pb push_back
#define pii pair<int,int>
#define int long long

void solve()
{
    
}

int32_t main()
{
    fast_read
    int _ =1;cin>>_;
    while (_--)
    {
        solve();
    }
    return 0;
}
