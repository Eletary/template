// @title 后缀数组
// @brief 倍增算法求 sa，rk，height
// @complexity O(n log n)
// @author ppip

char s[N+5];
int id[N+5],sa[N+5],buc[N+5],h[N+5],rk[N+5];
int main() {
    // read s
	int n(strlen(s+1));
	for (int i{1};i<=n;++i) ++buc[s[i]];
	partial_sum(buc+1,buc+1+'~',buc+1);
	for (int i{n};i>=1;--i) sa[buc[s[i]]--]=i;
	int m{0};
	for (int i{1};i<=n;++i) rk[sa[i]]=m+=(s[sa[i]]!=s[sa[i-1]]);
	fill_n(buc+1,'~',0);
	for (int w{1};m<n;w<<=1) {
		int cnt{0};
		for (int i{0};i<w;++i) id[++cnt]=n-i;
		for (int i{1};i<=n;++i) {
			if (sa[i]>w) id[++cnt]=sa[i]-w;
			++buc[rk[i]];
		}
		partial_sum(buc+1,buc+1+m,buc+1);
		for (int i{n};i>=1;--i) sa[buc[rk[id[i]]]--]=id[i];
		fill_n(buc+1,m,0);
		copy_n(rk+1,n,id+1);
		m=0;
		for (int i{1};i<=n;++i) rk[sa[i]]=m+=(id[sa[i]]!=id[sa[i-1]]||id[sa[i]+w]!=id[sa[i-1]+w]);
	}
	// for (int i{1};i<=n;++i) cout<<sa[i]<<" ";
	for (int i{1},k{0};i<=n;++i) {
		k-=!!k;
		while (s[i+k]==s[sa[rk[i]-1]+k]) ++k;
		h[rk[i]]=k;
	}
	return 0;
}