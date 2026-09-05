// @title manacher
// @brief 线性求回文子串数量
// @complexity O (n)
// @author yzj
namespace Manacher {
	int r[N], L, R, res;
	inline int manacher(char *s, int n) {
		res = L = R = 0; 
		rep(i, 1, n) {
			r[i] = i <= R ? min(r[R + L - i], R - i) : 0;
			while(i + r[i] + 1 <= n && i - r[i] - 1 > 0 && s[i + r[i] + 1] == s[i - r[i] - 1]) ++r[i];
			if(i + r[i] > R) L = i - r[i], R = i + r[i];
			res = max(res, r[i] / 2 * 2 + (i % 2 == 0));
		}
		return res;
	}
}