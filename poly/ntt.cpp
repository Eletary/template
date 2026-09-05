// @title 多项式乘法
// @brief ntt,未经任何优化
// @complexity O(nlogn)
// @author ysy

#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N=4000040,mod=998244353,g=3;
int n,m,a[N],b[N],r[N];
int ksm(int p,int k){
	int x=1;
	while(k){
		if(k&1)x=x*p%mod;
		p=p*p%mod;
		k>>=1;
	}
	return x;
}
void init(int lg){
    for(int i=1;i<(1<<lg);i++){
        r[i]=((r[i>>1]>>1)|((i&1)<<(lg-1)));
    }
}
void ntt(int *a,int lg,int fl=0){
    int n=(1<<lg);
    for(int i=0;i<n;i++){
        if(i<r[i])swap(a[i],a[r[i]]);
    }
    for(int ln=2;ln<=n;ln<<=1){
        int mid=(ln>>1),x=ksm(g,(mod-1)/ln);
        if(fl)x=ksm(x,mod-2);
        for(int i=0;i<n;i+=ln){
            int y=1;
            for(int j=0;j<mid;j++){
                int l=a[i+j],r=a[i+j+mid]*y%mod;
                a[i+j]=(l+r)%mod,a[i+j+mid]=(l-r+mod)%mod;
                y=y*x%mod;
            }
        }
    }
    if(fl){
        int iv=ksm(n,mod-2);
        for(int i=0;i<n;i++){
            a[i]=a[i]*iv%mod;
        }
    }
}
void mul(){
    int lg=__lg(n+m)+1;
    init(lg);
    ntt(a,lg);ntt(b,lg);
    for(int i=0;i<(1<<lg);i++){
        a[i]=a[i]*b[i]%mod;
    }
    ntt(a,lg,1);
}
signed main(){
    n=read(),m=read();
    for(int i=0;i<=n;i++){
        a[i]=read();
    }
    for(int i=0;i<=m;i++){
        b[i]=read();
    }
    mul();
    for(int i=0;i<=n+m;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
