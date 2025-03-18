#include "HeapHeap.cpp"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Distributes the input numbers into m lists
vector<vector<int>> distributeNumbers(vector<int> &numbers, int m) {
    vector<vector<int>> lists(m);
    for (int i = 0; i < numbers.size(); i++) {
        int listIndex = i % m;
        lists[listIndex].push_back(numbers[i]);
    }
    return lists;
}

// Sorts each list individually
void sortLists(vector<vector<int>> &lists) {
    for (auto &list : lists) {
        sort(list.begin(), list.end());
    }
}

void printLists(vector<vector<int>> &lists) {
    cout << "\nSorted lists:" << endl;
    for (int i = 0; i < lists.size(); i++) {
        cout << "List " << i + 1 << ": ";
        for (int num : lists[i]) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Merge m sorted lists into a single sorted list using heap.
vector<int> mergeSortedLists(vector<vector<int>> &lists) {
    Heap minHeap;
    vector<int> merged;

    for (int i = 0; i < lists.size(); i++) {
        if (!lists[i].empty()) {
            HeapNode node;
            node.value = lists[i][0];
            node.listIndex = i;
            node.elementIndex = 0;
            minHeap.insertKey(node);
        }
    }

    while (!minHeap.empty()) {
        HeapNode current = minHeap.popRoot();
        merged.push_back(current.value);

        int nextIndex = current.elementIndex + 1;

        if (nextIndex < lists[current.listIndex].size()) {
            HeapNode nextNode;
            nextNode.value = lists[current.listIndex][nextIndex];
            nextNode.listIndex = current.listIndex;
            nextNode.elementIndex = nextIndex;
            minHeap.insertKey(nextNode);
        }
    }

    return merged;
}

int main() {
    // Take n integers as input and sort them into m sorted lists/arrays
    int n;
    cout << "Enter the number of integers (n): ";
    cin >> n;

    vector<int> numbers(n);
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    int m;
    cout << "Enter the number of lists (m): ";
    cin >> m;

    vector<vector<int>> lists = distributeNumbers(numbers, m);
    sortLists(lists);
    printLists(lists);
    vector<int> merged = mergeSortedLists(lists);

    cout << "\nMerged Sorted List:" << endl;
    for (int num : merged) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}