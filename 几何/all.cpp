#include <bits/stdc++.h>
using namespace std;

const long double PI = (long double)3.14159265358979323846264338327950288419716939937510;
const long double eps = 1e-12;

int sgn(long double num) { // 判正负
    return num > eps ? 1 : (num < -eps ? -1 : 0);
}
long long sqr(long long num) { return num * num; }; // 平方

struct point { // 点类
    point(){};
    point(long double X, long double Y) : x(X), y(Y){};
    long double x, y;
    point operator+(const point another) const {
        return {x + another.x, y + another.y};
    }
    point operator-(const point another) const {
        return {x - another.x, y - another.y};
    }
    point operator*(const long double num) const {
        return {x * num, y * num};
    }
    point operator/(const long double num) const {
        return {x / num, y / num};
    }
    bool operator == (const point another) const {
        return sgn(x - another.x) == 0 && sgn(y - another.y) == 0;
    }
    bool operator < (const point another) const {
        if (sgn(x - another.x) == 0) {
            return sgn(y - another.y) < 0;
        } else {
            return sgn(x - another.x) < 0;
        }
    }
    point rotate(long double t) const {
        return {x * cos(t) - y * sin(t), x * sin(t) - y * cos(t)};
    }
    point rot90() const {
        return {-y, x};
    }
    point unit() const {
        return *this / sqrtl(sqr(x) + sqr(y));
    }
};
struct line { // 线类
    line(point S, point T) : s(S), t(T){};
    point s, t;
};
long double dis(point a, point b) { // 直线距离
    return sqrtl(sqr(a.x - b.x) + sqr(a.y - b.y));
}
long long dis_2(point a, point b) { // 距离平方
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}
long double dot(point a, point b) { // 点乘
    return a.x * b.x + a.y * b.y;
}
long double det(point a, point b) { // 叉乘
    return a.x * b.y - a.y * b.x;
}
bool ture_left(point a, point b, point c) { // 判点在线左边
    return sgn(det(b - a, c - a)) > 0;
}
bool same_dir(line a, line b) { // 判两线同向
    return sgn(det(a.t - a.s, b.t - b.s)) == 0 && sgn(dot(a.t - a.s, b.t - b.s)) > 0;
}
bool point_on_segment(point a, line l) { // 点在线段上
    return sgn(det(a - l.s, l.t - a)) == 0 && sgn(dot(a - l.s, l.t - a)) >= 0;
}
bool two_side(point a, point b, line c) { // 两点在线两边
    return sgn(det(a - c.s, c.t - c.s)) * sgn(det(b - c.s, c.t - c.s)) < 0;
}
bool inter_judge(line a, line b) { // 两直线判交
    if (point_on_segment(a.s, b) ||
        point_on_segment(a.t, b) ||
        point_on_segment(b.s, a) ||
        point_on_segment(b.t, a))
        return true;
    return two_side(a.s, a.t, b) && two_side(b.s, b.t, a);
}
point line_intersect(line a, line b) { // 两直线交点
    long double u = det(b.t - b.s, a.s - b.s);
    long double v = det(a.t - b.s, b.t - b.s);
    return (a.s * u + a.t * v) / (u + v);
}
bool ray_intersect_judge(line a, line b) { // 射线判交
    long double s1 = det(a.t - a.s, b.s - a.s);
    long double s2 = det(a.t - a.s, b.t - a.s);
    if (sgn(s1) == 0 && sgn(s2) == 0) {
        return sgn(dot(a.t - a.s, b.s - a.s) >= 0
                || dot(b.t - b.s, a.s - b.s) >= 0);
    }
    if (!sgn(s2 - s1) || sgn(s1) == sgn(s2 - s1))   return false;
    std::swap(a, b);
    s1 = det(a.t - a.s, b.s - a.s);
    s2 = det(a.t - a.s, b.t - a.s);
    return sgn(s1) != sgn(s2 - s1);
}
long double point_to_line(point a, line b) { // 点到直线距离
    return abs(det(b.t - b.s, a - b.s) / dis(b.s, b.t));
}
point project_to_line(point a, line b) { // 点在直线的投影
    return b.s + (b.t - b.s) * (dot(b.t - b.s, a - b.s) / dis_2(b.s, b.t));
}
long double point_to_segment(point a, line b) { // 点到线段的距离
    if (sgn(dot(b.s - a, b.t - b.s)) * sgn(dot(b.t - a, b.t - b.s)) <= 0)
        return abs(det(b.t - b.s, a - b.s) / dis(b.s, b.t));
    return std::min(dis(a, b.s), dis(a, b.t));
}
std::vector<point> convex_hull(std::vector<point> a) { // 求凸包
    int n = a.size();
    if (n <= 2) return a;
    std::sort(a.begin(), a.end());
    std::vector<point> ret;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        while (cnt > 1
            && !ture_left(ret[cnt - 2], ret[cnt - 1], a[i]))
            cnt--, ret.pop_back();
        cnt++, ret.push_back(a[i]);
    }
    int fixed = (int)ret.size();
    for (int i = n - 2; i >= 0; i--) {
        while (cnt > fixed
            && !ture_left(ret[cnt - 2], ret[cnt - 1], a[i]))
            cnt--, ret.pop_back();
        cnt++, ret.push_back(a[i]);
    }
    ret.pop_back();
    return ret;
}
 
long double convex_diameter(std::vector<point> a) { // 凸包直径
    int n = a.size();
    long double ret = 0;
    int nxt = 0;
    for (int i = 0; i < n; i++) {
        while (dis_2(a[i], a[nxt]) < dis_2(a[i], a[(nxt + 1) % n]))
            nxt = (nxt + 1) % n;
        ret = max(ret, (long double)dis_2(a[i], a[nxt]));
    }
    return sqrtl(ret);
}
 
long double area(std::vector<point> a) { // 多边形面积
    long double ret = 0;
    for (int i = 0; i < a.size(); i++) {
        int j = (i + 1) % a.size();
        ret += det(a[i], a[j]);
    }
    return abs(ret / 2);
}
struct Convex {
    int n;
    std::vector<point> a, lower, upper;
    Convex(std::vector<point> _a): a(_a) {
        n = a.size();
        int k = 0;
        for (int i = 1; i < n; i++) 
            if (a[k] < a[i])    k = i;
        for (int i = 0; i <= k; i++)
            lower.push_back(a[i]);
        for (int i = k; i <= n; i++)
            upper.push_back(a[i % n]);
    }
    bool contain(point p) { // 点在凸包内
        if (p.x < lower[0].x || p.x > lower.back().x)
            return false;
        int it = lower_bound(lower.begin(), lower.end(), point(p.x, -1e9)) - lower.begin();
        if (p.x == lower[it].x) {
            if (p.y < lower[it].y)  return false;
        } else if (det(lower[it - 1] - p, lower[it] - p) < 0){
            return false;
        }
        it = lower_bound(upper.begin(), upper.end(), point(p.x, 1e9)) - upper.begin();
        if (p.x == upper[it].x) {
            if (p.y > upper[it].y) return false;
        } else if (det(upper[it - 1] - p, upper[it] - p) < 0) {
            return false;
        }
        return true;
    }
 
};