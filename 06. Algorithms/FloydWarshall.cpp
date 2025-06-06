#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // Infinity represented by a large number

void floydWarshall(vector<vector<int>> W, int n) {
    vector<vector<int>> D = W;                   // Step 1: Initialize D as W
    vector<vector<int>> P(n, vector<int>(n, 0)); // Step 2: Initialize P as 0

    for (int k = 0; k < n; ++k) {        // Step 3: For each intermediate node
        vector<vector<int>> D_prime = D; // New matrix D'

        for (int i = 0; i < n; ++i) { // Step 4-5: For each pair of vertices
            for (int j = 0; j < n; ++j) {
                if (D[i][k] < INF && D[k][j] < INF && D[i][j] > D[i][k] + D[k][j]) {
                    D_prime[i][j] = D[i][k] + D[k][j]; // Step 7
                    P[i][j] = k + 1;                   // Step 8 (for clarity, store 1-based indexing)
                } else {
                    D_prime[i][j] = D[i][j]; // Step 9
                }
            }
        }

        D = D_prime; // Step 10: Update D
    }

    // Display Result
    cout << "Shortest distance matrix (D):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (D[i][j] == INF)
                cout << "INF ";
            else
                cout << setw(3) << D[i][j] << " ";
        }
        cout << endl;
    }

    // Display Predecessor Matrix
    cout << "\nPredecessor matrix (P):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(3) << P[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n = 4; // Number of vertices

    // Weighted adjacency matrix (W)
    // INF represents no direct path
    vector<vector<int>> W = {
        {0, 3, INF, 5},
        {2, 0, INF, 4},
        {INF, 1, 0, INF},
        {INF, INF, 2, 0}};

    floydWarshall(W, n);

    return 0;
}
