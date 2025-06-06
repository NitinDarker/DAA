#include <iostream>
#include <vector>
using namespace std;

int knapsack(int W, const vector<int> &weights, const vector<int> &values, int n) {
    vector<vector<int>> B(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                B[i][w] = max(values[i - 1] + B[i - 1][w - weights[i - 1]],
                              B[i - 1][w]);
            } else {
                B[i][w] = B[i - 1][w];
            }
        }
    }

    return B[n][W];
}

int main() {
    vector<int> weights = {2, 3, 4, 5};
    vector<int> values = {3, 4, 5, 6};
    int W = 5; // Knapsack capacity
    int n = weights.size();

    int maxVal = knapsack(W, weights, values, n);

    cout << "Maximum value in 0/1 Knapsack: " << maxVal << endl;

    return 0;
}
