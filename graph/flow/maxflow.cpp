// @title 最大流
// @brief Dinic
// @complexity 相信的心就是魔法
// @author ppip

struct edge {
    int u,v,w,nxt;
    edge(int _,int __,int ___,int ____):
        u{_},v{__},w{___},nxt{____} {}
};
vector<edge> e;
int hd[N+5],ne{1};
void _add(int u,int v,int w) {
    ++ne;
    e[ne]={u,v,w,hd[u]};
    hd[u]=ne;
}
void add(int u,int v,int w) {
    _add(u,v,w);
    _add(v,u,0);
}
int q[N+5],dis[N+5],pre[N+5];
int dep[N+5],cur[N+5];
bool bfs(int s,int t) {
    dep[s]=1;
    int l{0},r{0};
    q[r++]=s;
    while (r-l) {
        int u{q[l++]};
        for (int x{hd[u]};x;x=e[x].nxt)
            if (!dep[e[x].v]&&e[x].w) {
                dep[e[x].v]=dep[u]+1;
                q[r++]=e[x].v;
            }
    }
    return dep[t];
}
long long dfs(int s,int t,long long flow) {
    if (s==t||!flow) return flow;
    long long ans{0};
    for (int x{cur[s]},d;x;x=e[x].nxt) {
        cur[s]=x;
        if (dep[e[x].v]==dep[s]+1&&e[x].w&&(d=dfs(e[x].v,t,min(flow,(long long)e[x].w)))) {
            flow-=d;
            ans+=d;
            e[x].w-=d;
            e[x^1].w+=d;
            if (!flow) return ans;
        }
    }
    return ans;
}
long long calc(int s,int t) {
    long long flow{0};
    while (bfs(s,t)) {
        copy(hd+1,hd+t+1,cur+1);
        flow+=dfs(s,t,LLONG_MAX);
        fill_n(dep+1,t,0);
    }
    return flow;
}