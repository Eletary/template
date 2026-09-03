// @title Top Tree
// @brief Magic tree that can fulfill every wish.
// @complexity Tree height O(log n)
// @author ppip

vector<pair<int,int>> e[N+5];
int sz[N+5],fa[N+5],son[N+5];
void TOPTREE_INIT(int u) {
	sz[u]=1;
	for (auto [v,_]:e[u])
		if (v!=fa[u]) {
			TOPTREE_INIT(v);
			sz[u]+=sz[v];
			if (sz[v]>sz[son[u]]) son[u]=v;
		}
	if (son[u]) {
		int si{exchange(sz[son[u]],0)};
		sort(e[u].begin(),e[u].end(),[](auto x,auto y){return sz[x.first]<sz[y.first];});
		sz[son[u]]=si;
	}
}
struct cluster {
    //....
} t[N*2+5];
int cnode;
using P=pair<int,int>;
using iter=vector<P>::iterator;
int merge(iter L,iter R,char tp) {
	if (L+1==R) {
		int z{L->first};
		if (z<=n) t[z].u=fa[z],t[z].v=z;
		return z;
	}
	iter p{L+1};
	int sum{accumulate(p,R,-L->second,[](int x,P y){return x+y.second;})};
	while (p+1!=R&&sum>p->second) {
		sum-=p->second*2;
		++p;
	}
	int u{++cnode};
	t[u].t=tp;
	t[u].l=merge(L,p,tp);
	t[u].r=merge(p,R,tp);
	t[t[u].l].f=t[t[u].r].f=u;
	t[u].u=t[t[u].l].u;
	t[u].v=(tp=='C'?t[t[u].r].v:t[t[u].l].v);
	return u;
}
int build(int u) {
	vector<P> v1;v1.emplace_back(u,1);
	while (son[u]) {
		vector<P> v2;v2.emplace_back(son[u],1);
		for (auto [v,_]:e[u])
			if (v!=fa[u]&&v!=son[u]) v2.emplace_back(build(v),sz[v]);
		v1.emplace_back(merge(v2.begin(),v2.end(),'R'),sz[u]-sz[son[u]]);
		u=son[u];
	}
	return merge(v1.begin(),v1.end(),'C');
}
int main() {
	cnode=n;
	TOPTREE_INIT(1);
	int rt{build(1)};
	return 0;
}