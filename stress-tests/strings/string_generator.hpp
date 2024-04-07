#include "../utilities/template.h"

// call f for all possible lines with symbols to alpha
template<class F>
void gen_lines(string& s, int at, int alpha, F f) {
    if (at == static_cast<int>(s.size())) {
        f();
    } else {
        for (int i = 0; i < alpha; ++i) {
            s[at] = char('a' + i);
            gen_lines(s, at + 1, alpha, f);
        }
    }
}

typedef void (*StringTester)(string);

void run_many_lines(StringTester f) {
    // test ~3^12 strings
    for (int n = 0; n <= 12; ++n) {
        string s(n, 'x');
        gen_lines(s, 0, 3, [&]() {
            f(s);
        });
    }
	// then ~4^10 strings
    for (int n = 0; n <= 10; ++n) {
        string s(n, 'x');
        gen_lines(s, 0, 4, [&]() {
            f(s);
        });
    }
    // some random longer lines
    // len ~300
    for (int i = 0; i < 100; ++i) {
        int cur_len = 200 + rand() % 200;
        string s(cur_len, 'x');
        for (int i = 0; i < cur_len; ++i)
            s[i] = char('a' + rand() % 6);
        f(s);
    }
}
