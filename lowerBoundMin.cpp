#include "Heap.cpp"
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int lowerBound(vector<int> nums) {
    int n = nums.size();
    Heap *small = new Heap(); // Min-Heap
    Heap *large = new Heap(); // Max-Heap
    int i = 0;
    while (i < n) {
        if (i+1 == n) break;
        small->insertKey(min(nums[i], nums[i+1]));
        large->insertKey(max(nums[i], nums[i+1]));
        i += 2;
    }
    int mini = small->popRoot();
    int maxi = large->popRoot();
    if (n % 2 != 0) {
        if (nums[n-1] > maxi) maxi = nums[n-1];
        if (nums[n-1] < mini) mini = nums[n-1];   
    }
    return mini;
}

int main() {

    return 0;
}