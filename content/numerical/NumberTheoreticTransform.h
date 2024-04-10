/**
 * Author: Kapt
 * Description: fft(a, 0) computes direct dft, fft(a, 1) - inverted.
 * Inputs must be in [0, mod), returns in [0, mod).
 * Implemented with some foreign optimizations
 * Time: O(N \log N), multiplies polynomials of size 1 << 19 in 117 ms (-blazingio for i/o)
 */
#pragma once

const int G1 = 3;

void fft(vector<int>& A, bool inv = false) {
  int k = 0;
  while ((1 << k) < (int)A.size())
    ++k;
  int N = 1 << k;
  static vector<int> rev;
  static vector<uint32_t> power = {0, 1};
  rev.resize(N);
  for (int i = 0; i < N; ++i) {
    rev[i] = rev[i / 2] / 2 + ((i & 1) << (k - 1));
    if (i < rev[i]) swap(A[i], A[rev[i]]);
  }

  static auto mul = [](uint32_t a, uint32_t b) {
    return (uint64_t(a) * b) % MOD;
  };

  static vector<uint32_t> A1;
  A1.resize(N);
  for (int i = 0; i < N; ++i)
    A1[i] = A[i];

  for (int l = 1, t = 0; l < N; l *= 2, ++t) {
    if ((int)power.size() == l) {
      power.resize(2 * l);
      uint32_t w = pw(G1, (MOD - 1) / 2 / l);
      for (int i = l; i < 2 * l; ++i) {
        power[i] = power[i / 2];
        if (i & 1) power[i] = mul(power[i], w);
      }
    }
    if ((k - t - 1) & 3) {
      for (int i = 0; i < N; i += 2 * l) {
        for (int j = 0; j < l; ++j) {
          uint32_t x = A1[i + j], y = mul(power[j + l], A1[i + j + l]);
          A1[i + j] = x + y;
          A1[i + j + l] = x + MOD - y;
        }
      }
    } else {
      for (int i = 0; i < N; i += 2 * l) {
        for (int j = 0; j < l; ++j) {
          uint32_t x = A1[i + j], y = mul(power[j + l], A1[i + j + l]);
          A1[i + j] = (uint64_t(x) + y) % MOD;
          A1[i + j + l] = (uint64_t(x) + MOD - y) % MOD;
        }
      }
    }
  }

  for (int i = 0; i < N; ++i)
    A[i] = A1[i];

  if (inv) {
    reverse(A.begin() + 1, A.end());
    int anti = pw(N, MOD - 2);
    for (int i = 0; i < N; ++i)
      A[i] = mul(A[i], anti);
  }
}
