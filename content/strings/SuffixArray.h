/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: Builds suffix array for a string.
 * \texttt{sa[i]} is the starting index of the suffix which
 * is $i$'th in the sorted suffix array.
 * The returned vector is of size $n+1$, and \texttt{sa[0] = n}.
 * The \texttt{lcp} array contains longest common prefixes for
 * neighbouring strings in the suffix array:
 * \texttt{lcp[i] = lcp(sa[i], sa[i-1])}, \texttt{lcp[0] = 0}.
 * The input string must not contain any zero bytes.
 * Time: O(n \log n)
 * Status: stress-tested
 */
#pragma once

// all symbols > $
struct SuffixArray {
	vector<int> order;
	vector<int> lcp;
	vector<int> id;
	SuffixArray(string s) {
		s += '$';
		int n = (int) s.size();
		order.resize(n);
		vector<int> classes(n);
		vector<int> new_order(n);
		vector<int> new_classes(n);
		vector<int> cnt(n);
		iota(order.begin(), order.end(), 0);
		sort(order.begin(), order.end(), [&](int a, int b) {
			return s[a] < s[b];
		});
		classes[order[0]] = 0; 
		for (int i = 1; i < n; ++i) 
			classes[order[i]] = classes[order[i - 1]] + (s[order[i]] != s[order[i - 1]]);
		auto safe = [&](int x) {
			if (x >= n) return x - n;
			return x;
		};
		for (int l = 1; l < n; l *= 2) {
			fill(cnt.begin(), cnt.end(), 0);
			for (int i = 0; i < n; ++i)
				++cnt[classes[i]];
			for (int i = 1; i < n; ++i)
				cnt[i] += cnt[i - 1];
			for (int i = n - 1; i >= 0; --i) {
				int j = order[i] - l;
				if (j < 0)
					j += n;
				--cnt[classes[j]];
				new_order[cnt[classes[j]]] = j;
			}
			new_classes[new_order[0]] = 0;
			for (int i = 1; i < n; ++i) {
				new_classes[new_order[i]] = new_classes[new_order[i - 1]] + 
				(make_pair(classes[new_order[i]], classes[safe(new_order[i] + l)]) != 
				make_pair(classes[new_order[i - 1]], classes[safe(new_order[i - 1] + l)]));
			}
			swap(classes, new_classes);
			swap(order, new_order);
		}
		lcp.resize(n);
		id.resize(n);
		for (int i = 0; i < n; ++i)
			id[order[i]] = i;
		int tmp = 0;
		for (int i = 0; i < n; ++i) {
			if (id[i] == n - 1) {
				tmp = 0;
				continue;
			}
			int j = order[id[i] + 1];
			while (s[i + tmp] == s[j + tmp])
				++tmp;
			lcp[id[i]] = tmp;
			tmp = max(tmp - 1, 0);
		}
	}
};