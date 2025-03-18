#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> matrix;

// Function to compute the next power of 2 greater than or equal to n
int nextPowerOfTwo(int n) {
    return pow(2, ceil(log2(n)));
}

// Function to pad a given matrix with zeros to size newSize x newSize
matrix addZeroes(matrix &m, int newSize) {
    int oldSize = m.size();
    matrix padded(newSize, vector<int>(newSize, 0));
    for (int i = 0; i < oldSize; i++) {
        for (int j = 0; j < m[0].size(); j++) {
            padded[i][j] = m[i][j];
        }
    }
    return padded;
}

// void padMatrix(matrix &m, int newSize) {
//     int origRows = m.size();
//     int origCols = m[0].size();
    
//     for (auto &row : m) {
//         row.resize(newSize, 0);
//     }
    
//     // If there are fewer rows than newSize, add new rows filled with zeros.
//     m.resize(newSize, vector<int>(newSize, 0));
// }

// Function to add two matrices
matrix add(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

// Function to subtract two matrices
matrix subtract(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

// The Strassen multiplication algorithm
matrix strassenMultiply(const matrix &A, const matrix &B) {
    int n = A.size();
    matrix C(n, vector<int>(n, 0));

    // Base case: single element matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Dividing matrices into quadrants
    int newSize = n / 2;
    matrix A11(newSize, vector<int>(newSize, 0));
    matrix A12(newSize, vector<int>(newSize, 0));
    matrix A21(newSize, vector<int>(newSize, 0));
    matrix A22(newSize, vector<int>(newSize, 0));
    matrix B11(newSize, vector<int>(newSize, 0));
    matrix B12(newSize, vector<int>(newSize, 0));
    matrix B21(newSize, vector<int>(newSize, 0));
    matrix B22(newSize, vector<int>(newSize, 0));

    for (int i = 0; i < newSize; i++) {
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
    }

    matrix m1 = strassenMultiply(add(A11, A22), add(B11, B22));
    matrix m2 = strassenMultiply(add(A21, A22), B11);
    matrix m3 = strassenMultiply(A11, subtract(B12, B22));
    matrix m4 = strassenMultiply(A22, subtract(B21, B11));
    matrix m5 = strassenMultiply(add(A11, A12), B22);
    matrix m6 = strassenMultiply(subtract(A21, A11), add(B11, B12));
    matrix m7 = strassenMultiply(subtract(A12, A22), add(B21, B22));

    matrix C11 = add(subtract(add(m1, m4), m5), m7);
    matrix C12 = add(m3, m5);
    matrix C21 = add(m2, m4);
    matrix C22 = add(subtract(add(m1, m3), m2), m6);

    // Combining the 4 quadrants into a single matrix
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
    return C;
}

// Remove padding from the result matrix, returning the original size (r x c)
matrix unpadMatrix(const matrix &m, int r, int c) {
    matrix result(r, vector<int>(c, 0));
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            result[i][j] = m[i][j];
    return result;
}

void printmatrix(const matrix &m) {
    for (auto &row : m) {
        for (auto val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    matrix A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    matrix B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}};

    int origSize = A.size();
    int newSize = nextPowerOfTwo(origSize);

    matrix A_padded = addZeroes(A, newSize);
    matrix B_padded = addZeroes(B, newSize);

    matrix C_padded = strassenMultiply(A_padded, B_padded);

    matrix C = unpadMatrix(C_padded, origSize, origSize);

    cout << "matrix A:" << endl;
    printmatrix(A);
    cout << "\nmatrix B:" << endl;
    printmatrix(B);
    cout << "\nProduct (A x B) using Strassen's algorithm:" << endl;
    printmatrix(C);

    return 0;
}
