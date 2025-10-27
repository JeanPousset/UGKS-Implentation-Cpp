#ifndef MATRIX_H
#define MATRIX_H
#include <stdexcept>
#include <string>


class Matrix {
private:
    int rows; ///< number of rows
    int cols; ///< number of columns
    double *data; ///< "flat matrix" for contiguous memory
public:

    // CONSTRUCTORS

    /** @brief Initializes a matrix of size (n_rows, n_cols) */
    Matrix(int n_rows = 0, int n_cols = 0); // basic constructor

    /** @brief Initializes a matrix of size (n_rows, n_cols) filled with v_init values */
    Matrix(int n_rows, int n_cols, double v_init); // initializes every element to v_init

    /**
     * @brief copy constructor
     * @param mat
     */
    Matrix(const Matrix &mat);

    /**
     * @brief move constructor
     * @note used when returning a matrix
     * @param mat
     */
    Matrix(Matrix &&mat) noexcept;


    // DESTRUCTOR

    /** @brief Destructor for any matrix */
    ~Matrix();

    // OPERATORS

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

    /**
     * @brief Copy assignment for a matrix
     * @param mat right member of the equal
     * @return a deep copy of the right member (matrix)
     */
    Matrix &operator=(const Matrix &mat);

    /**
     * @brief semantic move
     * @param mat right member of the equal -> Its pointer will be assigned to nullpointer
     * @return matrix composed of the same data (pointer copy) of the right member
     */
    Matrix &operator=(Matrix &&mat) noexcept;



    // GETTERS

    /** @brief Returns number of rows of the matrix */
    int n_rows() const;

    /** @brief Returns number of columns of the matrix */
    int n_cols() const;


    // IO OPERATIONS

    /** @brief Display a matrix in its natural shape */
    void display() const;

    /**
     * @brief Write matrix data in a CSV file
     * @param filename name of the CSV file
     * @param delimiter by default : ','. Can also be ';' ' ' '\\t' '`' or ':'
     * @param precision default (0) set maximum precision so that no information is lost
     */
    void exportToCSV(const std::string &filename, char delimiter = ',', int precision = 0) const;


};


#endif //MATRIX_H
