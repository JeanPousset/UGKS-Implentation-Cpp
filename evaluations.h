#ifndef EVALUATIONS_H
#define EVALUATIONS_H

#include "problem.h"
#include "matrix.h"



double A(const Problem& pb);//A(double δt,double σ,double eta, double ε);
double C(const Problem& pb);//A(double δt,double σ,double eta, double ε);
double D(const Problem& pb);//A(double δt,double σ,double eta, double ε);

/// @brief return the value of J_i^(-,n)
double J_i_m(const double* V, const double* F_n_i, int N);

/// @brief return the value of J_i^(+,n)
double J_i_p(const double* V, const double* F_n_i, int N);

/**
 * @brief Evaluate macroscopic interface values Φ_i+1/2 for i in [1:2N-1]
 *
 * @param Φ Array of macroscopic interface values to evaluate
 * @param V Speed discretization array
 * @param F_n Distribution matrix (for each cell i and each speed j) at time n
 * @param ρ_n Densities array (for each cell) at time n
 * @param pb Problem settings
 * @param δ Discretization information
 */
void macroscopic_flux(double* Φ, const double *V, const Matrix& F_n, const double* ρ_n, const Problem& pb, const Discretization& δ);


#endif //EVALUATIONS_H
