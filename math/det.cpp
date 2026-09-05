// @title det
// @brief 行列式求值
// @complexity O(n^3)
// @author yzj
inline mint det (vc <vc <mint> > a, int n) {	
	int rev = 0;
	rep (i, 1, n) {
		rep (j, i + 1, n) {
			while (a[i][i].x) {
				int d = a[j][i].x / a[i][i].x;
				rep (k, i, n) a[j][k] -= a[i][k] * d;
				swap (a[i], a[j]); rev ^= 1;
			}
			swap (a[i], a[j]); rev ^= 1;
		}
		if (!a[i][i].x) return 0;
	}
	mint res = 1;
	rep (i, 1, n) res *= a[i][i];
	return rev ? MOD - res : res;
}
