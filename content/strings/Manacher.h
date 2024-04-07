/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: For each position in a string, computes p[i] = half length of
 *  longest odd palindrome around pos i (half rounded down).
 * Time: O(N)
 * Status: Stress-tested
 */
#pragma once

vector<int> get_odd_pali(string s) {
	int n = (int)s.size();
	vector<int> pali(n);
	int l = 0, r = 0;
	for (int i = 0; i < n; ++i) {
		if (i < r) {
			pali[i] = min(r - i - 1, pali[l + r - i - 1]);
		}
		while (i > pali[i] && i + pali[i] + 1 < n && s[i - pali[i] - 1] == s[i + pali[i] + 1])
			++pali[i];
		if (i + pali[i] + 1 > r) {
			r = i + pali[i] + 1;
			l = i - pali[i];
		}
	}
	return pali;
}
