// @title O(1) 查询树状数组
// @brief 下标从 1 开始，单点加、查询后缀和；适合查询远多于修改
// @complexity Query O(1), add O(128+N/4096)
// @author ppip

struct FWT {
	int s1[N+5],s2[(N>>6)+5],s3[(N>>12)+5];
	void init() {
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		memset(s3,0,sizeof(s3));
	}
	void add(int x,int y) {
		for (int i{(x>>6)<<6};i<=x;++i) s1[i]+=y;
		for (int i{(x>>12)<<6};i<(x>>6);++i) s2[i]+=y;
		for (int i{0};i<(x>>12);++i) s3[i]+=y;
	}
	int qry(int x) {
		return s1[x]+s2[x>>6]+s3[x>>12];
	}
} T;
