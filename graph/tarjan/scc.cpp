// @title 强连通分量
// @brief Tarjan 缩点，id 为所属强连通分量，w 为点权和
// @complexity O(n+m)
// @author yzj
inline void Tarjan(int x) {
	dfn[x]=low[x]=++idx; sta[++topf]=x; ins[x]=1;
	for(int i=hd[x],y;i;i=ne[i]) 
		if(!dfn[y=to[i]]) Tarjan(y), low[x]=min(low[x],low[y]);
		else if(ins[y]) low[x]=min(low[x],dfn[y]);
	if(dfn[x]==low[x]) {
		++cnt; int z;
		do { z=sta[topf--]; id[z]=cnt; w[cnt]+=a[z]; ins[z]=0; }while(x^z);
	}
}
