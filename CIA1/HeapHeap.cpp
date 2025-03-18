#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct HeapNode {
    int value;        // The actual integer value.
    int listIndex;    // Which list this value comes from.
    int elementIndex; // The index of this element in its list.
};

class Heap {
    vector<HeapNode> arr;

  public:
    // Insert a HeapNode into the min-heap.
    void insertKey(HeapNode key) {
        arr.push_back(key);
        int i = arr.size() - 1;
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (arr[parent].value <= arr[i].value)
                break;
            swap(arr[parent], arr[i]);
            i = parent;
        }
    }

    // Delete and return the root (minimum element) of the heap.
    HeapNode popRoot() {
        if (arr.empty()) {
            return {-1, -1, -1};
        }
        HeapNode rootValue = arr[0];
        arr[0] = arr.back();
        arr.pop_back();
        heapify(0);
        return rootValue;
    }

    bool empty() {
        return arr.empty();
    }

  private:
    // Helper function to restore heap property starting from index i.
    void heapify(int i) {
        int n = arr.size();
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = i;
            if (left < n && arr[left].value < arr[smallest].value)
                smallest = left;
            if (right < n && arr[right].value < arr[smallest].value)
                smallest = right;
            if (smallest == i)
                break;
            swap(arr[i], arr[smallest]);
            i = smallest;
        }
    }

  public:
    void printHeap() {
        for (auto node : arr) {
            cout << node.value << " ";
        }
        cout << endl;
    }
};