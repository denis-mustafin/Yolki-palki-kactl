/**
 * Author: Tikhon Evteev/Vsevolod Nagibin
 * Date: 2024-04-08
 * Description: Min-cost max-flow.
 * Status: not tested
 */
#pragma once

// Warning: inf flow and cost!
// Each step works in O(E log V), sometimes O(V^2) may be better
// Dijkstra can be replaced
const int INF = 1e9;

struct CostEdge {
  int from, to;
  int flow;
  int cap;
  int cost;
  CostEdge(int from, int to, int flow, int cap, int cost): from(from), to(to), flow(flow), cap(cap), cost(cost) {}
};

struct MinCost {
  vector<CostEdge> edges;
  vector<vector<int>> G;
  vector<int> dist;
  vector<int> potential;
  vector<int> par;
  int N;
  int s, t;

  MinCost(int N, int s, int t): edges(), G(N), dist(N), potential(N), par(N), N(N), s(s), t(t) {}

  void add_dir_edge(int from, int to, int cap, int cost) {
    G[from].emplace_back(edges.size());
    edges.emplace_back(from, to, 0, cap, cost);
    G[to].emplace_back(edges.size());
    edges.emplace_back(to, from, 0, 0, -cost);
  }

  void calc_potential() {
    for (int i = 0; i < N; ++i) {
      for (auto e : edges) {
        if (e.flow < e.cap)
          potential[e.to] = min(potential[e.to], potential[e.from] + e.cost);
      }
    }
  }

  int flow;
  int cost;

  bool step() {
    fill(dist.begin(), dist.end(), INF);
    fill(par.begin(), par.end(), -1);
    set<pair<int, int>> Q;
    dist[s] = 0;
    Q.emplace(0, s);
    while (!Q.empty()) {
      int v = Q.begin()->second;
      Q.erase(Q.begin());
      for (int i : G[v]) {
        if (edges[i].cap > edges[i].flow) {
          int u = edges[i].to;
          int opt = dist[v] + edges[i].cost + potential[v] - potential[u];
          if (dist[u] > opt) {
            Q.erase(make_pair(dist[u], u));
            par[u] = i;
            dist[u] = opt;
            Q.emplace(dist[u], u);
          }
        }
      }
    }
    if (dist[t] == INF)
      return false;
    int mn = INF;
    int cur = t;
    while (cur != s) {
      mn = min(mn, edges[par[cur]].cap - edges[par[cur]].flow);
      cur = edges[par[cur]].from;
    }
    cur = t;
    while (cur != s) {
      edges[par[cur]].flow += mn;
      edges[par[cur] ^ 1].flow -= mn;
      cur = edges[par[cur]].from;
    }
    cost += mn * (dist[t] + potential[t] - potential[s]);
    for (int i = 0; i < N; ++i)
      potential[i] += dist[i];
    return true;
  }

  pair<int, int> min_cost_max_flow() {
    flow = 0;
    cost = 0;
    calc_potential();
    while (step());
    return make_pair(cost, flow);
  }
};