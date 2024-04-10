/**
 * Author: Tikhon Evteev/Vsevolod Nagibin
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 */
#pragma once

// Warning: int flow!
const int INF = 1e9;

struct Edge {
  int from, to;
  int flow;
  int cap;
  Edge(int from, int to, int flow, int cap): from(from), to(to), flow(flow), cap(cap) {}
};

struct DinicFlow {
  vector<Edge> edges;
  vector<vector<int>> G;
  vector<int> last_edge;
  vector<int> dist;
  int N;
  int s, t;

  DinicFlow(int N, int s, int t): edges(), G(N), last_edge(N, 0), dist(N, 0), N(N), s(s), t(t) {}

  void add_undir_edge(int from, int to, int cap) {
    G[from].emplace_back(edges.size());
    edges.emplace_back(from, to, 0, cap);
    G[to].emplace_back(edges.size());
    edges.emplace_back(to, from, 0, cap);
  }

  void add_dir_edge(int from, int to, int cap) {
    G[from].emplace_back(edges.size());
    edges.emplace_back(from, to, 0, cap);
    G[to].emplace_back(edges.size());
    edges.emplace_back(to, from, 0, 0);
  }

  int dfs(int v, int mf) {
    if (v == t)
      return mf;
    int res = 0;
    for (; last_edge[v] < (int)G[v].size(); ++last_edge[v]) {
      int i = G[v][last_edge[v]];
      if (dist[edges[i].to] != dist[v] + 1)
        continue;
      if (edges[i].cap <= edges[i].flow)
        continue;
      int cur = dfs(edges[i].to, min(mf - res, edges[i].cap - edges[i].flow));
      if (cur == 0)
        continue;
      res += cur;
      edges[i].flow += cur;
      edges[i ^ 1].flow -= cur;
      if (edges[i].cap > edges[i].flow || res == mf)
        return res;
    }
    return res;
  }

  int flow() {
    while (true) {
      dist.assign(N, N);
      deque<int> Q;
      dist[s] = 0;
      Q.emplace_back(s);
      while (!Q.empty()) {
        int v = Q.front();
        Q.pop_front();
        for (int i : G[v]) {
          if (edges[i].cap > edges[i].flow && dist[edges[i].to] > dist[v] + 1) {
            dist[edges[i].to] = dist[v] + 1;
            Q.emplace_back(edges[i].to); 
          }
        }
      }
      if (dist[t] == N)
        break;
      fill(last_edge.begin(), last_edge.end(), 0);
      while (dfs(s, INF));
    }
    int res = 0;
    for (int i : G[s])
      res += edges[i].flow;
    return res;
  }
};

