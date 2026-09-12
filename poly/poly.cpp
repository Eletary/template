// @title DIF-DIT NTT & All op
// @brief 效率较高的 NTT
// @complexity 除『』外，均为 O(nlogn)
// @author ppip

using LL=long long;
#define ensure(x) do { \
    if (!(x)) { \
        fprintf(stderr,"ensure failed: %s, line %d\n",#x,__LINE__); \
        exit(1); \
    } \
} while(0)
struct poly {
    static const int mod=998244353;
    vector<LL>a;
    static vector<LL>w;

    poly(){}
    poly(int n):a(n){}
    poly(vector<LL> v):a(move(v)){}
    poly(initializer_list<LL> v):a(v){}

    int size()const{return a.size();}
    LL& operator[](int i){return a[i];}
    const LL& operator[](int i)const{return a[i];}
    void resize(int n){a.resize(n);}

    static LL qp(LL a,LL n=mod-2){
        LL r=1;
        for(;n;n>>=1,a=a*a%mod)if(n&1)r=r*a%mod;
        return r;
    }

    static int up(int n){
        return n<=1?1:1<<(__lg(n-1)+1);
    }

    static void init(int n){
        ensure(n>0&&!(n&(n-1))&&n<=(1<<23));
        int m=n>>1,k=w.size();
        if(k>=m)return;
        w.resize(m);
        for(;k<m;k<<=1){
            LL r=qp(31,1<<(21-__lg(k)));
            for(int i=0;i<k;i++)w[k+i]=w[i]*r%mod;
        }
    }

    static void dif(vector<LL>&a){
        int n=a.size();
        init(n);
        for(int len=n>>1;len;len>>=1){
            int o=0;
            for(int l=0;l<n;l+=len<<1,++o){
                LL r=w[o];
                for(int i=l;i<l+len;i++){
                    LL x=a[i],y=r*a[i+len]%mod;
                    a[i]=x+y;
                    if(a[i]>=mod)a[i]-=mod;
                    a[i+len]=x-y;
                    if(a[i+len]<0)a[i+len]+=mod;
                }
            }
        }
    }

    static void dit(vector<LL>&a){
        int n=a.size();
        init(n);
        for(int len=1;len<n;len<<=1){
            int o=0;
            for(int l=0;l<n;l+=len<<1,++o){
                LL r=w[o];
                for(int i=l;i<l+len;i++){
                    LL x=a[i],y=a[i+len];
                    a[i]=x+y;
                    if(a[i]>=mod)a[i]-=mod;
                    a[i+len]=(x-y+mod)*r%mod;
                }
            }
        }
    }

    vector<LL> val(int n=0)const{
        if(!n)n=up(size());
        vector<LL>f(n);
        copy_n(a.begin(),min(n,size()),f.begin());
        dif(f);
        return f;
    }

    static poly from(vector<LL>f){
        if(f.empty())return {};
        int n=f.size();
        dit(f);
        reverse(f.begin()+1,f.end());
        LL iv=mod-(mod-1)/n;
        for(LL&x:f)x=x*iv%mod;
        return poly(move(f));
    }

    friend poly operator*(const poly&A,const poly&B){
        if(!A.size()||!B.size())return {};
        int s=A.size()+B.size()-1;
        if(min(A.size(),B.size())<=32){
            poly c(s);
            for(int i=0;i<A.size();i++)for(int j=0;j<B.size();j++)
                c[i+j]=(c[i+j]+A[i]*B[j])%mod;
            return c;
        }
        int n=up(s);
        auto a=A.val(n);
        if(&A==&B){
            for(LL&x:a)x=x*x%mod;
        }else{
            auto b=B.val(n);
            for(int i=0;i<n;i++)a[i]=a[i]*b[i]%mod;
        }
        poly c=from(move(a));
        c.resize(s);
        return c;
    }

	friend poly operator+(poly A,const poly&B){
		if(A.size()<B.size()) A.resize(B.size());
		for(int i=0;i<B.size();++i){
			A[i]+=B[i];
			if(A[i]>=mod) A[i]-=mod;
		}
		return A;
	}
	friend poly operator-(poly A,const poly&B){
		if(A.size()<B.size()) A.resize(B.size());
		for(int i=0;i<B.size();++i){
			A[i]-=B[i];
			if(A[i]<0) A[i]+=mod;
		}
		return A;
	}

	poly& operator+=(const poly&b){
		return *this=*this+b;
	}
	poly& operator-=(const poly&b){
		return *this=*this-b;
	}
	poly& operator*=(const poly&b){
		return *this=*this*b;
	}

	friend poly inv(const poly &f,int n=-1) {
        ensure(f.size() && f[0]);
		if (n==-1) n=(f.size()-1);
		poly F{f[0]},G{qp(F[0])};
		for (int i{2};(i>>1)<=n;i<<=1) {
			// FG=1+E
			// G1=G(1-E)=G(1-(FG-1))=G(2-FG)
			F.resize(i);
			for (int j{i/2};j<i&&j<=n;++j) F[j]=f[j];
			G=G*(poly{2}-F*G);
			G.resize(i);
		}
		G.resize(n+1);
		return G;
	}
	friend poly dev(const poly &f) {
		if (f.size()<=1) return poly{0};
		poly g(f.size()-1);
		for (int i=1;i<f.size();++i)
			g[i-1]=f[i]*i%mod;
		return g;
	}
	friend poly inte(const poly &f) {
		poly g(f.size()+1);
		g[0]=0;
		vector<LL> iv(f.size()+1);
		if (f.size()) iv[1]=1;
		for (int i=2;i<=f.size();++i)
			iv[i]=mod-mod/i*iv[mod%i]%mod;
		for (int i=0;i<f.size();++i)
			g[i+1]=f[i]*iv[i+1]%mod;
		return g;
	}
	friend poly ln(const poly &f,int n=-1) {
		ensure(f[0]==1);
		// G'=(lnF)'=F'/F
		// G=int(F'*F^-1)
		if (n==-1) n=f.size();
		auto g{inte(dev(f)*inv(f))};
		g.resize(n);
		return g;
	}
};
vector<LL> poly::w{1};