/**
 * Author: Vsevolod Nagibin
 * Description: Finding K shortest paths in a directed weighted graph
 */

//Leftist Heap

struct Node{
  long long val;
  int val_v;
  int left;
  int right;
  int s;
  Node(long long _val = 0, int _val_v = 0) {
    val = _val;
    val_v = _val_v;
    left = right = -1;
    s = 1;
  }
};

// don't know why
Node nodes[5000000];
int nodes_cnt = 0;

int node(long long val, int val_v) {
  nodes[nodes_cnt] = Node(val, val_v);
  ++nodes_cnt;
  return nodes_cnt - 1;
}

int get_s(int v) {
  if (v == -1)
    return 0;
  return nodes[v].s;
}

int merge(int a, int b) {
  if (a == -1)
    return b;
  if (b == -1)
    return a;
  if (nodes[a].val > nodes[b].val)
    swap(a, b);
  int ans = node(nodes[a].val, nodes[a].val_v);
  nodes[ans].left = nodes[a].left;
  nodes[ans].right = merge(nodes[a].right, b);
  if (get_s(nodes[ans].right) > get_s(nodes[ans].left))
    swap(nodes[ans].left, nodes[ans].right);
  nodes[ans].s = get_s(nodes[ans].right) + 1;
  return ans;
}

int extract_min(int v) {
  return merge(nodes[v].left, nodes[v].right);
}

// max number of vertices
const int MAXN = 500000;
const long long INF = 1e18;
vector<pair<pair<int, int>, int>> G[MAXN];
vector<pair<pair<int, int>, int>> GT[MAXN];
long long d[MAXN];
int par[MAXN];
int par_edge[MAXN];

int main() {
#ifdef DEBUG
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#else
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
#endif

  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    G[u].emplace_back(make_pair(v, i), w);
    GT[v].emplace_back(make_pair(u, i), w);
  }
  fill(d, d + n, INF);
  d[n - 1] = 0;
  set<pair<long long, int>> Q;
  vector<int> order;
  par_edge[n - 1] = -1;
  Q.emplace(0, n - 1);
  while (!Q.empty()) {
    int v = Q.begin()->second;
    order.emplace_back(v);
    Q.erase(Q.begin());
    for (auto t : GT[v]) {
      if (d[t.first.first] > d[v] + t.second) {
        Q.erase(make_pair(d[t.first.first], t.first.first));
        d[t.first.first] = d[v] + t.second;
        par_edge[t.first.first] = t.first.second;
        par[t.first.first] = v;
        Q.emplace(d[t.first.first], t.first.first);
      }
    }
  }
  vector<int> heaps(n, -1);
  for (int v : order) {
    if (v != n - 1)
      heaps[v] = heaps[par[v]];
    for (auto t : G[v]) {
      if (t.first.second == par_edge[v])
        continue;
      if (d[t.first.first] != INF)
        heaps[v] = merge(heaps[v], node(d[t.first.first] + t.second - d[v], t.first.first));
    }
  }
  if (d[0] == INF) {
    for (int i = 0; i < k; ++i)
      cout << -1 << ' ';
    cout << '\n';
    return 0;
  }
  vector<long long> ans(k, -1);
  vector<int> rest_heaps(k, -1);
  ans[0] = d[0];
  rest_heaps[0] = heaps[0];
  if (rest_heaps[0] != -1)
    Q.emplace(d[0] + nodes[rest_heaps[0]].val, 0);
  for (int i = 1; i < k; ++i) {
    if (Q.empty())
      break;
    int j = Q.begin()->second;
    Q.erase(Q.begin());
    ans[i] = ans[j] + nodes[rest_heaps[j]].val;
    rest_heaps[i] = heaps[nodes[rest_heaps[j]].val_v];
    rest_heaps[j] = extract_min(rest_heaps[j]);
    if (rest_heaps[i] != -1)
      Q.emplace(ans[i] + nodes[rest_heaps[i]].val, i);
    if (rest_heaps[j] != -1)
      Q.emplace(ans[j] + nodes[rest_heaps[j]].val, j);
  }
  for (int i = 0; i < k; ++i)
    cout << ans[i] << ' ';
  cout << '\n';
  return 0;
}
