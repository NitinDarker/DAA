#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pii; // (weight, vertex)

// Dijkstra's Algorithm
vector<int> dijkstra(int source, const vector<vector<pii>> &adjList, int V) {
    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    priority_queue<pii, vector<pii>, greater<pii>> minHeap;

    dist[source] = 0;
    minHeap.push({0, source}); // (distance, vertex)

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        minHeap.pop();

        if (visited[u])
            continue;

        visited[u] = true;

        // For all neighbors of u
        for (auto [weight, v] : adjList[u]) {
            if (!visited[v] && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                minHeap.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<pii>> adjList(V);

    // Example graph: (u, v, weight)
    // Edge 0-1 with weight 2
    adjList[0].push_back({2, 1});
    adjList[1].push_back({2, 0});

    // Edge 0-3 with weight 6
    adjList[0].push_back({6, 3});
    adjList[3].push_back({6, 0});

    // Edge 1-2 with weight 3
    adjList[1].push_back({3, 2});
    adjList[2].push_back({3, 1});

    // Edge 1-3 with weight 8
    adjList[1].push_back({8, 3});
    adjList[3].push_back({8, 1});

    // Edge 1-4 with weight 5
    adjList[1].push_back({5, 4});
    adjList[4].push_back({5, 1});

    // Edge 2-4 with weight 7
    adjList[2].push_back({7, 4});
    adjList[4].push_back({7, 2});

    int source = 0;
    vector<int> distances = dijkstra(source, adjList, V);

    // Output shortest distances from source
    cout << "Vertex\tDistance from Source " << source << "\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << distances[i] << "\n";
    }

    return 0;
}
