#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX

int N; // Number of cities

// Function to find the minimum edge cost having an end at the vertex i
int firstMin(const vector<vector<int>> &cost, int i) {
    int min = INF;
    for (int k = 0; k < N; k++)
        if (cost[i][k] < min && i != k)
            min = cost[i][k];
    return min;
}

// Second minimum cost from vertex i
int secondMin(const vector<vector<int>> &cost, int i) {
    int first = INF, second = INF;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;

        if (cost[i][j] <= first) {
            second = first;
            first = cost[i][j];
        } else if (cost[i][j] <= second && cost[i][j] != first) {
            second = cost[i][j];
        }
    }
    return second;
}

// Global variables
int final_res = INF;
vector<int> final_path;

// Recursive function for Branch and Bound
void TSPRec(const vector<vector<int>> &cost, vector<bool> &visited, int curr_bound,
            int curr_weight, int level, vector<int> &curr_path) {

    // Base case: All cities visited
    if (level == N) {
        if (cost[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + cost[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                final_path = curr_path;
                final_path.push_back(curr_path[0]);
                final_res = curr_res;
            }
        }
        return;
    }

    // Try next cities
    for (int i = 0; i < N; i++) {
        if (cost[curr_path[level - 1]][i] != 0 && !visited[i]) {
            int temp = curr_bound;
            curr_weight += cost[curr_path[level - 1]][i];

            // Bound Calculation
            if (level == 1)
                curr_bound -= ((firstMin(cost, curr_path[level - 1]) + firstMin(cost, i)) / 2);
            else
                curr_bound -= ((secondMin(cost, curr_path[level - 1]) + firstMin(cost, i)) / 2);

            // If acceptable, go deeper
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                TSPRec(cost, visited, curr_bound, curr_weight, level + 1, curr_path);
            }

            // Backtrack
            curr_weight -= cost[curr_path[level - 1]][i];
            curr_bound = temp;
            visited[i] = false;
        }
    }
}

// Driver function to start TSP Branch and Bound
void TSP(const vector<vector<int>> &cost) {
    vector<int> curr_path(N + 1, -1);
    vector<bool> visited(N, false);

    // Compute initial lower bound
    int curr_bound = 0;
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(cost, i) + secondMin(cost, i));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

    visited[0] = true;
    curr_path[0] = 0;

    TSPRec(cost, visited, curr_bound, 0, 1, curr_path);

    // Print result
    cout << "\nMinimum cost: " << final_res << endl;
    cout << "Path taken : ";
    for (int i : final_path)
        cout << i << " ";
    cout << endl;
}

int main() {
    vector<vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}};

    N = cost.size();
    TSP(cost);

    return 0;
}
