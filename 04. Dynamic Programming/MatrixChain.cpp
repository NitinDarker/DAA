#include <climits> // For INT_MAX
#include <iostream>
#include <vector>
using namespace std;

// Function to compute the cost table (m) and split table (s)
void matrixChainOrder(const vector<int> &p, vector<vector<int>> &m, vector<vector<int>> &s) {
    int n = p.size() - 1;

    // Step 3: Initialize m[i][i] = 0
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // Step 4–12: Fill tables using bottom-up DP
    for (int l = 2; l <= n; l++) { // l is chain length
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k <= j - 1; k++) {
                // Cost: m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

// Helper function to print optimal parenthesis
void printOptimalParens(const vector<vector<int>> &s, int i, int j) {
    if (i == j) {
        cout << "A" << i;
    } else {
        cout << "(";
        printOptimalParens(s, i, s[i][j]);
        cout << " x ";
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ")";
    }
}

int main() {
    // Example input: dimensions of matrices A1 (30x35), A2 (35x15), A3 (15x5), etc.
    vector<int> p = {30, 35, 15, 5, 10, 20, 25}; // 6 matrices

    int n = p.size() - 1;
    vector<vector<int>> m(n + 1, vector<int>(n + 1, 0)); // Cost table
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0)); // Split table

    matrixChainOrder(p, m, s);

    cout << "Minimum number of scalar multiplications: " << m[1][n] << endl;
    cout << "Optimal Parenthesis: ";
    printOptimalParens(s, 1, n);
    cout << endl;

    return 0;
}
