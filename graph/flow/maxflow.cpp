// @title 最大流
// @brief Dinic, 要求汇点编号为最大值
// @complexity 相信的心就是魔法
// @author ppip

struct edge {
    int u,v,w,nxt;
    edge(int _,int __,int ___,int ____):
        u{_},v{__},w{___},nxt{____} {}
    edge() {}
};
vector<edge> e(2);
int hd[N+5];
void _add(int u,int v,int w) {
    e.emplace_back(u,v,w,hd[u]);
    hd[u]=e.size()-1;
}
void add(int u,int v,int w) {
    _add(u,v,w);
    _add(v,u,0);
}
int q[N+5];
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
    for (int &x{cur[s]},d;x;x=e[x].nxt) {
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
    fill_n(dep+1,t,0);
    long long flow{0};
    while (bfs(s,t)) {
        copy(hd+1,hd+t+1,cur+1);
        flow+=dfs(s,t,LLONG_MAX);
        fill_n(dep+1,t,0);
    }
    return flow;
}
void clear(int t) {
    e.resize(2);
    fill_n(hd+1,t,0);
}