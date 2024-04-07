/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: z[i] computes the length of the longest common prefix of s[i:] and s,
 * except z[0] = 0. (abacaba -> 0010301)
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vector<int> get_z(string s) {
	int n = (int)s.size();
	int j = 0;
	vector<int> z(n);
	for (int i = 1; i < n; ++i) {
		if (j + z[j] > i)
			z[i] = min(z[i - j], j + z[j] - i);
		while (s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] > j + z[j])
			j = i;
	}
	return z;
}
