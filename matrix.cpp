#include "matrix.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>  // for std::setprecision

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
    for (int i = 0; i < rows * cols; i++) { data[i] = mat.data[i]; } // deep copy of the right data
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
        for (int i = 0; i < rows * cols; i++) { data[i] = mat.data[i]; } // deep copy of the right data
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

//Returns matrix number of row
int Matrix::n_rows() const {
    return rows;
}

// Returns matrix' number of row
int Matrix::n_cols() const {
    return cols;
}


// IO OPERATIONS

// Display a matrix in its natural shape
void Matrix::display() const {
    std::cout << "[(" << rows << "," << cols << ") matrix] :" << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << data[i * cols + j] << "\t";
        }
        std::cout << std::endl;
    }
}

// write a matrix in a CSV file
void Matrix::exportToCSV(const std::string &filename, char delimiter, int precision) const {

    // Open file in read mode (delete its previous content)
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("[Matrix::exportToCSV] Error : can't open file " + filename);
    }

    if (precision == 0) {
        // default precision is set to have the exact data
        file << std::setprecision(std::numeric_limits<double>::max_digits10);
    } else {
        file << std::setprecision(precision);
    }
    // write matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols - 1; ++j) {
            file << data[i * cols + j];
            file << delimiter;
        }
        // special case : no delimiter at the end
        file << data[i * cols + cols - 1];
        file << "\n"; // new row
    }

    file.close();
    std::cout << "==> " << filename << " successfully exported" << std::endl;
}
