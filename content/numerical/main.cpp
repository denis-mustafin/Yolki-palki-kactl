#include <bits/stdc++.h>
using namespace std;

#include "FastFourierTransform.h"

int main() {

  vector<cd> a = {{1, 0}, {2, 0}}, b = {{1, 0}, {3, 0}};

  int sz = 4;
  a.resize(sz);
  b.resize(sz);
  fft(a);
  fft(b);
  for (int i = 0; i < sz; ++i) {
    a[i] *= b[i];
  }
  fft(a, true);
  a.resize(3);
  for (auto elem : a) {
    cout << elem.real() << " " << elem.imag() << endl;
  }

  return 0;
}
