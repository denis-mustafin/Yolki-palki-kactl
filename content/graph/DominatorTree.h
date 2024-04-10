/**
 * Author: Denis Mustafin
 * Description: Dominator tree
 */

struct Dom {
    static const int MAXN = MAX;
    vector<int> g[MAXN], e[MAXN], ch[MAXN];
    int tin[MAXN], ind[MAXN];
    int t = 0;
    int n;
    int s;

    Dom(int n, int s): n(n), s(s) {}

    void add(int u, int v) {
        g[u].push_back(v);
    }

    void calc_tin(int v) {
        tin[v] = t++;
        ind[tin[v]] = v;
        for (int u : g[v]) {
            if (tin[u] == -1) {
                calc_tin(u);
                ch[tin[v]].push_back(tin[u]);
            }
            e[tin[u]].push_back(tin[v]);
        }
    }

    vector<int> inv_sdom[MAXN];
    int dom[MAXN], sdom[MAXN], p[MAXN], val[MAXN];

    int get_min(int u, int v) {
        return sdom[u] < sdom[v] ? u : v;
    }

    int get(int v) {
        if (v == p[v]) return val[v];
        int res = get(p[v]);
        p[v] = p[p[v]];
        return val[v] = get_min(val[v], res);
    }

    void solve() {
        fill(tin, tin + n, -1);
        fill(ind, ind + n, -1);
        iota(p, p + n, 0);
        iota(val, val + n, 0);
        iota(sdom, sdom + n, 0);
        calc_tin(s);
        for (int v = n - 1; v >= 0; --v) {
            for (int u : e[v])
                sdom[v] = min(sdom[v], sdom[get(u)]);
            inv_sdom[sdom[v]].push_back(v);
            for (int u : inv_sdom[v]) {
                int res = get(u);
                if (sdom[res] == v) {
                    dom[u] = v;
                } else {
                    dom[u] = res;
                }
            }
            for (int u : ch[v]) p[u] = v;
        }
        vector<int> rdom(n);
        for (int v = 0; v < n; ++v) {
            if (dom[v] != sdom[v])
                dom[v] = dom[dom[v]];
            if (ind[v] != -1)
                rdom[ind[v]] = ind[dom[v]];
        }
        for (int v = 0; v < n; ++v)
            dom[v] = rdom[v];
    }
};
