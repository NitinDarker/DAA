#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

// Tree node
struct HuffmanNode {
    char data; // character
    int freq;  // frequency
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char d, int f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }
};

// Comparator for min-heap
struct Compare {
    bool operator()(HuffmanNode *a, HuffmanNode *b) {
        return a->freq > b->freq; // smallest frequency has higher priority
    }
};

// Function to print Huffman Codes
void printHuffmanCodes(HuffmanNode *root, string code) {
    if (!root)
        return;

    // If it's a leaf node, print the character and its code
    if (!root->left && !root->right) {
        cout << root->data << ": " << code << endl;
        return;
    }

    printHuffmanCodes(root->left, code + "0");
    printHuffmanCodes(root->right, code + "1");
}

int main() {
    // Sample input: characters with their frequencies
    char characters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int n = sizeof(characters) / sizeof(characters[0]);

    // Step 1: Create a min-heap (priority queue)
    priority_queue<HuffmanNode *, vector<HuffmanNode *>, Compare> minHeap;

    for (int i = 0; i < n; i++) {
        minHeap.push(new HuffmanNode(characters[i], freq[i]));
    }

    // Step 2: Build Huffman Tree
    while (minHeap.size() > 1) {
        HuffmanNode *left = minHeap.top();
        minHeap.pop();
        HuffmanNode *right = minHeap.top();
        minHeap.pop();

        HuffmanNode *merged = new HuffmanNode('-', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        minHeap.push(merged);
    }

    // Step 3: Traverse the tree and print codes
    HuffmanNode *root = minHeap.top();
    cout << "Huffman Codes:\n";
    printHuffmanCodes(root, "");

    return 0;
}
