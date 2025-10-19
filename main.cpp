#include <iostream>
#include "matrix.h"

int main() {

    int n = 3, m = 4;
    Matrix empty_mat(n,m);
    Matrix one_mat(n,m,1.);
    empty_mat.display();
    one_mat.display();
    return 0;
}