#include <iostream>
#include <vector>
using namespace std;

vector<int> calculate_lps(string pattern) {
    int n = pattern.length();
    vector<int> lps(n, 0);
    int length = 0;
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

int kmp_search(string text, string pattern) {
    int count = 0;
    int m = pattern.length();
    int n = text.length();
    vector<int> lps = calculate_lps(pattern);
    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;

            if (j == m) {
                count++;
                j = lps[j - 1];
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return count;
}
