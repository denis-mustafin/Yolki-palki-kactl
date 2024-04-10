#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/GlobalMinCut.h"
#include "../../content/graph/Dinic.h"

int global_min_cut_dinic(vector<vector<int>> G) {
    int N = G.size();
    int ans = 1e9;
    for (int s = 0; s < N; ++s) {
        for (int t = s + 1; t < N; ++t) {
            DinicFlow dinic(N, s, t);
            for (int i = 0; i < N; ++i) {
                for (int j = i + 1; j < N; ++j)
                    dinic.add_undir_edge(i, j, G[i][j]);
            }
            ans = min(ans, dinic.flow());
        }
    }
    return ans;
}

void test(vector<vector<int>> G) {
    int real_ans = global_min_cut_dinic(G);
    auto ans = global_min_cut(G);
    assert(real_ans == ans.first);
    // check that really a cut
    int N = G.size();
    auto L = ans.second;
    sort(L.begin(), L.end());
    // all different
    assert(unique(L.begin(), L.end()) == L.end());
    assert(0 < L.size() && L.size() < N);
    int real_cost = 0;
    vector<bool> in_left(N, false);
    for (int i : L)
        in_left[i] = true;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (in_left[i] && !in_left[j])
                real_cost += G[i][j];
        }
    }
    assert(real_cost == ans.first);
}

int main() {
    // 10^4 test of graphs of size ~10
    for (int _ = 0; _ < 10000; ++_) {
        int N = rand() % 8 + 6;
        vector<vector<int>> G(N, vector<int>(N));
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                int w = rand() % 10;
                G[i][j] = G[j][i] = w;
            }
        }
        test(G);
    }
    cout << "Tests passed!" << endl;
}