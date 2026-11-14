// @title 杜教筛
// @brief 求欧拉函数与莫比乌斯函数的前缀和
// @complexity O(n^{2/3})
// @author yzj
#include<iostream>
#include<cstdio>
#include<map>
#define ll long long
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=4000040,mod=20101009;
int t,mx=4000000;
int p[N],pri[N],cnt,mo[N],ans;
ll fi[N];
map<int,int>f1;
map<int,ll>f2;
void oula(){
    mo[1]=1,fi[1]=1;
    for(int i=2;i<=mx;i++){
        if(!fi[i]){
            pri[++cnt]=i;
            mo[i]=-1;
            fi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*pri[j]<=mx;j++){
            int p=pri[j];
            fi[i*p]=fi[i]*p;
            if(i%p==0)break;
            fi[i*p]=fi[i]*(p-1);
            mo[i*p]=-mo[i];
        }
    }
    for(int i=1;i<=mx;i++){
        mo[i]+=mo[i-1],fi[i]+=fi[i-1];
    }
}
int sumu(int n){
    if(n<=mx)return mo[n];
    if(f1[n])return f1[n];
    int cnt=1;
    for(ll l=2,r=0;l<=n;l=r+1){
        r=n/(n/l);
        cnt-=(r-l+1)*sumu(n/l);
    }
    return f1[n]=cnt;
}
ll sumf(int n){
    if(n<=mx)return fi[n];
    if(f2[n])return f2[n];
    ll cnt=n*(n+1ll)/2ll;
    for(ll l=2,r=0;l<=n;l=r+1){
        r=n/(n/l);
        cnt-=(r-l+1ll)*sumf(n/l);
    }
    return f2[n]=cnt;
}
signed main(){
    oula();
    t=read();
    while(t--){
        int n=read();
        cout<<sumf(n)<<" "<<sumu(n)<<"\n";
    }
}
