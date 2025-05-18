#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

// Helper: Get next power of 2
int nextPowerOf2(int n) {
    int power = 1;
    while (power < n)
        power <<= 1;
    return power;
}

// Matrix addition
Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Matrix subtraction
Matrix subtract(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// Strassen recursive function
Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n, 0));

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    Matrix A11(newSize, vector<int>(newSize)),
        A12(newSize, vector<int>(newSize)),
        A21(newSize, vector<int>(newSize)),
        A22(newSize, vector<int>(newSize)),

        B11(newSize, vector<int>(newSize)),
        B12(newSize, vector<int>(newSize)),
        B21(newSize, vector<int>(newSize)),
        B22(newSize, vector<int>(newSize));

    // Dividing matrices A and B into 4 sub-matrices
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }

    // 7 recursive multiplications (Strassen’s formulas)
    auto M1 = strassen(add(A11, A22), add(B11, B22));
    auto M2 = strassen(add(A21, A22), B11);
    auto M3 = strassen(A11, subtract(B12, B22));
    auto M4 = strassen(A22, subtract(B21, B11));
    auto M5 = strassen(add(A11, A12), B22);
    auto M6 = strassen(subtract(A21, A11), add(B11, B12));
    auto M7 = strassen(subtract(A12, A22), add(B21, B22));

    // Calculating result C matrix
    Matrix C11 = add(subtract(add(M1, M4), M5), M7);
    Matrix C12 = add(M3, M5);
    Matrix C21 = add(M2, M4);
    Matrix C22 = add(subtract(add(M1, M3), M2), M6);

    // Combining sub-matrices into one
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }

    return C;
}

// Function to prepare matrices by padding and call strassen
Matrix multiply(const Matrix &A, const Matrix &B, int origSize) {
    int n = A.size();
    int m = nextPowerOf2(n);

    // Pad A and B
    Matrix A_pad(m, vector<int>(m, 0));
    Matrix B_pad(m, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A_pad[i][j] = A[i][j];
            B_pad[i][j] = B[i][j];
        }

    Matrix C_pad = strassen(A_pad, B_pad);

    // Extract the original result size
    Matrix result(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = C_pad[i][j];

    return result;
}

// Helper function to print a matrix
void printMatrix(const Matrix &M) {
    for (auto &row : M) {
        for (int val : row)
            cout << val << " ";
        cout << "\n";
    }
}

int main() {
    // Example: 3x3 matrices (will be padded to 4x4 internally)
    Matrix A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    Matrix B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};

    if (A.size() != B.size()) {
        cout << "Matrices must be square and of same size.\n";
        return 0;
    }

    Matrix C = multiply(A, B, A.size());

    cout << "Result of Strassen Matrix Multiplication:\n";
    printMatrix(C);

    return 0;
}
