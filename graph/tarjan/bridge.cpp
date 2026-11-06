// @title 桥
// @brief Tarjan 求无向图中的桥
// @complexity O(n+m)
// @author yzj
namespace bridge {
        inline void tarjan (int x, int in) {
                dfn[x] = low[x] = ++ DDFN;
                for (int i = hd[x], y; i; i = ne[i]) if (i != in) {
                        if (! dfn[y = to[i]]) {
                                tarjan (y, i ^ 1);
                                low[x] = min (low[x], low[y]);
                                if (low[y] > dfn[x]) bg[i >> 1] = 1;
                        }
                        else low[x] = min (low[x], dfn[y]);
                }
        }
}
