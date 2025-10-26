#include "matrix.h"
#include <iostream>


// ------------ Constructors ------------

// Constructor that initializes a matrix of size (n_rown_rowss, n_cols) with v_init value
Matrix::Matrix(int n_rows, int n_cols) : rows(n_rows), cols(n_cols) {
    data = new double [n_rows * n_cols];
}

// Constructor that initializes a matrix of size (n_rown_rowss, n_cols) with v_init value
Matrix::Matrix(int n_row, int n_cols, double v_init) : Matrix(n_row, n_cols) {
    for (int i = 0; i < n_row * n_cols; i++) { data[i] = v_init; }
}

// Copy constructor
Matrix::Matrix(const Matrix &mat) {
    rows = mat.rows;
    cols = mat.cols;
    data = new double [rows * cols];
    for (int i = 0; i< rows * cols; i++) { data[i] = mat.data[i]; } // deep copy of the right data
}

// Move constructor
Matrix::Matrix(Matrix &&mat) noexcept {
    rows = mat.rows;
    cols = mat.cols;
    data = mat.data; // pointer copy
    mat.data = nullptr; // right matrix must not point to its old data
    mat.rows = 0;
    mat.cols = 0;
}

// Destructor for any matrix
Matrix::~Matrix() {
    delete[] data; // removes all element
}

// ------------ COPY functions ------------

// Copy assignment for a matrix
Matrix &Matrix::operator=(const Matrix &mat) {
    if (this != &mat) {
        delete[] data; // clean old data of our left (this) matrix
        rows = mat.rows;
        cols = mat.cols;
        data = new double [rows * cols];
        for (int i = 0; i< rows * cols; i++) { data[i] = mat.data[i]; } // deep copy of the right data
    }
    return *this;
}

// Move copy
Matrix &Matrix::operator=(Matrix &&mat) noexcept {
    if (this != &mat) {
        delete[] data;
        rows = mat.rows;
        cols = mat.cols;
        data = mat.data; // pointer copy of the right data
        mat.data = nullptr; // right matrix must not point to its old data
        mat.rows = 0;
        mat.cols = 0;
    }
    return *this;
}

// ------------ GETTERS ------------
/**
 * Returns matrix number of row
 */
int Matrix::n_rows() const {
    return rows;
}

/**
 * Returns matrix' number of row
 */
int Matrix::n_cols() const {
    return cols;
}

//
void Matrix::display() const {
    std::cout << "[(" << rows << "," << cols << ") matrix] :" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i * cols + j] << "\t";
        }
        std::cout << std::endl;
    }
}
