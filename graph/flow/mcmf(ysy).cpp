// @title 最小费用最大流
// @brief 最小费用最大流，原始对偶实现
// @complexity /yun
// @author ysy
#include<iostream>
#include<cstdio>
#include<queue>
#define M(x,y) make_pair(x,y)
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=100010,inf=1e9+7;
int n,m,s,t,fr[N],nex[N],to[N],fl[N],vl[N],ct=1;
int h[N],d[N],b[N],bl[N],eg[N],cnt,res;
queue<int>Q;
priority_queue<pair<int,int> >q;
void add(int x,int y,int z,int f){
    nex[++ct]=fr[x];
    to[ct]=y;
    vl[ct]=z;
    fl[ct]=f;
    fr[x]=ct;
}
void lnk(int x,int y,int z,int f){
    add(x,y,z,f);add(y,x,-z,0);
}
void spfa(){
    for(int i=1;i<=n;i++){
        h[i]=inf;
    }
    h[s]=0;Q.push(s);b[s]=1;
    while(!Q.empty()){
        int x=Q.front();Q.pop();
        b[x]=0;
        for(int i=fr[x];i;i=nex[i]){
            if(!fl[i])continue;
            int y=to[i];
            if(h[y]>h[x]+vl[i]){
                h[y]=h[x]+vl[i];
                if(!b[y]){
                    Q.push(y);
                    b[y]=1;
                }
            }
        }
    }
}
bool dij(){
    for(int i=1;i<=n;i++){
        d[i]=inf;b[i]=0;
    }
    d[s]=0;q.push(M(0,s));
    while(!q.empty()){
        int x=q.top().second;q.pop();
        if(b[x])continue;
        b[x]=1;
        for(int i=fr[x];i;i=nex[i]){
            if(!fl[i])continue;
            int y=to[i],z=vl[i]-(h[y]-h[x]);
            if(d[y]>d[x]+z){
                d[y]=d[x]+z;
                bl[y]=x,eg[y]=i;
                q.push(M(-d[y],y));
            }
        }
    }
    return(d[t]!=inf);
}
int main(){
    n=read(),m=read(),s=read(),t=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read(),w=read(),c=read();
        lnk(u,v,c,w);
    }
    spfa();
    while(dij()){
        for(int i=1;i<=n;i++){
            h[i]+=d[i];
        }
        int x=t,mn=inf,cs=0;
        while(x!=s){
            mn=min(mn,fl[eg[x]]);
            x=bl[x];
        }
        x=t;
        while(x!=s){
            cs+=vl[eg[x]]*mn;
            fl[eg[x]]-=mn;fl[eg[x]^1]+=mn;
            x=bl[x];
        }
        cnt+=mn,res+=cs;
    }
    cout<<cnt<<" "<<res<<"\n";
    return 0;
}
