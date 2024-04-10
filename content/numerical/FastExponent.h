/**
 * Author: Kapt
 * Description: Works faster than naive implemtntation with ln
 * Time: O(N \log N)
 */
#pragma once

void exp_step(vector<int>& f, vector<int>& g, const vector<int>& h) {
  int m = f.size();
  g = g + g - f * (g * g);
  g.resize(m);
  vector<int> q(m, 0);
  for (int i = 0; i < m - 1 && i + 1 < (int)h.size(); ++i) {
    q[i] = mul(h[i + 1], i + 1);
  }
  vector<int> w = q + g * (der(f) - f * q);
  w.resize(2 * m - 1);
  vector<int> h1(2 * m);
  for (int i = 0; i < 2 * m && i < (int)h.size(); ++i) {
    h1[i] = h[i];
  }
  f = f + f * (h1 - integ(w));
  f.resize(2 * m);
}

vector<int> exp(vector<int> h, int n) {
  /// h[0] = 0
  vector<int> f = {1}, g = {1};
  for (int m = 1; m < n; m *= 2) {
    exp_step(f, g, h);
  }
  f.resize(n);
  return f;
}
