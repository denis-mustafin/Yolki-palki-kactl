#include "../utilities/template.h"

#include "../../content/strings/SuffixArray.h"

#include "string_generator.hpp"

int dumb_lcp(string s, string t) {
	int ans = 0;
	while (ans < (int)s.size() && ans < (int)t.size() && s[ans] == t[ans])
		++ans;
	return ans;
}

void test(string s) {
	SuffixArray sa(s);
	s += '$';
	int n = (int) s.size();
	vector<int> order(n);
	iota(order.begin(), order.end(), 0);
	auto get_suffix = [&](int a) {
		return s.substr(a, n - a);
	};
	sort(order.begin(), order.end(), [&](int a, int b) {
		return get_suffix(a) < get_suffix(b);
	});
	assert(order == sa.order);
	for (int i = 0; i + 1 < n; ++i) {
		assert(sa.lcp[i] == dumb_lcp(get_suffix(order[i]), get_suffix(order[i + 1])));
	}
}

int main() {
	run_many_lines(test);
	cout << "Tests passed!" << endl;
}
