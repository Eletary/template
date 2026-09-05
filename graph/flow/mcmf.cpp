// @title 最小费用最大流
// @brief 
// @complexity O(nmF)
// @author yzj
namespace MCMF {
        const int MAXN = 1e6 + 5, inf = 1e18;
        int s, t, mxfl, mico;
        int inq[MAXN], d[MAXN], pr[MAXN];
        int hd[MAXN], cur[MAXN], to[MAXN << 1], ne[MAXN << 1], e[MAXN << 1], c[MAXN << 1], tc = 1;

        inline void add (int x, int y, int z, int w) {
                // cerr << x << " " << y << " " << z << " " << w << endl;
                to[++ tc] = y; ne[tc] = hd[x]; hd[x] = tc; e[tc] = z; c[tc] = w;
                to[++ tc] = x; ne[tc] = hd[y]; hd[y] = tc; e[tc] = 0; c[tc] = - w;
        }

        inline int spfa () {
                rep (i, 0, t) inq[i] = pr[i] = 0, d[i] = inf; 
                queue <int> Q; Q.push (s); d[s] = 0; inq[s] = 1;
                while (!Q.empty ()) {
                        int x = Q.front (); Q.pop (); inq[x] = 0; cur[x] = hd[x];
                        for (int i = hd[x], y; i; i = ne[i])
                                if (e[i] && d[y = to[i]] > d[x] + c[i]) {
                                        d[y] = d[x] + c[i]; pr[y] = i;
                                        if (!inq[y]) Q.push (y), inq[y] = 1;
                                }
                }
                return d[t] != inf;
        }

        inline pii mcmf() {
		pii res = mkp(0, 0); 
		while(spfa ()) {
			int c = inf;
			for(int x = t; x != s; x = to[pr[x] ^ 1]) c = min(c, e[pr[x]]);
			for(int x = t; x != s; x = to[pr[x] ^ 1]) e[pr[x]] -= c, e[pr[x] ^ 1] += c;
			res.first += c; res.second += d[t] * c;
		}
		return res;
	}
} 