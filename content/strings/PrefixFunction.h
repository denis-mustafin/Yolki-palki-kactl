/**
 * Author: Vsevolod Nagibin
 * Date: 2024-04-07
 * Description: pi[x] computes the length of the longest prefix of s that ends at x,
 * other than s[0...x] itself (abacaba -> 0010123).
 * Can be used to find all occurrences of a string.
 * Time: O(n)
 * Status: Stress-tested
 */
#pragma once

vector<int> get_pi(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j != -1 && s[j] != s[i])
            j = (j == 0 ? -1 : pi[j - 1]);
        pi[i] = j + 1;
    }
    return pi;
}
