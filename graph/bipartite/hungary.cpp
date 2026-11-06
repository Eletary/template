// @title 匈牙利算法
// @brief 二分图最大匹配
// @complexity O(nm)
// @author yzj
namespace bipartite {
        int vis[N], match[N], ans;

        inline bool hungary (int x) {
                for (auto y : G[x]) if (!vis[y]) {
                        vis[y] = 1;
                        if (! match[y] || hungary (match[y])) return match[y] = x, 1;
                }
                return 0;
        }
        
        inline void mian () {
                n = read (); int k = read (); m = read ();
                for (int i = 1, x, y; i <= m; i ++) {
                        x = read (); y = read ();
                        G[x].pb (y); 
                }
                
                rep (i, 1, n) {
                        rep (j, 0, k) vis[j] = 0;
                        ans += hungary (i);
                }

                printf ("%lld\n", ans);
        }
}
