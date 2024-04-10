/**
 * Author: Tikhon Evteev
 * Description: Persistent treap with merge, split and finding
 * element by index
 * Time: O(\log N)
 */
#pragma once

struct node {
  int val;
  int l = 0, r = 0;
  int sz = 1;
  node() {}
  node(int val) : val(val) {}
};

const int MAXN = 6e7;
node tree[MAXN];
int c = 1;

int merge(int a, int b) {
  if (a == 0) return b;
  if (b == 0) return a;
  ll r = rand();  // int
  r %= (tree[a].sz + tree[b].sz);
  int c1 = c++;
  if (r < tree[a].sz) {
    tree[c1] = tree[a];
    tree[c1].sz += tree[b].sz;
    tree[c1].r = merge(tree[c1].r, b);
  } else {
    tree[c1] = tree[b];
    tree[c1].sz += tree[a].sz;
    tree[c1].l = merge(a, tree[c1].l);
  }
  return c1;
}

pii split(int a, ll sz) {  // first.sz = sz
  if (a == 0) return {0, 0};
  int c1 = c++;
  tree[c1] = tree[a];
  a = c1;
  pii p;
  if (tree[tree[a].l].sz >= sz) {
    p = split(tree[a].l, sz);
    tree[a].l = p.second;
    tree[a].sz -= tree[p.first].sz;
    p.second = a;
  } else {
    p = split(tree[a].r, sz - tree[tree[a].l].sz - 1);
    tree[a].r = p.first;
    tree[a].sz -= tree[p.second].sz;
    p.first = a;
  }
  return p;
}

int get(int a, ll pos) {
  if (a == 0) return 0;
  if (tree[tree[a].l].sz == pos) {
    return tree[a].val;
  } else if (tree[tree[a].l].sz > pos) {
    return get(tree[a].l, pos);
  } else {
    return get(tree[a].r, pos - tree[tree[a].l].sz - 1);
  }
}
