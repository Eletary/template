// @title Geometry basic
// @brief 凸包，检查一个点是否在凸包内，闵可夫斯基和
// @complexity 
// @author yzj
namespace Geometry {
	const db eps = 1e-5;
	struct Vector {
		ll x,y;
		Vector operator+(const Vector &A) { return Vector{x+A.x,y+A.y}; }
		Vector operator-(const Vector &A) { return Vector{x-A.x,y-A.y}; }
		Vector operator*(const Vector &A) { return Vector{x*A.x,y*A.y}; }
		bool operator== (const Vector &A) { return x==A.x && y==A.y; }
		inline ll square() { return x*x+y*y; }
		inline db dis() { return sqrt((db)(x*x+y*y)); }
		inline int section() {
			if(x>0 && y>=0) return 1;
			else if(x<=0 && y>0) return 2;
			else if(x<0 && y<=0) return 3;
			else return 4;
		}
		inline void in() { x = read(); y = read(); }
	};
	const Vector zero = {0,0};
	vc<Vector> as;
	
	inline ll crs(Vector A,Vector B) { return A.x*B.y-A.y*B.x; }
	inline bool right(Vector A,Vector B) { return crs(A,B)<0; }
	inline bool left (Vector A,Vector B) { return crs(A,B)>0; }
	inline bool cmp1(Vector A,Vector B) { return A.y==B.y?A.x<B.x:A.y<B.y; }
	inline bool cmpangle(Vector A,Vector B) { return A.section()==B.section()?left(A,B):A.section()<B.section(); }
	inline bool inseg(Vector A,Vector B,Vector C) { 
		return fabs((C-A).dis()+(C-B).dis()-(B-A).dis())<eps;
	}
	
	inline vc<Vector> ConvexHull(vc<Vector> a) {
		sort(a.begin(),a.end(),cmp1);
		vc<Vector> b, c, o; int l=0;
		for(auto u:a) { while(b.size()>1 && right(b[l-1]-b[l-2],u-b[l-1])) b.pop_back(), --l; b.pb(u); ++l; }
		l=0; reverse(a.begin(),a.end());
		for(auto u:a) { while(c.size()>1 && right(c[l-1]-c[l-2],u-c[l-1])) c.pop_back(), --l; c.pb(u); ++l;}
		o=b; for(int i=1;i<l-1;i++) o.pb(c[i]);
		return o;
	} 
	
	inline vc<Vector> Minkowski(vc<Vector> A,vc<Vector> B) {
		if(!A.size()) return A; if(!B.size()) return B;
		vc<Vector> C; Vector s = A[0]+B[0];
		for(int i=0;i<A.size();i++) C.pb(A[(i+1)%A.size()]-A[i]);
		for(int i=0;i<B.size();i++) C.pb(B[(i+1)%B.size()]-B[i]);
		sort(C.begin(),C.end(),cmpangle); 
		vc<Vector> res; Vector sum = s; res.pb(s);
		for(auto u:C) sum = sum+u, res.pb(sum);
		return res.pop_back(), res;
	}
	
	inline bool in(Vector x) { // ask whether x is in ConvexHull as
		if(as.size()==0) return 0;
		if(as.size()==1) return as[0]==x;
		if(as.size()==2)  return !crs(as[l-1]-as[0],x-as[0]) && inseg(as[l-1],as[0],x);
		int l = as.size();
		if(left(as[l-1]-as[0],x-as[0])) return 0;
		int le = 1, ri = l-2, mid, cnt=0;
		while(le <= ri) {
			++cnt;
			mid = le+ri>>1;
			if(!right(as[mid]-as[0],x-as[0])) le = mid+1;
			else ri = mid-1;
		}
		return !right(as[ri+1]-as[ri],x-as[ri]);
	}
}