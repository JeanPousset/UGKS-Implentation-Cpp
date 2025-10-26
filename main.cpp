#include <iostream>
#include <utility> // for move constructor / assignment tests
#include "matrix.h"
#include "solver.h"

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


using std::cout;
using std::endl;


int main() {


    // Problem definition
    auto ρ0 = [](double x) {return C_INT * exp(-(x - 0.5) * (x - 0.5));};
    auto f0 = [](double x, double v) {return exp(-(x - 0.5) * (x - 0.5) - 10. * (1. - v) * (1. - v));};
    constexpr double σ = 1., eta = 1., ε = 100.;
    const Pb_BGK bgk(σ,eta,ε,f0,ρ0);

    // Discretization
    constexpr double dt = 1e-5, Tf = 0.1;
    constexpr double v_max = 1.;
    constexpr int N = 50;
    constexpr double L = 1.;
    constexpr int Nx = 100;
    const Discretization δ(dt, Tf, N, v_max, L, Nx);

    const Matrix ρ = solve(bgk, δ);

    ρ.display();

    // Automatic clean memory for ρ at the end -> [TO DO] Check that

    return 0;
}


/*
 * Ideas :
 *   - make a new class Collision for the operator collision instead of problem.
 *      -> then create a class problem with at least two members : collision and discretization so it computes A,C,D and other coeffs
 *
 *   - Change N to Nv ? No Nv = 2N
 *
 *   - delete solver file and put its content in updates.cpp (name everything solver)
 *
 */


/*
 * Questions :
 *
 * - Do we include x = L into the space discretization because we already have x = 0 whith periodic condtions
 *
 *
 *
 *
 *
 *
 */