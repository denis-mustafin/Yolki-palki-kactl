/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: Minimum automaton accepting all the suffixes of the line
 * (and only them). Has linear size (up to 2n vertices, 3n edges)
 * Time: O(n)
 * Status: Stress-tested
 */
#pragma once

// maxlen * 2
const int MAXN = 300300;
const int ALPHA = 26;

int go[MAXN][ALPHA];
int par[MAXN];
int len[MAXN];
int suff[MAXN];
int nodes_cnt = 0;

int get_char_id(char c) {
  return c - 'a';
}

int node() {
  fill(go[nodes_cnt], go[nodes_cnt] + ALPHA, -1);
  suff[nodes_cnt] = -1;
  len[nodes_cnt] = 0;
  ++nodes_cnt;
  return nodes_cnt - 1;
}

int push_back(int last, char c) {
  int new_v = node();
  go[last][get_char_id(c)] = new_v;
  par[new_v] = last;
  len[new_v] = len[last] + 1;
  last = suff[last];
  while (last != -1 && go[last][get_char_id(c)] == -1) {
    go[last][get_char_id(c)] = new_v;
    last = suff[last];
  }
  if (last == -1) {
    suff[new_v] = 0;
  } else {
    int pos_suff = go[last][get_char_id(c)];
    if (len[pos_suff] == len[last] + 1) {
      suff[new_v] = pos_suff;
    } else {
      int new_suff = node();
      len[new_suff] = len[last] + 1;
      suff[new_suff] = suff[pos_suff];
      par[new_suff] = last;
      suff[pos_suff] = new_suff;
      for (int i = 0; i < ALPHA; ++i)
        go[new_suff][i] = go[pos_suff][i];
      while (last != -1 && go[last][get_char_id(c)] == pos_suff) {
        go[last][get_char_id(c)] = new_suff;
        last = suff[last];
      }
      suff[new_v] = new_suff;
    }
  }
  return new_v;
}
