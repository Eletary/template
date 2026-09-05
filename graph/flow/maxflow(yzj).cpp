// @title 最大流
// @brief 网络最大流
// @complexity O(nm^2), 二分图中 O (m \sqrt n)
// @author yzj
namespace flow {
	int dep[N], S, T;
	ll maxflow;
	int hd[N], cur[N], to[N << 1], ne[N << 1], e[N << 1], tc = 1;
	inline void add(int x, int y, int z) {
		to[++tc] = y; ne[tc] = hd[x]; hd[x] = tc; e[tc] = z;
		to[++tc] = x; ne[tc] = hd[y]; hd[y] = tc; e[tc] = 0; 
	}
	inline int bfs() {
		rep(i, 0, T) dep[i] = -1; dep[S] = 0; queue<int> Q; Q.push(S);
		while(!Q.empty()) {
			int x = Q.front(); Q.pop(); cur[x] = hd[x];
			if(x == T) return 1;
			for(int i = hd[x], y; i; i = ne[i]) 
				if(e[i] && dep[y = to[i]] == -1) dep[y] = dep[x] + 1, Q.push(y);
		}
		return 0;
	}
	inline int dfs(int x, int fl) {
		if(x == T) return maxflow += fl, fl;
		for(int &i = cur[x], y, o; i; i = ne[i]) 
			if(e[i] && dep[y = to[i]] == dep[x] + 1 && (o = dfs(y, min(fl, e[i]))))
				return e[i] -= o, e[i ^ 1] += o, o;
		return 0;
	}
	inline void dinic() { while(bfs()) { while(dfs(S, inf)); } } 
}