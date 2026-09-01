// @title 快速模乘
// @brief 要求 1<=P<2^31 且 a<P；同一 z 多次使用时先 trans，再用 mul_t
// @complexity O(1)
// @author ppip

using u32=unsigned;
using u64=unsigned long long;
using u128=unsigned __int128;
const u32 P=998244353;
inline u64 trans(u64 x) {
	constexpr u64 A=-(u64)P/P+1;
	constexpr u64 q=((u128(-(u64)P%P)<<64)+P-1)/P;
	return x*A+u64((u128)x*q>>64)+1;
}
// t 必须是 trans(z) 的返回值；复用同一 z 时只需计算一次 t
inline u32 mul_t(u32 a,u64 t) {
	return a*t*(u128)P>>64;
}
inline u32 mul(u32 a,u64 z) {
	return mul_t(a,trans(z));
}
