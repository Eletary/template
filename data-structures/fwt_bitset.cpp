// @title 01 树状数组
// @brief 下标从 1 开始，激活位置并查询区间内已激活位置数
// @complexity Add/query O(log(N/64)), in-block query O(1)
// @author ppip

struct fwt {
	static constexpr int B{(N>>6)+5};
	int t[B],n;
	unsigned long long b[B];
	void clear() {
		n=(::n>>6)+1;
		fill_n(t,n+1,0);
		fill_n(b,n+1,0);
	}
	int px(int x) {
		int y{x&63},z{x>>6};
		return __builtin_popcountll(b[z]&(~0ull>>(63-y)));
	}
	int qry(int l,int r) {
		--l;
		int ans{px(r)-px(l)};
		l>>=6;r>>=6;
		while (r>l) ans+=t[r],r&=r-1;
		while (l>r) ans-=t[l],l&=l-1;
		return ans;
	}
	void add(int x) {
		unsigned long long w{1ull<<(x&63)};
		if (b[x>>6]&w) return;
		b[x>>6]|=w;
		x=(x>>6)+1;
		while (x<=n) {
			++t[x];
			x+=x&-x;
		}
	}
	int qry(int x) {
		int ans{px(x)};
		x>>=6;
		while (x) {
			ans+=t[x];
			x&=x-1;
		}
		return ans;
	}
} t;
