// @title 后缀树
// @brief Ukkonen 在线构造隐式后缀树
// @complexity build O(n) 
// @author ppip

constexpr int N(1e6),inf(1e7),RNG{26+26+10};
struct Suft {
	int ch[N*2+5][RNG];
	int st[N*2+5],len[N*2+5],link[N*2+5];
	char s[N+5];
	int now{1},rem{0},n{0},tot{1};
	Suft() {len[0]=inf;}
	int new_node(int l,int le) {
		++tot;st[tot]=l;len[tot]=le;
		return tot;
	}
	void extend(int x) {
		s[++n]=x;++rem;
		for (int lst{1};rem;) {
			while (rem>len[ch[now][s[n-rem+1]]])
				rem-=len[now=ch[now][s[n-rem+1]]];
			int &v{ch[now][s[n-rem+1]]},c{s[st[v]+rem-1]};
			if (!v||x==c) {
				link[lst]=now;lst=now;
				if (!v) v=new_node(n,inf);
				else break;
			} else {
				int u{new_node(st[v],rem-1)};
				ch[u][c]=v;ch[u][x]=new_node(n,inf);
				st[v]+=rem-1;len[v]-=rem-1;
				link[lst]=v=u;lst=u;
			}
			if (now==1) --rem;
			else now=link[now];
		}
	}
	void search(int u,int dep=0) {
		if (st[u]+len[u]-1>=n&&st[u]-dep!=n) cout<<st[u]-dep<<" ";
		else dep+=len[u];
		for (int i{0};i<RNG;++i)
			if (ch[u][i]) search(ch[u][i],dep);
	}

} T;