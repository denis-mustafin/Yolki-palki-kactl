/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-08
 * Source: https://en.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm
 * Description: Find a global minimum cut in an undirected weighted graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: stress tested with dinic
 */
#pragma once

// G[i][j] = weight of the edge from i to j
// symmetric matrix
pair<int, vector<int>> global_min_cut(vector<vector<int>> G) {
	int n = (int) G.size();
	vector<vector<int>> comps(n);
	for (int i = 0; i < n; ++i)
		comps[i].resize(1, i);
	pair<int, vector<int>> ans(1e9, {});
	for (int i = 0; i < n - 1; ++i) {
		vector<int> w = G[0];
		vector<bool> taken(n, false);
		taken[0] = true;
		int s = 0, t = 0, last_cost = 0;
		for (int j = 0; j < n - i - 1; ++j) {
			int opt = -1;
			for (int u = 0; u < n; ++u) {
				if (!taken[u] && !comps[u].empty()) {
					if (opt == -1 || w[u] > w[opt])
						opt = u;
				}
			}
			s = t;
			t = opt;
			last_cost = w[opt];
			taken[opt] = true;
			for (int u = 0; u < n; ++u) {
				if (!taken[u])
					w[u] += G[opt][u];
			}
		}
		if (last_cost < ans.first) {
			ans.first = last_cost;
			ans.second = comps[t];
		}
		// merge s and t
		for (int u : comps[t]) {
			comps[s].emplace_back(u);
		}
		comps[t].clear();
		for (int i = 0; i < n; ++i) {
			G[s][i] += G[t][i];
			G[i][s] = G[s][i];
		}
	}
	return ans;
}
