/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: Two trees for all the palindrome substring of a line.
 * One tree for odd palindromes, other for even. Has linear size (up to n+2 nodes)
 * Time: O(n)
 * Status: no tests
 */
#pragma once

// maxlen + eps
const int MAXSZ = 400'100;
const int ALPHA = 26;

int go[MAXSZ][ALPHA];
int len[MAXSZ];
int suff[MAXSZ];
int nodes_cnt = 0;

int node() {
  fill(go[nodes_cnt], go[nodes_cnt] + ALPHA, -1);
  len[nodes_cnt] = 0;
  suff[nodes_cnt] = -1;
  ++nodes_cnt;
  return nodes_cnt - 1;
}

int get_char_id(char c) {
  return c - 'a';
}

string cur_s;

int push_back(int last, char c) {
  cur_s += c;
  while ((int)cur_s.size() < len[last] + 2 || cur_s[cur_s.size() - len[last] - 2] != c)
    last = suff[last];
  if (go[last][get_char_id(c)] == -1) {
    int new_v = node();
    go[last][get_char_id(c)] = new_v;
    len[new_v] = len[last] + 2;
    if (len[last] == -1) {
      suff[new_v] = 1; // even root
    } else {
      int new_suff = suff[last];
      while (new_suff != -1 && cur_s[cur_s.size() - len[new_suff] - 2] != c)
        new_suff = suff[new_suff];
      suff[new_v] = go[new_suff][get_char_id(c)];
    }
  }
  last = go[last][get_char_id(c)];
  return last;
}

/* in main
  node();  0 - odd root
  node();  1 - even root
  suff[0] = -1;
  len[0] = -1;
  suff[1] = 0;
  len[1] = 0;
*/
