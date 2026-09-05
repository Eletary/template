// @title 计数常用代码
// @brief mint 类和 poly 类
// @complexity O(n log n)
// @author yzj
const int MOD = 998244353;
 
// CALC
inline void inc (int &x, int y) { x += y - MOD; x += (x >> 31) & MOD; }
struct mint {
        int x; 
        mint (int ix = 0) { x = ix % MOD; if(x < 0) x += MOD; }
        mint operator += (mint a) { inc (x, a.x); return a; }
        mint operator -= (mint a) { inc (x, MOD - a.x); return a; }
        mint operator *= (mint a) { x = 1ll * x * a.x % MOD; return a; }
        mint friend operator + (mint a, mint b) { a += b; return a; }
        mint friend operator - (mint a, mint b) { a -= b; return a; }
        mint friend operator * (mint a, mint b) { a *= b; return a; }
} fc[N], ifc[N];
inline mint qpow (mint a, int b) { mint res = 1; for(; b; b >>= 1, a *= a) if(b & 1) res *= a; return res; }
inline mint qinv (mint a) { return qpow(a.x, MOD - 2); }
inline mint binom (int n, int m) { return n < m ? 0 : fc[n] * ifc[m] * ifc[n - m]; }
//

namespace Poly {
        const int MAXN = 1 << 22;
        int t, bit, rev[MAXN];

        struct poly : vc <mint> {
                poly (int n = 0) { resize (n); for (auto &u : (*this)) u = 0; } 
                inline void show () {
                        for (auto u : (*this)) cerr << u.x << " ";
                        cerr << endl;
                }
        } ;

        inline void Resize (poly &a, int n) {
                while (a.size () < n) a.pb (0);
                while (a.size () > n) a.pop_back ();
        }
        inline void init (int n) {
                t = 2, bit = 1; while (t < n) t <<= 1, ++ bit;
                rep (i, 0, t - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
        }
        inline void dft (poly &a) {
                rep (i, 0, t - 1) if (i < rev[i]) swap (a[i], a[rev[i]]);
                mint o = 1, w = qpow (3, (MOD - 1) >> 1), x, y;
                for (int m = 1; m < t; m <<= 1, w = qpow (3, (MOD - 1) / (m << 1)))
                        for (int i = 0; i < t; i += (m << 1), o = 1) for (int j = 0; j < m; j ++, o = o * w)
                                x = a[i + j], y = o * a[i + j + m], a[i + j] = x + y, a[i + j + m] = x - y;
        }
        inline void idft (poly &a) {
                dft (a); auto inv = qinv (t);
                reverse (a.begin () + 1, a.end ());
                for (auto &u : a) u *= inv;
        }
        poly operator * (poly a, poly b) {
                int h; init (h = a.size () + b.size () - 1);
                poly f (t); Resize (a, t); Resize (b, t);
                dft (a); dft (b);
                rep (i, 0, t - 1) f[i] = a[i] * b[i];
                idft (f); Resize (f, h);
                return f;
        }
}

int n, c[N], g[N];

inline Poly :: poly solve (int l, int r) {
        if (l == r) {
                Poly :: poly f (c[l] + 1);
                rep (i, 0, min (c[l],  g[l]))   
                        if (i & 1) f[c[l] - i] = MOD - binom (c[l], i) * binom (g[l], i) * fc[i];
                        else f[c[l] - i] = binom (c[l], i) * binom (g[l], i) * fc[i];
                return f;
        }
        int mid = ((l + r) >> 1);
        return solve (l, mid) * solve (mid + 1, r);
}
