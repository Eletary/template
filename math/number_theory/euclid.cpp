// @title Euclid
// @brief 
// @complexity O(\log max (a, c))
// @author yzj
namespace Euclid {
	const int mod = 998244353, inv2 = 499122177, inv6 = 166374059;
	struct Data { int f, g, h; };

	inline Data calc(int n, int a, int b, int c) {
		if(a >= c || b >= c) {
			int A = a / c, B = b / c;
			Data t = calc(n, a % c, b % c, c);
			int N = n % mod, s0 = (N + 1) % mod;
			int s1 = N * s0 % mod * inv2 % mod;
			int s2 = N * s0 % mod * (2 * N + 1) % mod * inv6 % mod;
			A %= mod; B %= mod;

			int f = (t.f + A * s1 + B * s0) % mod;
			int g = (t.g + A * A % mod * s2 + B * B % mod * s0
				+ 2 * A % mod * t.h + 2 * B % mod * t.f
				+ 2 * A % mod * B % mod * s1) % mod;
			int h = (t.h + A * s2 + B * s1) % mod;
			return {f, g, h};
		}

		int m = (a * n + b) / c;
		if(!m) return {0, 0, 0};

		Data t = calc(m - 1, c, c - b - 1, a);
		int N = n % mod, M = m % mod;
		int s1 = N * ((N + 1) % mod) % mod * inv2 % mod;

		int f = (N * M % mod - t.f) % mod;
		int g = (N * M % mod * M % mod - 2 * t.h - t.f) % mod;
		int h = (M * s1 % mod - (t.g + t.f) % mod * inv2) % mod;
		if(f < 0) f += mod;
		if(g < 0) g += mod;
		if(h < 0) h += mod;
		return {f, g, h};
	}
}

auto [f, g, h] = Euclid::calc(n, a, b, c);

f // sum floor((ai+b)/c)
g // sum floor((ai+b)/c)^2
h // sum i*floor((ai+b)/c)