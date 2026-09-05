// @title PAM
// @brief 回文树
// @complexity O(n)
// @author yzj
namespace PAM {
	int ch[N][26], fail[N], len[N], cnt[N], last, tot;
	inline int getfail(int p, int x) {
		while(str[x - len[p] - 1] != str[x]) p = fail[p];
		return p;
	}
	inline void insert(int x) {
		int c = str[x] - 'a', p = getfail(last, x);
		if(!ch[p][c]) {
			len[++tot] = len[p] + 2;
			if(len[tot] == 1) fail[tot] = 0;
			else {
				int q = getfail(fail[p], x);
				fail[tot] = ch[q][c];
			}
			ch[p][c] = tot;
		}
		last = ch[p][c]; cnt[last]++;
	}
	inline void build() {
		len[0] = 0; fail[0] = 1;
		len[1] = -1; fail[1] = 1;
		last = 0; tot = 1;
		for(int i = 1; i <= n; i++) insert(i);
		for(int i = tot; i > 1; i--) cnt[fail[i]] += cnt[i];
	}
}