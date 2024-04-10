#include "../utilities/template.h"
#include "../utilities/utils.h"

#include "../../content/graph/Hungarian.h"
#include "../../content/graph/MinCostMaxFlow.h"

int solve_min_cost(int n, int m) {
    int N = n + m + 2;
    MinCost network(N, 0, N - 1);
    for (int i = 1; i <= n; ++i) {
        network.add_dir_edge(0, i, 1, 0);
    }
    for (int i = 1; i <= m; ++i) {
        network.add_dir_edge(n + i, N - 1, 1, 0);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            network.add_dir_edge(i, n + j, 1, A[i][j]);
    }
    return network.min_cost_max_flow().first;
}

void test(int n, int m) {
    int real_ans = solve_min_cost(n, m);
    auto ans = Hungarian(n, m).first;
    assert(real_ans == ans);
}

int main() {
    // 10^4 test of graphs of size ~10
    for (int _ = 0; _ < 10000; ++_) {
        int n = rand() % 40 + 8;
        int m = n + rand() % 3;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j)
                A[i][j] = rand() % 100;
        }
        test(n, m);
    }
    cout << "Tests passed!" << endl;
}