/**
 * Author: Tikhon228
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 */
#pragma once



struct Edge {
	int from, to, cap, nxt;
	int flow = 0;
	Edge() {}
   	Edge(int from, int to, int cap, int nxt) : from(from), to(to), cap(cap), nxt(nxt) {}
};

struct DinicFlow {
	static const int inf = 1e9;

	int n;
	int s, t;
	vector<Edge> e;
	vector<int> head;
	vector<int> dist;

	DinicFlow(int n, int s = -1, int t = -1) : n(n), s(s), t(t), head(vector<int>(n, -1)) {}



	void add_edge(int from, int to, int cap) {
		e.emplace_back(from, to, cap, head[from]);
		head[from] = e.size() - 1;
		e.emplace_back(to, from, 0, head[to]);
		head[to] = e.size() - 1;
	}
	void add_undir_edge(int from, int to, int cap) {
    e.emplace_back(from, to, cap, head[from]);
    head[from] = e.size() - 1;
    e.emplace_back(to, from, cap, head[to]);
    head[to] = e.size() - 1;
  }

  int dfs(int u, int mf) {
    if (u == t) return mf;
    int res = 0;
    for (int& i = head[u]; i != -1; i = e[i].nxt) {
      Edge& e1 = e[i];
      if (e1.cap - e1.flow < 1) continue;
      if (dist[e1.from] + 1 != dist[e1.to]) continue;
      int x = dfs(e1.to, min(mf - res, e1.cap - e1.flow));
      if (x == 0) continue;
      res += x;
      e1.flow += x;
      e[i ^ 1].flow -= x;
      if (e1.cap - e1.flow || mf == res) return res;
    }
    return res;
  }

  int flow() {
    bool found = true;
    while (found) {
      dist.assign(n, inf);
      queue<int> burn;
      dist[s] = 0;
      burn.push(s);
      while (!burn.empty()) {
        int at = burn.front();
        burn.pop();
        for (int i = head[at]; i != -1; i = e[i].nxt) {
          if (e[i].cap - e[i].flow < 1) continue;
          if (dist[at] + 1 >= dist[e[i].to]) continue;
          dist[e[i].to] = dist[at] + 1;
          burn.push(e[i].to);
        }
      }
      auto head_copy = head;
      found = false;
      while (dfs(s, inf)) found = true;
      head = head_copy;
    }
    ll res = 0;
    for (int i = head[s]; i != -1; i = e[i].nxt)
      res += e[i].flow;
    return res;
  }
};

