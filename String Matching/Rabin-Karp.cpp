#include <iostream>
#include <string>
using namespace std;

// Function to implement Rabin-Karp pattern matching
void rabinKarpMatching(const string &T, const string &P, int d, int q) {
    int n = T.length(); // length of text
    int m = P.length(); // length of pattern
    int h = 1;

    // Precompute h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    int p = 0; // hash value for pattern
    int t = 0; // hash value for text

    // Initial hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int s = 0; s <= n - m; s++) {
        // Check the hash values
        if (p == t) {
            // If hash values match, check characters one by one
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (T[s + j] != P[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern occurs at shift " << s << endl;
            }
        }

        // Calculate hash value for next window of text
        if (s < n - m) {
            t = (d * (t - T[s] * h) + T[s + m]) % q;

            // Make sure t is positive
            if (t < 0) {
                t = t + q;
            }
        }
    }
}

// Main driver
int main() {
    string T = "3141592653589793"; // Example text
    string P = "26535";            // Example pattern
    int d = 10;                    // Assuming decimal input
    int q = 101;                   // A prime number for hashing

    cout << "Text: " << T << "\nPattern: " << P << endl;
    rabinKarpMatching(T, P, d, q);

    return 0;
}
