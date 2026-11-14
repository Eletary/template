// @title Geometry basic
// @brief 分数、凸包、点在凸包内、闵可夫斯基和
// @complexity O(n log n)
// @author yzj
#include<bits/stdc++.h>

#define int long long
#define i128 __int128

#define vc vector
#define pb emplace_back
#define pii pair<int, int>
#define mkp make_pair
#define rep(i, a, b) for(int i = (a); i <= (b); ++i)
#define lep(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

inline int read() {
        int x = 0, w = 0;
        char ch = getchar();
        while(!isdigit(ch)) w |= (ch == '-'), ch = getchar();
        while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = getchar();
        return w ? -x : x;
}

const int N = 2e5 + 5;



inline i128 mygcd (i128 x, i128 y) { return y ? mygcd (y, x % y) : x; }
inline i128 myabs (i128 x) { return x < 0 ? - x : x; }
struct Frac {
        i128 p, q;
        Frac (i128 pp = 0, i128 qq = 1) : p (pp), q (qq) {
                if (q < 0) p = - p, q = - q;
                assert (q != 0);
                i128 g = mygcd (myabs (p), q);
                p /= g; q /= g;
        }

        Frac operator + (const Frac &a) const {
                i128 g = mygcd(q, a.q);
                return Frac(p * (a.q / g) + a.p * (q / g),
                        (q / g) * a.q);
        }

        Frac operator - (const Frac &a) const {
                i128 g = mygcd(q, a.q);
                return Frac(p * (a.q / g) - a.p * (q / g),
                        (q / g) * a.q);
        }

        Frac operator * (const Frac &a) const {
                i128 g1 = mygcd(myabs(p), a.q);
                i128 g2 = mygcd(myabs(a.p), q);
                return Frac((p / g1) * (a.p / g2),
                        (q / g2) * (a.q / g1));
        }

        Frac operator / (const Frac &a) const {
                assert(a.p != 0);
                i128 g1 = mygcd(myabs(p), myabs(a.p));
                i128 g2 = mygcd(q, a.q);
                return Frac((p / g1) * (a.q / g2),
                        (q / g2) * (a.p / g1));
        }

        bool operator < (const Frac &a) const {
                return (i128) p * a.q < (i128) a.p * q;
        }
        bool operator == (const Frac &a) const {
                return p == a.p && q == a.q;
        }
} ;

namespace Geometry {
        const double eps = 1e-7, PI = acos (- 1);
        struct Point { 
                int x, y;
                Point (int x = 0, int y = 0): x (x), y (y) {} 
                auto operator<=>(const Point&) const = default;
                Point operator - (const Point &a) const { return Point (x - a.x, y - a.y); }
                Point operator + (const Point &a) const { return Point (x + a.x, y + a.y); }
        } ;
        inline int half (Point a) { return a.y > 0 || (a.y == 0 && a.x > 0); }
        inline int crs (Point a, Point b) { return a.x * b.y - a.y * b.x; }
        inline int dot (Point a, Point b) { return a.x * b.x + a.y * b.y; }
        inline int cmp (Point a, Point b) {
                return half (a) == half (b) ? crs (a, b) > 0 : half (a) < half (b); 
        }
        inline vc<Point> ConvexHull (vc <Point> a) {
                sort (a.begin (), a.end ());
                a.erase (unique (a.begin (), a.end ()), a.end ());
                vc <Point> b;
                if (a.size () <= 1) return a;
                rep (t, 0, 1) {
                        int k = b.size ();
                        for (auto u : a) {
                                while ((b.size () >= k + 2) && crs (b.back () - b[b.size () - 2], u - b.back ()) <= 0) b.pop_back ();
                                b.pb (u);
                        }
                        b.pop_back ();
                        reverse (a.begin (), a.end ());
                }
                return b;
        }
        inline int inarea (const vc <Point> &a, Point u) {
                if (a.size () < 2) return 0;
                int pos = 0, neg = 0;
                for (int i = 0; i < a.size (); i ++) {
                        int v = crs (a[(i + 1) % a.size ()] - a[i], u - a[i]);
                        pos += (v > 0); neg += (v < 0);
                }
                return (pos == a.size ()) || (neg == a.size ());
        }

        inline bool onseg(Point a, Point b, Point p) {
                if (crs(b - a, p - a) != 0) return false;
                return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x)
                && min(a.y, b.y) <= p.y && p.y <= max(a.y, b.y);
        }

        // 要求 a 是逆时针凸包，不重复首尾顶点
        // 0: outside, 1: boundary, 2: inside
        inline int inConvex(const vc<Point> &a, Point p) {
                int n = a.size();
                if (n == 0) return 0;
                if (n == 1) return p == a[0] ? 1 : 0;
                if (n == 2) return onseg(a[0], a[1], p) ? 1 : 0;

                int x = crs(a[1] - a[0], p - a[0]);
                int y = crs(a[n - 1] - a[0], p - a[0]);

                if (x < 0 || y > 0) return 0;
                if (x == 0) return onseg(a[0], a[1], p) ? 1 : 0;
                if (y == 0) return onseg(a[0], a[n - 1], p) ? 1 : 0;

                int l = 1, r = n - 1;
                while (l + 1 < r) {
                        int mid = (l + r) >> 1;
                        if (crs(a[mid] - a[0], p - a[0]) >= 0)
                                l = mid;
                        else r = mid;
                }

                int s = crs(a[l + 1] - a[l], p - a[l]);
                if (s < 0) return 0;
                if (s == 0) return onseg(a[l], a[l + 1], p) ? 1 : 0;
                return 2;
        }
        inline vc<Point> Minkowski(vc<Point> a, vc<Point> b) {
                if (a.empty() || b.empty()) return {};
                if (a.size() == 1) {
                        for (auto &p : b) p = p + a[0];
                        return b;
                }
                if (b.size() == 1) {
                        for (auto &p : a) p = p + b[0];
                        return a;
                }

                auto cmp = [](Point a, Point b) {
                        return a.y != b.y ? a.y < b.y : a.x < b.x;
                };
                auto angleCmp = [](Point a, Point b) {
                        if (half(a) != half(b))
                                return half(a) > half(b) ? -1 : 1;
                        i128 v = (i128)a.x * b.y - (i128)a.y * b.x;
                        return v > 0 ? -1 : v < 0 ? 1 : 0;
                };

                rotate(a.begin(), min_element(a.begin(), a.end(), cmp), a.end());
                rotate(b.begin(), min_element(b.begin(), b.end(), cmp), b.end());

                int n = a.size(), m = b.size();
                int i = 0, j = 0;
                Point p = a[0] + b[0];

                vc<Point> c;
                while (i < n || j < m) {
                        c.pb(p);

                        if (i == n) {
                                p = p + b[(j + 1) % m] - b[j];
                                ++j;
                        } else if (j == m) {
                                p = p + a[(i + 1) % n] - a[i];
                                ++i;
                        } else {
                                Point u = a[(i + 1) % n] - a[i];
                                Point v = b[(j + 1) % m] - b[j];

                                int t = angleCmp(u, v);
                                if (t <= 0) p = p + u, ++i;
                                if (t >= 0) p = p + v, ++j;
                        }
                }
                return c;
        }
}

signed main () {
        return 0;
}
