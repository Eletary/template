// @title 割点
// @brief Tarjan 求无向图中的割点
// @complexity O(n+m)
// @author yzj
namespace cutnode {

        vc <int> ans;
        inline void tarjan (int x, int rt) {
                dfn[x] = low[x] = ++ DDFN; int cnt = 0, fl = 0;
                for (auto y : G[x]) 
                        if (! dfn[y]) {
                                tarjan (y, rt);
                                low[x] = min (low[x], low[y]);
                                if (low[y] >= dfn[x]) {
                                        ++ cnt;
                                        if (!fl && (x != rt || cnt > 1)) 
                                                fl = 1, ans.pb (x);
                                }
                        }
                        else low[x] = min (low[x], dfn[y]);
        }
}
