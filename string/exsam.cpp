// @title 广义SAM
// @brief 建立多串SAM
// @complexity O(n*C)
// @author ysy

#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;
int read(){
	int x;
	scanf("%d",&x);
	return x;
}
const int N=2000020;
struct SAM{
	int fa[N],ch[N][26],ln[N],ct=1,la=1;
	void ins(int c){
		int p=la;
		if(ch[p][c]){
			int q=ch[p][c];
			if(ln[q]==ln[p]+1)la=q;
			else{
				int nq=++ct;ln[nq]=ln[p]+1,la=nq;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];fa[q]=nq;
				for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=nq;
			}
			return;
		}
		int np=++ct;ln[np]=ln[p]+1,la=np;
		for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;
		if(!p)fa[np]=1;
		else{
			int q=ch[p][c];
			if(ln[q]==ln[p]+1)fa[np]=q;
			else{
				int nq=++ct;ln[nq]=ln[p]+1;
				memcpy(ch[nq],ch[q],sizeof(ch[q]));
				fa[nq]=fa[q];fa[q]=fa[np]=nq;
				for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=nq;
			}
		}
	}
	ll calc(){
		ll ans=0;
		for(int i=2;i<=ct;i++){
			ans+=ln[i]-ln[fa[i]];
		}
		return ans;
	}
}sa;
int n,m;
char c[N];
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",c+1);
		m=strlen(c+1),sa.la=1;
		for(int j=1;j<=m;j++){
			sa.ins(c[j]-'a');
		}
	}
	cout<<sa.calc()<<"\n"<<sa.ct;
	return 0;
}
