// @title SA
// @brief 后缀排序并求出 height 数组
// @complexity O(n \log n)
// @author yzj
namespace SA {
	int sa[N], rk[N], tmp[N], id[N], buc[N], height[N], idx;
	inline void suffix_sort() {
		for(int i = 0; i < 256; i++) buc[i] = 0;
		for(int i = 1; i <= n; i++) buc[(unsigned char)str[i]]++;
		for(int i = 1; i < 256; i++) buc[i] += buc[i - 1];
		for(int i = n; i; i--) sa[buc[(unsigned char)str[i]]--] = i;
		rk[sa[1]] = idx = 1;
		for(int i = 2; i <= n; i++)
			rk[sa[i]] = str[sa[i]] == str[sa[i - 1]] ? idx : ++idx;

		for(int w = 1; idx < n; w <<= 1) {
			int p = 0;
			for(int i = n - w + 1; i <= n; i++) id[++p] = i;
			for(int i = 1; i <= n; i++) if(sa[i] > w) id[++p] = sa[i] - w;

			for(int i = 1; i <= idx; i++) buc[i] = 0;
			for(int i = 1; i <= n; i++) buc[rk[id[i]]]++;
			for(int i = 1; i <= idx; i++) buc[i] += buc[i - 1];
			for(int i = n; i; i--) sa[buc[rk[id[i]]]--] = id[i];

			for(int i = 1; i <= n; i++) tmp[i] = rk[i];
			rk[sa[1]] = idx = 1;
			for(int i = 2; i <= n; i++) {
				int x = sa[i], y = sa[i - 1];
				rk[x] = tmp[x] == tmp[y] &&
					(x + w > n ? 0 : tmp[x + w]) == (y + w > n ? 0 : tmp[y + w])
					? idx : ++idx;
			}
		}

		for(int i = 1, k = 0; i <= n; i++) {
			if(rk[i] == 1) { k = 0; continue; }
			if(k) k--;
			int j = sa[rk[i] - 1];
			while(i + k <= n && j + k <= n && str[i + k] == str[j + k]) k++;
			height[rk[i]] = k;
		}
		height[1] = 0;
	}
}