// @title 多项式求逆
// @brief ntt,多项式求逆
// @complexity O(nlogn)
// @author ysy

#include<iostream>
#include<cstdio>
#include<cstring>
#define int long long 
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int N=4000010,mod=998244353,g=3;
int ksm(int p,int k){
	int x=1;
	while(k){
		if(k&1)x=x*p%mod;
		p=p*p%mod;
		k>>=1;
	}
	return x;
}
int r[N];
void init(int lg){
	for(int i=0;i<(1<<lg);i++){
		r[i]=(r[i>>1]>>1)|((i&1)<<(lg-1));
	}
}
void ntt(int *a,int n,bool f=0){
	for(int i=0;i<n;i++){
		if(i<r[i])swap(a[i],a[r[i]]);
	}
	for(int ln=2;ln<=n;ln<<=1){
		int x=ksm(g,(mod-1)/ln),mid=(ln>>1);
		if(f)x=ksm(x,mod-2);
		for(int i=0;i<n;i+=ln){
			int y=1;
			for(int j=0;j<mid;j++){
				int l=a[i+j],r=y*a[i+j+mid]%mod;
				a[i+j]=(l+r)%mod,a[i+j+mid]=(l-r+mod)%mod;
				y=y*x%mod;
			}
		}
	}
	if(f){
		int iv=ksm(n,mod-2);
		for(int i=0;i<n;i++){
			a[i]=a[i]*iv%mod;
		}
	}
}
void mul(int *a,int *b,int n){
	static int c[N],d[N];
	memset(c,0,sizeof(c));
	memset(d,0,sizeof(d));
	int m=(n<<1);
	for(int i=0;i<n;i++){
		c[i]=a[i],d[i]=b[i];
	}
	ntt(c,m,0);ntt(d,m,0);
	for(int i=0;i<m;i++){
		a[i]=c[i]*d[i]%mod;
	}
	ntt(a,m,1);
}
void qinv(int n,int *g){
	int m=1,lg=0;
	static int f[N],h[N];
	memcpy(f,g,sizeof(f));
	memset(g,0,sizeof(g)); 
	g[0]=ksm(f[0],mod-2);
	while(m<=n){
		m<<=1,lg++;
		init(lg+1);
		memcpy(h,g,sizeof(h));
		memset(g,0,sizeof(g));
		for(int i=0;i<m;i++){
			g[i]=h[i]*2%mod;
		}
		mul(h,h,m);
		mul(h,f,m);
		for(int i=0;i<m;i++){
			g[i]=(g[i]-h[i]+mod)%mod;
		}
	}
}
int n,a[N],b[N];
signed main(){
	n=read()-1;
	for(int i=0;i<=n;i++){
		a[i]=read();
	}
	qinv(n,a);
	for(int i=0;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
