#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>


class Matrix {
private:
    int rows; ///< number of rows
    int cols; ///< number of columns
    double *data; ///< "flat matrix" for contiguous memory
public:
    /** @brief Initializes a matrix of size (n_rows, n_cols) */
    Matrix(int n_rows = 0, int n_cols = 0); // basic constructor

    /** @brief Initializes a matrix of size (n_rows, n_cols) filled with v_init values */
    Matrix(int n_rows, int n_cols, double v_init); // initializes every element to v_init

    /**
     * @brief Access operator if we  want to update an element of the matrix
     * @note made it "inline" for performance purpose
     */
    double *operator[](int i) {
        if (i < 0 || i >= rows) {
            throw std::out_of_range("Matrix (hande made class) index out of range");
        }
        return data + i * cols; // Pointer on the 1st element of the i-th row
    }

    /**
     * @brief Access operator if we only want to read an element of the matrix
     * @note made it "inline" for performance purpose
     */
    const double *operator[](int i) const {
        if (i < 0 || i >= rows) {
            throw std::out_of_range("Matrix (hande made class) index out of range");
        }
        return data + i * cols; // Pointer on the 1st element of the i-th row
    }

    // Getters
    /** @brief Returns number of rows of the matrix */
    int n_rows() const;
    /** @brief Returns number of columns of the matrix */
    int n_cols() const;

    /** @brief Display a matrix in its natural shape */
    void display() const;

    /** @brief Destructor for any matrix */
    ~Matrix();
};


#endif //MATRIX_H
