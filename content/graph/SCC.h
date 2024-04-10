/**
 * Author: Kapt
 * Description: Finds strongly connected components in a
 * directed graph.
 * Time: O(E + V)
 */
#pragma once

struct SCC {
  int n;
  vector<int>* g;
  vector<int> tin, used, up;
  int tim = 0;

  SCC(int n): n(n) {
    g = new vector<int>[n];
    tin.resize(n, -1);
    used.resize(n);
    up.resize(n);
  }

  ~SCC() {
    delete[] g;
  }

  void add_edge(int u, int v) {
    g[u].push_back(v);
  }

  vector<int> stk;

  void dfs(int v) {
    tin[v] = tim++;
    up[v] = tin[v];
    stk.push_back(v);
    used[v] = true;
    for (int u : g[v]) {
      if (tin[u] == -1) {
        dfs(u);
        up[v] = min(up[v], up[u]);
      } else if (used[u]) {
        up[v] = min(up[v], tin[u]);
      }
    }
    if (tin[v] == up[v]) {
      while (stk.back() != v) {
        used[stk.back()] = false;
        stk.pop_back();
      }
      used[v] = false;
      stk.pop_back();
      /// the component had just beed lifted from the stk
    }
  }

  void get() {
    for (int i = 0; i < n; ++i) {
      if (tin[i] == -1) {
        dfs(i);
      }
    }
  }
};
