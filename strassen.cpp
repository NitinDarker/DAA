#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// power of two =>
// x & (x-1) == 0

int nextPowerOf2(int size) {
    int i = 0;
    while (pow(2, i) < size) {
        i++;
    }
    return pow(2, i);
}

vector<vector<int>> fixMult(vector<vector<int>> mat) {
    int n = mat.size();
    int rowSize = nextPowerOf2(n);
    for (int i = 0; i < mat.size(); i++) {
        
    }
}

vector<vector<int>> matrixAdd(vector<vector<int>> arr, vector<vector<int>> brr) {
    // 2x2 Matrix Addition
    vector<vector<int>> crr = {
        {arr[0][0] + brr[0][0], arr[0][1] + brr[0][1]},
        {arr[1][0] + brr[1][0], arr[1][1] + brr[1][1]}};
    return crr;
}

vector<vector<int>> matrixSub(vector<vector<int>> arr, vector<vector<int>> brr) {
    // 2x2 Matrix Addition
    vector<vector<int>> crr = {
        {arr[0][0] - brr[0][0], arr[0][1] - brr[0][1]},
        {arr[1][0] - brr[1][0], arr[1][1] - brr[1][1]}};
    return crr;
}

vector<vector<int>> matrixMul(vector<vector<int>> arr, vector<vector<int>> brr) {
    // 2x2 Matrix Multiply
    int a11 = arr[0][0];
    int a12 = arr[0][1];
    int a21 = arr[1][0];
    int a22 = arr[1][1];
    int b11 = brr[0][0];
    int b12 = brr[0][1];
    int b21 = brr[1][0];
    int b22 = brr[1][1];

    int p1 = (a11 + a22) * (b11 + b22);
    int p2 = (a21 + a22) * b11;
    int p3 = (b12 - b22) * a11;
    int p4 = (b21 - b11) * a22;
    int p5 = (a11 + a12) * b22;
    int p6 = (a21 - a11) * (b11 + b12);
    int p7 = (a12 - a22) * (b21 + b22);

    int c1 = p1 + p4 - p5 + p7;
    int c2 = p3 + p5;
    int c3 = p2 + p4;
    int c4 = p1 + p3 - p2 + p6;

    vector<vector<int>> crr = {{c1, c2}, {c3, c4}};
    return crr;
}

vector<vector<int>> strassen(vector<vector<int>> &A, vector<vector<int>> &B) {
    // Divide 4x4 into 2x2
    vector<vector<int>> A11(2, vector<int>(2, 0)), A12(2, vector<int>(2, 0)), A21(2, vector<int>(2, 0)), A22(2, vector<int>(2, 0));
    vector<vector<int>> B11, B12, B21, B22;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            A11[i][j] = A[i][j];         // Top-left
            A12[i][j] = A[i][j + 2];     // Top-right
            A21[i][j] = A[i + 2][j];     // Bottom-left
            A22[i][j] = A[i + 2][j + 2]; // Bottom-right
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            B11[i][j] = B[i][j];        
            B12[i][j] = B[i][j + 2];     
            B21[i][j] = B[i + 2][j];    
            B22[i][j] = B[i + 2][j + 2]; 
        }
    }

    vector<vector<int>> p1, p2, p3, p4, p5, p6, p7;
    p1 = matrixMul(matrixAdd(A11, A22), matrixAdd(B11, B22));
    p2 = matrixMul(matrixAdd(A21, A22), B11);
    p3 = matrixMul(matrixSub(B12, B22), A11);
    p4 = matrixMul(matrixSub(B21, B11), A22);
    p5 = matrixMul(matrixAdd(A11, A12), B22);
    p6 = matrixMul(matrixSub(A21, A11), matrixAdd(B11, B12));
    p7 = matrixMul(matrixSub(A12, A22), matrixAdd(B21, B22));

    vector<vector<int>> c1, c2, c3, c4;
    c1 = matrixSub(matrixAdd(matrixAdd(p4, p1), p7), p5);
    c2 = matrixAdd(p3, p5);
    c3 = matrixAdd(p2, p4);
    c4 = matrixSub(matrixAdd(matrixAdd(p1, p3), p6), p2);

    vector<vector<int>> crr = {{c1, c2}, {c3, c4}};
    return crr;
}

int main() {
    
    return 0;
}