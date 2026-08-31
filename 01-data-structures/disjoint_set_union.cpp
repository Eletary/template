// @title Disjoint Set Union
// @brief Maintain components with path compression and union by size.
// @complexity O(alpha(n)) amortized per operation
// @tags dsu, union-find, connectivity

struct DSU {
    std::vector<int> parent, size;

    explicit DSU(int n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (x != parent[x]) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    bool same(int a, int b) { return find(a) == find(b); }
    int component_size(int x) { return size[find(x)]; }
};
