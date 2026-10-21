// @title LCT
// @brief LCT
// @complexity O(nlogn)
// @author ysy

#include<iostream>
#include<cstdio>
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=100010;
int n,q,fa[N],ch[N][2],rv[N],v[N],yh[N];
bool nrt(int x){return(ch[fa[x]][0]==x||ch[fa[x]][1]==x);}
void pup(int x){
    yh[x]=(yh[ch[x][0]]^yh[ch[x][1]]^v[x]);
}
void rnt(int x){
    int y=fa[x],z=fa[y],k=(ch[y][1]==x),w=ch[x][k^1];
    if(nrt(y))ch[z][ch[z][1]==y]=x;
    fa[fa[fa[ch[ch[x][k^1]=y][k]=w]=y]=x]=z;
    pup(y);pup(x);
}
void pd(int x){
    swap(ch[x][0],ch[x][1]);
    rv[x]^=1;
}
void psd(int x){
    if(rv[x]){
        pd(ch[x][0]);
        pd(ch[x][1]);
        rv[x]=0;
    }
}
int s[N],tt;
void psc(int x){
    s[++tt]=x;
    for(;nrt(x);x=fa[x])s[++tt]=fa[x];
    while(tt)psd(s[tt--]);
}
void spl(int x){
    psc(x);
    while(nrt(x)){
        int y=fa[x],z=fa[y];
        if(nrt(y))rnt((ch[z][1]==y)^(ch[y][1]==x)?x:y);
        rnt(x);
    }
}
void acs(int x){
    int y=0;
    while(x){
        spl(x);
        ch[x][1]=y;
        pup(x);
        y=x;x=fa[x];
    }
}
void mrt(int x){
    acs(x);
    spl(x);
    pd(x);
}
int grt(int x){
    acs(x);
    spl(x);
    while(ch[x][0])x=ch[x][0];
    spl(x);
    return x;
}
bool chk(int x,int y){
    mrt(x);
    return(grt(y)==x);
}
void lnk(int x,int y){
    if(chk(x,y))return;
    fa[x]=y;
}
void cut(int x,int y){
    if(!chk(x,y)||ch[x][1]!=y||ch[y][0])return;
    ch[x][1]=fa[y]=0;pup(x);
}
void qry(int x,int y){
    if(!chk(x,y))cout<<"?\n";
    cout<<yh[x]<<"\n";
}
void upd(int x,int y){
    spl(x);
    v[x]=y;
    pup(x);
}
int main(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		v[i]=read();
	}
    while(q--){
        int op=read(),x=read(),y=read();
        if(op==0)qry(x,y);
        if(op==1)lnk(x,y);
        if(op==2)cut(x,y);
        if(op==3)upd(x,y);
    }
	return 0;
}
