#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to compute the prefix function (π array)
vector<int> computePrefixFunction(const string &p) {
    int m = p.length();
    vector<int> pi(m, 0); // Π[1..m], using 0-based indexing in C++
    int k = 0;

    for (int q = 1; q < m; q++) {
        while (k > 0 && p[k] != p[q]) {
            k = pi[k - 1]; // k ← Π[k]
        }
        if (p[k] == p[q]) {
            k = k + 1;
        }
        pi[q] = k;
    }

    return pi; // return Π
}

// KMP string matching algorithm
void KMPMatcher(const string &T, const string &P) {
    int n = T.length();
    int m = P.length();
    vector<int> pi = computePrefixFunction(P);

    int q = 0; // number of characters matched

    for (int i = 0; i < n; i++) {
        while (q > 0 && P[q] != T[i]) {
            q = pi[q - 1]; // q ← Π[q]
        }
        if (P[q] == T[i]) {
            q = q + 1;
        }
        if (q == m) {
            cout << "Pattern occurs with shift " << (i - m + 1) << endl;
            q = pi[q - 1]; // Prepare for next potential match
        }
    }
}

// Driver function to test above code
int main() {
    string text = "ababcabcabababd";
    string pattern = "ababd";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl
         << endl;

    KMPMatcher(text, pattern);

    return 0;
}
