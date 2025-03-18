#include <bits/stdc++.h>
using namespace std;

void bubbleSort(int *arr, int size);

void printArray(vector<int> arr) {
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int optimalMergePattern(vector<int> arr) {
    while (arr.size() > 1) {
        sort(arr.begin(), arr.end());
        printArray(arr);
        int sum = arr[0] + arr[1];
        arr.erase(arr.begin());
        arr.erase(arr.begin());
        arr.push_back(sum);
    }
    return arr[0];
}

int optimalMergePattern(int arr[], int n) {
    while (n > 1) {
        bubbleSort(arr, n);
        printArray(arr, n);
        int sum = arr[0] + arr[1];
        for (int i = 2; i < n; i++) {
            arr[i - 2] = arr[i];
        }
        arr[n - 2] = sum;
        arr--;
    }
    return arr[n - 1];
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Optimal Merge: " << optimalMergePattern(arr) << endl;
    return 0;
}

void bubbleSort(int *arr, int size) {
    while (size > 1) {
        int i = 0;
        int j = i + 1;
        while (j < size) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]);
            }
            i++;
            j++;
        }
        size--;
    }
}