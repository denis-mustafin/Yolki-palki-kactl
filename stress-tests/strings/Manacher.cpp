#include "../utilities/template.h"

#include "../../content/strings/Manacher.h"

#include "string_generator.hpp"

bool is_pali(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return s == t;
}

// check that manacher is correct
void test(string s) {
    vector<int> pali = get_odd_pali(s);
    int n = static_cast<int>(s.size());
	for (int i = 0; i < n; ++i) {
        int maxlen = -1;
        for (int len = 1; len <= n; len += 2) {
            int half = len / 2;
            if (i >= half && i + half < n && is_pali(s.substr(i - half, len))) {
                maxlen = max(maxlen, len);
            }
        }
        assert(pali[i] == maxlen / 2);
	}
}

int main() {
	run_many_lines(test);
    cout << "Tests passed!" << endl;
}
