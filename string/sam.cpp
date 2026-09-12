// @title SAM
// @brief Magic automaton
// @complexity O(n)
// @author ppip

constexpr int N(1e6),S{26};
struct SAM {
	int cnt,cur,n;
	struct node {
		int len,link;
		array<int,S> ch;
	} t[N*2+5];
	SAM() {cur=cnt=1;fill(t[0].ch.begin(),t[0].ch.end(),1);t[0].len=-1;}
	void extend(int c) {
		++n;
		int x{cur},p{++cnt};
		t[p].len=n;
		while (!t[x].ch[c]) t[x].ch[c]=p,x=t[x].link;
		int q{t[x].ch[c]};
		t[p].link=q;
		if (t[x].len+1!=t[q].len) {
			int nq{++cnt};
			t[nq].ch=t[q].ch;
			t[nq].link=t[q].link;
			t[nq].len=t[x].len+1;

			t[p].link=t[q].link=nq;
			while (t[x].ch[c]==q) t[x].ch[c]=nq,x=t[x].link;
		}
		cur=p;
	}
	void print() {
		return;
		for (int i{1};i<=cnt;++i)
			for (int j{0};j<S;++j)
				if (t[i].ch[j])
					cerr<<i<<" "<<t[i].ch[j]<<" "<<char(j+'a')<<endl;
		for (int i{cur};i;i=t[i].link) cerr<<i<<" ";
		cerr<<endl<<endl;
	}
} T;