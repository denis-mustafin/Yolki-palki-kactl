/**
 * Author: Kapt
 * Description: Initially there is an array of linear functions with pointers at x=0
 * update changes a line at ind to l with pointer at x=0
 * heaten advences pointers of lines from [l; r) by d
 * get finds the minimum value at current pointer for lines in [l; r)
 * requireres define int long long!
 * Time: O(N \log^{?} N) 186ms for n, q = 1e5
 */
#pragma once


const int INFX = 2e12, INFY = 2e18;

struct Line {
  int k, b;

  Line(int k = 0, int b = 0): k(k), b(b) {}

  int operator()(int x) {
    return k * x + b;
  }
};

struct LazyKST {

  int n;
  vector<Line> tree;
  vector<int> melt;
  vector<int> add;

  void pull(int v) {
    int v1 = v * 2, v2 = v * 2 + 1;
    if (tree[v1].b < tree[v2].b || (tree[v1].b == tree[v2].b && tree[v1].k < tree[v2].k)) {
      swap(v1, v2);
    }
    tree[v] = tree[v2];
    melt[v] = min(melt[v1], melt[v2]);
    if (tree[v1].k < tree[v2].k) {
      int x = (tree[v1].b - tree[v2].b + tree[v2].k - tree[v1].k - 1) / (tree[v2].k - tree[v1].k);
      melt[v] = min(melt[v], x);
    }
  }

  void push(int v) {
    int d = add[v];
    add[v] = 0;
    if (v * 2 < 4 * n) {
      add[v * 2] += d;
      add[v * 2 + 1] += d;
      melt[v * 2] -= d;
      tree[v * 2].b += tree[v * 2].k * d;
      melt[v * 2 + 1] -= d;
      tree[v * 2 + 1].b += tree[v * 2 + 1].k * d;
    }
  }

  void build(int v, int vl, int vr, vector<Line>& arr) {
    add[v] = 0;
    if (vr - vl == 1) {
      tree[v] = arr[vl];
      melt[v] = INFX;
      return;
    }
    int vm = (vl + vr) / 2;
    build(v * 2, vl, vm, arr);
    build(v * 2 + 1, vm, vr, arr);
    pull(v);
  }

  LazyKST(vector<Line> arr = {}): n(arr.size()), tree(n * 4), melt(n * 4), add(n * 4) {
    build(1, 0, n, arr);
  }

  void rec_upd(int v, int vl, int vr, int ind, Line val) {
    push(v);
    if (ind >= vr || ind < vl) return;
    if (vr - vl == 1) {
      tree[v] = val;
      return;
    }
    int vm = (vl + vr) / 2;
    rec_upd(v * 2, vl, vm, ind, val);
    rec_upd(v * 2 + 1, vm, vr, ind, val);
    pull(v);
  }

  void upd(int ind, Line l) {
    rec_upd(1, 0, n, ind, l);
  }

  void propagate(int v, int vl, int vr) {
    if (melt[v] > 0) return;
    int vm = (vl + vr) / 2;
    push(v);
    propagate(v * 2, vl, vm);
    propagate(v * 2 + 1, vm, vr);
    pull(v);
  }

  void rec_heaten(int v, int vl, int vr, int l, int r, int d) {
    if (l >= vr || r <= vl) return;
    if (l <= vl && r >= vr) {
      tree[v].b += tree[v].k * d;
      if (vr - vl > 1) {
        melt[v] -= d;
        add[v] += d;
      }
      propagate(v, vl, vr);
      return;
    }
    int vm = (vl + vr) / 2;
    push(v);
    rec_heaten(v * 2, vl, vm, l, r, d);
    rec_heaten(v * 2 + 1, vm, vr, l, r, d);
    pull(v);
  }

  void heaten(int l, int r, int d) {
    rec_heaten(1, 0, n, l, r, d);
  }

  int rec_get(int v, int vl, int vr, int l, int r) {
    if (l >= vr || r <= vl) return INFY;
    if (l <= vl && r >= vr) return tree[v].b;
    int vm = (vl + vr) / 2;
    push(v);
    int res1 = rec_get(v * 2, vl, vm, l, r);
    int res2 = rec_get(v * 2 + 1, vm, vr, l, r);
    return min(res1, res2);
  }

  int get(int l, int r) {
    return rec_get(1, 0, n, l, r);
  }
};
