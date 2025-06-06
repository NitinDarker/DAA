// https://www.geeksforgeeks.org/problems/search-pattern-rabin-karp-algorithm--141631/1
#include <bits/stdc++.h>
using namespace std;

vector<int> rabinKarp(string &pat, string &txt) {
    vector<int> res;
    int m = pat.size();
    int n = txt.size();
    int q = 11; // A prime number
    int d = 26; // Radix

    int h = 1; // helper variable
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    int patHash = 0;
    int txtHash = 0;

    // Calculating hash of pattern
    for (int i = 0; i < m; i++) {
        patHash = (d * patHash + pat[i] - 'a') % q;
        txtHash = (d * txtHash + txt[i] - 'a') % q;
    }

    // Rolling Hash on txt
    for (int k = 0; k <= n - m; k++) {

        // Hash Hit
        if (patHash == txtHash) {
            int match = true;
            for (int l = 0; l < m; l++) {
                if (pat[l] != txt[l + k]) {
                    // Spurious Hit
                    match = false;
                    break;
                }
            }
            if (match) {
                res.push_back(k + 1);
            }
        }

        if (k < n - m)
            txtHash = (d * (txtHash - h * (txt[k] - 'a')) + (txt[k + m] - 'a')) % q;
        if (txtHash < 0)
            txtHash += q;
    }
    return res;
}

void printMatch(string &txt, string &pat, vector<int> matches) {
    cout << txt << endl;

    int idx = 0;
    int k = 1;
    while (idx != matches.size() && k <= txt.size()) {
        if (k != matches[idx]) {
            cout << " ";
            k++;
        } else {
            cout << pat << endl;
            idx++;
            k++;
            for (int i = 1; i < k; i++) {
                cout << " ";
            }
        }
    }
}

int main() {
    string txt, pat;
    cout << "Enter the text string: ";
    cin >> txt;
    cout << "Enter a pattern to be matched: ";
    cin >> pat;

    vector<int> matches = rabinKarp(pat, txt);
    printMatch(txt, pat, matches);

    cout << endl << "Index: ";
    for (int it : matches) {
        cout << it << " ";
    }
    cout << endl;
}
