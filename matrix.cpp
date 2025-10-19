#include "matrix.h"
#include <iostream>

/**
 * Initializes a matrix of size (n_rows, n_cols)
 */
Matrix::Matrix(int n_rows, int n_cols) : rows(n_rows), cols(n_cols) {
    data = new double [n_rows*n_cols];
}


Matrix::Matrix(int n_row, int n_cols, double v_init) : Matrix(n_row, n_cols) {
    for (int i=0; i<n_row*n_cols; i++) {data[i] = v_init;}
}

// Destructor for any matrix
Matrix::~Matrix() {
    delete[] data; // removes all element
}

/**
 * Display a matrix
 */
void Matrix::display() const{
    std::cout<<"[("<<rows<<","<<cols<<") matrix] :"<<std::endl;
    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            std::cout<<data[i*cols+j]<<"\t";
        }
        std::cout << std::endl;
    }
}
// ----- Getters ----
/**
 * Returns matrix' number of row
 */
int Matrix::n_rows() const{
    return rows;
}

/**
 * Returns matrix' number of row
 */
int Matrix::n_cols() const {
    return cols;
}
