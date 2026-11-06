// @title Euclid
// @brief 类欧几里得算法
// @complexity O(\log \max(a,c))
// @author yzj
namespace Euclid {
        using ll = long long;
        const mint inv2 = 499122177, inv6 = 166374059;
        struct Data { mint f, g, h; };

        inline Data calc (ll n, ll a, ll b, ll c) {
                if(n < 0) return {};

                ll A = a / c, B = b / c;
                a %= c; b %= c;
                if(a < 0) a += c, --A;
                if(b < 0) b += c, --B;

                mint N = n % MOD, s0 = N + 1;
                mint s1 = N * s0 * inv2;
                mint s2 = N * s0 * (2 * N + 1) * inv6;

                if(A || B) {
                        Data t = calc(n, a, b, c);
                        mint x = A % MOD, y = B % MOD;
                        return {
                                t.f + x * s1 + y * s0,
                                t.g + x * x * s2 + y * y * s0
                                        + 2 * x * t.h + 2 * y * t.f
                                        + 2 * x * y * s1,
                                t.h + x * s2 + y * s1
                        };
                }

                ll m = ((__int128)a * n + b) / c;
                if(!m) return {};

                Data t = calc(m - 1, c, c - b - 1, a);
                mint M = m % MOD;
                return {
                        N * M - t.f,
                        N * M * M - 2 * t.h - t.f,
                        M * s1 - (t.g + t.f) * inv2
                };
        }
// f: sum floor((a*i+b)/c)
// g: sum floor((a*i+b)/c)^2
// h: sum i*floor((a*i+b)/c)
}
