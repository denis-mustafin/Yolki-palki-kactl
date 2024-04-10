/**
 * Author: Vsevolod Nagibin
 * Description: Solves the assignment problem for minimization. $O(n^3)$.
 */
#pragma once


// 1-indexing !
const int MAXN = 100;
int A[MAXN][MAXN];

pair<int, vector<int>> Hungarian(int n, int m) {
    const int INF = 1e9;

    // potentials
    vector<int> u(n + 1);
    vector<int> v(m + 1);
    vector<int> p(m + 1);
    vector<int> way(m + 1);
    for (int i = 1; i <= n; ++i) {
        vector<int> minv(m + 1, INF);
        vector<bool> used(n + 1, false);
        p[0] = i;
        int j0 = 0;
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            int d = INF;
            for (int j = 1; j <= m; ++j) {
                if (!used[j]) {
                    int cur = A[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < d) {
                        d = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (used[j]) {
                    u[p[j]] += d;
                    v[j] -= d;
                } else {
                    minv[j] -= d;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    vector<int> ans(n + 1);
    for (int j = 1; j <= m; ++j)
        ans[p[j]] = j;
    int cost = -v[0];
    return make_pair(cost, ans);
}
