// @title min25
// @brief 
// @complexity O(n^{3/4} / \log n)
// @author yzj
namespace min25 {
	int pri[N], cov[N], sq, m;
	int id1[N], id2[N], val[N], idx;
	mint f[N], g[N], h[N];
	map <pii, mint> dps;
	
	inline int id (int x) { return x <= sq ? id1[x] : id2[n / x]; }
	
	inline void init (int n) {
		sq = sqrt (n); m = idx = 0;
		
		rep (i, 2, sq) {
			if (!cov[i]) pri[++ m] = i, h[m] = h[m - 1] + i;
			for (int j = 1; j <= m && i * pri[j] <= sq; j ++) {
				cov[i * pri[j]] = 1;
				if (i % pri[j] == 0) break;
			}
		}
		
		for (int l = 1, r, v; l <= n; l = r + 1) {
			val[++ idx] = v = n / l; r = n / v; 
			(v <= sq ? id1[v] : id2[n / v]) = idx;
			f[idx] = (mint) v * (v + 1) * inv2 - 1; g[idx] = v - 1;
		}
		
		rep (j, 1, m) for (int i = 1; i <= idx && pri[j] * pri[j] <= val[i]; i ++) {
			int k = id (val[i] / pri[j]);
			f[i] -= pri[j] * (f[k] - h[j - 1]);
			g[i] -= g[k] - j + 1;
		}
	}
	
	int TIME = 0;
	inline mint S (int n, int i) {
		if (n <= 1 || pri[i] >= n) return 0;
		
		int u = id (n);
		mint res = f[u] - g[u] - h[i] + i;
		if (i == 0) res += 2;
		
		for (int j = i + 1; j <= m && pri[j] * pri[j] <= n; j ++) {
			for (int c = 1, pw = pri[j]; pw <= n; pw *= pri[j], c ++)
				res += (pri[j] ^ c) * (S (n / pw, j) + (c > 1));
		}
		
		return res;
	}
} 