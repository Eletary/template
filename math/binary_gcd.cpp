// @title Binary GCD
// @brief 超快 gcd 算法
// @complexity O(log n)，可以当作 O(1)
// @author ppip

#define ctz __builtin_ctz
inline int gcd(int a,int b) {
    int az{ctz(a)},bz{ctz(b)},z{min(az,bz)},t;b>>=bz;
    while (a) a>>=az,t=a-b,az=ctz(t),b=min(a,b),a=abs(t);
    return b<<z;
}