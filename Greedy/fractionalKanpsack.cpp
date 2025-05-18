#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Structure to represent items with weight and value
struct Item {
    int value;
    int weight;
    double ratio; // value-to-weight ratio
};

// Comparison function to sort items by value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to solve fractional knapsack problem
double fractionalKnapsack(vector<Item> &items, int capacity) {
    // Calculate value-to-weight ratio for each item
    for (int i = 0; i < items.size(); i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }

    // Sort items by value-to-weight ratio (descending)
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;
    int currentWeight = 0;

    // Iterate through sorted items
    for (int i = 0; i < items.size(); i++) {
        // If adding the entire item doesn't exceed capacity
        if (currentWeight + items[i].weight <= capacity) {
            currentWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            // Take a fraction of the item
            int remainingCapacity = capacity - currentWeight;
            totalValue += items[i].ratio * remainingCapacity;
            break; // Knapsack is full
        }
    }

    return totalValue;
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<Item> items(n);

    cout << "Enter value and weight for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << " (value weight): ";
        cin >> items[i].value >> items[i].weight;
    }

    double maxValue = fractionalKnapsack(items, capacity);

    cout << "Maximum value in knapsack: " << maxValue << endl;

    return 0;
}
