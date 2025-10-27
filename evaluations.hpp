#ifndef EVALUATIONS_H
#define EVALUATIONS_H

#include "problem.hpp"
#include "matrix.hpp"


/// @brief return the value of J_i^(-,n)
double J_i_m(const double *V, const double *F_n_i, int N);

/// @brief return the value of J_i^(+,n)
double J_i_p(const double *V, const double *F_n_i, int N);

/**
 * @brief Evaluate microscopic values Φ_i+1/2,j and macroscopic values φ_i+1/2 at interfaces (i in [1:Nx], j in [1:2N])
 *
 * @param φ matrix of microscopic interface values to evaluate
 * @param Φ Array of macroscopic interface values to evaluate
 * @param F Distribution matrix (for each space "node" i and each speed j) at time n
 * @param ρ Densities values (for each space node i in [1,Nx+1]) at time n
 * @param δ Discretization information
 * @param A coefficient A (pre-computed)
 * @param C coefficient C (pre-computed)
 * @param D coefficient D (pre-computed)
 */
void micro_macro_flux(Matrix &φ, double *Φ, const Matrix &F, const double *ρ, const Discretization &δ, double A,
                      double C, double D);

#endif //EVALUATIONS_H
