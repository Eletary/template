// @title 2-SAT
// @brief Tarjan 强连通分量求解 2-SAT
// @complexity O(n+m)
// @author yzj
namespace twosat {
        int tot; 

        inline void tarjan (int x) {
                dfn[x] = low[x] = ++ DDFN; stk[++ topf] = x; ins[x] = 1;
                for (int i = hd[x], y; i; i = ne[i]) 
                        if (! dfn[y = to[i]]) tarjan (y), low[x] = min (low[x], low[y]);
                        else if (ins[y]) low[x] = min (low[x], dfn[y]);
                if (dfn[x] == low[x]) {
                        int z; ++ tot;
                        do { z = stk[topf --]; ins[z] = 0; id[z] = tot; } while (x != z);
                }
        }

        inline void getans () {
                /*
                rep (i, 1, n) 
                        if (id[i true] < id[i false]) 
                                then i is true;
                */
        }
}
