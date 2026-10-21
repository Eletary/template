// @title 最大流
// @brief 网络最大流
// @complexity O(nm^2), 二分图中 O (m \sqrt n)
// @author ysy
#include<iostream>
#include<cstdio>
#include<queue>
#define int long long
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=220,M=10010,inf=1e18;
int n,m,s,t,fr[N],nex[M],to[M],v[M],ct=1,nw[N],dep[N],ans;
queue<int>q;
void add(int x,int y,int z){
	nex[++ct]=fr[x];
	to[ct]=y;
	v[ct]=z;
	fr[x]=ct;
}
void lnk(int x,int y,int z){
	add(x,y,z);add(y,x,0);
}
bool bfs(){
	for(int i=1;i<=n;i++){
		dep[i]=0,nw[i]=fr[i];
	}
	q.push(s);dep[s]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=fr[x];i;i=nex[i]){
			int y=to[i];
			if(v[i]&&!dep[y]){
				dep[y]=dep[x]+1;
				q.push(y);
			}
		}
	}
	return dep[t];
}
int dfs(int x,int fl){
	if(x==t)return fl;
	int res=0;
	for(int i=nw[x];i&&fl;i=nex[i]){
		nw[x]=i;int y=to[i];
		if(v[i]&&dep[y]==dep[x]+1){
			int z=dfs(y,min(v[i],fl));
			fl-=z;res+=z;
			v[i]-=z;v[i^1]+=z;
		}
	}
	if(!res)dep[x]=0;
	return res;
}
signed main(){
	n=read(),m=read(),s=read(),t=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		lnk(u,v,w);
	}
	while(bfs())ans+=dfs(s,inf);
	cout<<ans;
	return 0;
}
