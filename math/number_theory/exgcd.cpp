// @title exgcd
// @brief 
// @complexity O(\log n)
// @author yzj
inline int exgcd(int a, int b, int &x, int &y) {
	if(!b) return x = 1, y = 0, a;
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}
inline int inv(int a, int mod) {
	int x, y;
	exgcd(a, mod, x, y);
	return (x % mod + mod) % mod;
}