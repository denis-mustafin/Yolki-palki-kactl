#include "../utilities/template.h"

#include "../../content/strings/SuffixAuto.h"

#include "string_generator.hpp"

void dfs_no_cycles(int v, vector<int>& used) {
    used[v] = 1;
    for (int i = 0; i < ALPHA; ++i) {
        if (go[v][i] == -1)
            continue;
        assert(used[go[v][i]] != 1);
        if (!used[go[v][i]])
            dfs_no_cycles(go[v][i], used);
    }
    used[v] = 2;
}

void gen_all_lines(int v, string cur, vector<bool>& is_term, vector<string>& accepted) {
    if (is_term[v])
        accepted.emplace_back(cur);
    for (int i = 0; i < ALPHA; ++i) {
        if (go[v][i] != -1)
            gen_all_lines(go[v][i], cur + char('a' + i), is_term, accepted);
    }
}

void test(string s) {
    // clearing the nodes
    nodes_cnt = 0;
    int n = int(s.size());
    int last_node = node();
    for (char c : s) {
        last_node = push_back(last_node, c);
    }
    assert(nodes_cnt <= max(1, 2 * n));
    vector<int> used(nodes_cnt, 0);
    // no cycles
    dfs_no_cycles(0, used);
    // all reachable
    for (int i = 0; i < nodes_cnt; ++i)
        assert(used[i]);
    vector<bool> is_term(nodes_cnt, false);
    {
        int tmp = last_node;
        while (tmp != -1) {
            is_term[tmp] = true;
            tmp = suff[tmp];
        }
    }
    vector<string> accepted;
    gen_all_lines(0, "", is_term, accepted);
    sort(accepted.begin(), accepted.end(), [](const string& a, const string& b) {
        return a.size() < b.size();
    });
    assert((int)accepted.size() == n + 1);
    for (int len = 0; len <= n; ++len)
        assert(accepted[len] == s.substr(n - len, len));
}

int main() {
	run_many_lines(test);
	cout << "Tests passed!" << endl;
}
