#include "../utilities/template.h"

#include "../../content/strings/ZFunction.h"

#include "string_generator.hpp"

// check that z is correct
void test(string s) {
	vector<int> z = get_z(s);
    int n = static_cast<int>(s.size());
	if (n > 0)
		assert(z[0] == 0);
	for (int i = 1; i < n; ++i) {
		int maxlen = -1;
		for (int len = 0; len <= n - i; ++len) {
			if (s.substr(0, len) == s.substr(i, len))
				maxlen = max(maxlen, len);
		}
        assert(z[i] == maxlen);
	}
}

int main() {
	run_many_lines(test);
    cout << "Tests passed!" << endl;
}
