/**
 * Author: Kapt
 * Description: Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde ?s$ for $N=2^{22}$)
 */
#pragma once

using cd = complex<double>; // better implement by hand

void fft(vector<cd>& a, bool inv = false) {
  int n = a.size();
  int k = 0;
  while ((1 << k) < n) ++k;
  static vector<int> rev;
  static vector<cd> power = {0, 1};
  rev.resize(n);
  rev[0] = 0;
  for (int i = 1; i < n; ++i) {
    rev[i] = rev[i / 2] / 2 + ((i & 1) << (k - 1));
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int l = 1; l < n; l *= 2) {
    if ((int)power.size() == l) {
      power.resize(2 * l);
      complex<long double> w = polar(1.0L, acos(-1.0L) / l);
      cd wcd = {(double)w.real(), (double)w.imag()};
      for (int i = l; i < 2 * l; ++i) {
        power[i] = power[i / 2];
        if (i & 1) power[i] *= w;
      }
    }
    for (int i = 0; i < n; i += 2 * l) {
      for (int j = 0; j < l; ++j) {
        cd x = a[i + j], y = a[i + j + l] * power[j + l];
        a[i + j] = x + y;
        a[i + j + l] = x - y;
      }
    }
  }
  if (inv) {
    reverse(a.begin() + 1, a.end());
    double anti = 1.0L / n;
    for (cd& x : a) x *= anti;
  }
}
