#include "../utilities/template.h"

#include "../../content/strings/PrefixFunction.h"

#include "string_generator.hpp"

// check that pi is correct
void test(string s) {
	vector<int> pi = get_pi(s);
    int n = static_cast<int>(s.size());
	for (int i = 0; i < n; ++i) {
		int maxlen = -1;
        for (int len = 0; len <= i; ++len) {
            if (s.substr(0, len) == s.substr(i + 1 - len, len))
                maxlen = max(maxlen, len);
        }
        assert(pi[i] == maxlen);
	}
}

int main() {
	run_many_lines(test);
    cout << "Tests passed!" << endl;
}
