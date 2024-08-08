#include <bits/stdc++.h>

template <class T, size_t size = std::tuple_size<T>::value>
std::string to_debug(T, std::string s = "") requires(not std::ranges::range<T>);
std::string to_debug(auto x) requires requires(std::ostream& os) { os<<x; } { return static_cast<ostringstream>(ostringstream()<<x).str(); }
std::string to_debug(std::ranges::range auto x, std::string s = "") requires(not std::is_same_v<decltype(x), std::string>) { for (auto xi:x) { s += ", "+to_debug(xi); }return "["+s.substr(s.empty() ? 0 : 2)+"]"; }
template <class T, size_t size>
std::string to_debug(T x, std::string s) requires(not std::ranges::range<T>) { [&] <size_t... I>(index_sequence<I...>) { ((s += ", "+to_debug(get<I>(x))), ...); }(make_index_sequence<size>()); return "("+s.substr(s.empty() ? 0 : 2)+")"; }
#define dbg(...) cout << __LINE__ << ": (" #__VA_ARGS__ ") = " << to_debug(tuple(__VA_ARGS__)) << endl
