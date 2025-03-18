#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// Min-Heap
class Heap {
    vector<int> arr;

  public:
    // Insert a key into the min-heap.
    void insertKey(int key) {
        arr.push_back(key);
        int i = arr.size() - 1; 

        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[parent] <= arr[i])
                break;
            swap(arr[parent], arr[i]);
            i = parent;
        }
    }

    // Delete and return the root (minimum element) of the heap.
    int popRoot() {
        if (arr.empty()) {
            return -1;
        }
        int rootValue = arr[0];
        arr[0] = arr.back();
        arr.pop_back();
        heapify(0);
        return rootValue;
    }

  private:
    // Helper function to restore heap property starting from index i.
    void heapify(int i) {
        int n = arr.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;

            if (left < n && arr[left] < arr[smallest])
                smallest = left;
            if (right < n && arr[right] < arr[smallest])
                smallest = right;

            if (smallest == i)
                break; // The heap property is satisfied.

            swap(arr[i], arr[smallest]);
            i = smallest;
        }
    }

  public:
    // Prints the current elements in the heap.
    void printHeap() {
        for (int val : arr) {
            cout << val << " ";
        }
        cout << endl;
    }
};