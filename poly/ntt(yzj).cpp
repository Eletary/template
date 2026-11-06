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
                assert (n <= MAXN);
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
                if (a.empty () || b.empty ()) return poly ();
                int h; init (h = a.size () + b.size () - 1);
                poly f (t); Resize (a, t); Resize (b, t);
                dft (a); dft (b);
                rep (i, 0, t - 1) f[i] = a[i] * b[i];
                idft (f); Resize (f, h);
                return f;
        }
        poly deriv (poly a) {
                int n = a.size ();
                poly b (n ? n - 1 : 0);
                rep (i, 1, n - 1) b[i - 1] = a[i] * i;
                return b;
        }
        poly integ (poly a) {
                int n = a.size ();
                static vc <mint> iv = {0, 1};
                for (int i = iv.size (); i <= n; i ++) iv.pb (mint (MOD - MOD / i) * iv[MOD % i]);
                poly b (n + 1);
                rep (i, 0, n - 1) b[i + 1] = a[i] * iv[i + 1];
                return b;
        }
        // Return the first n coefficients; omitted coefficients of a are zero.
        poly inv (poly a, int n) {
                if (!n) return poly ();
                assert (!a.empty () && a[0].x);
                Resize (a, n);
                poly b (1); b[0] = qinv (a[0]);
                for (int m = 1; m < n; m <<= 1) {
                        int k = min (m << 1, n);
                        poly c (k);
                        rep (i, 0, k - 1) c[i] = a[i];
                        c = c * b; Resize (c, k);
                        rep (i, 0, k - 1) c[i] = mint (0) - c[i];
                        c[0] += 2;
                        b = b * c; Resize (b, k);
                }
                return b;
        }
        poly ln (poly a, int n) {
                if (!n) return poly ();
                assert (!a.empty () && a[0].x == 1);
                if (n == 1) return poly (1);
                Resize (a, n);
                poly b = deriv (a) * inv (a, n - 1);
                Resize (b, n - 1);
                return integ (b);
        }
        poly exp (poly a, int n) {
                if (!n) return poly ();
                assert (a.empty () || !a[0].x);
                Resize (a, n);
                poly b (1); b[0] = 1;
                for (int m = 1; m < n; m <<= 1) {
                        int k = min (m << 1, n);
                        poly c = ln (b, k);
                        rep (i, 0, k - 1) c[i] = a[i] - c[i];
                        c[0] += 1;
                        b = b * c; Resize (b, k);
                }
                return b;
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
