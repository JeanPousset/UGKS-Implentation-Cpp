#include <iostream>
#include "problem.hpp"
#include "tests.hpp"



using std::cout, std::endl;


int main() {

    transport_test("Results/ρ_transport.csv","Results/pb_transport.json");

    diffusion_test("Results/ρ_diffusion.csv","Results/pb_diffusion.json");

    return 0;
}

/*
// [OLD] Matrix constructor and assignments (copy and move) tests
const int n = 3, m = 4;
Matrix empty_mat(n, m);
Matrix one_mat(n, m, 1.);
const Matrix two_mat(n, m, 2.);


Matrix test_copy_constructor(empty_mat);

Matrix test_move_constructor = std::move(two_mat);

cout << "Empty matrix copy constructor:" << endl;
test_copy_constructor.display();

cout << "One matrix move constructor:" << endl;
test_move_constructor.display();
one_mat.display();

cout << "Two matrix const move assignement (copy):" << endl;
Matrix test_copy_assignment_const(one_mat);
test_copy_assignment_const = std::move(two_mat);  // carefull here copy assignment is called and not move assignment
test_copy_assignment_const.display();

cout << "One matrix const move assignement (copy):" << endl;
Matrix test_copy_assignment(empty_mat);
test_copy_assignment = std::move(one_mat);  // carefull here copy assignment is called and not move assignment
test_copy_assignment.display();
one_mat.display();

*/