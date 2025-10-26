#ifndef SOLVER_H
#define SOLVER_H

#include "evaluations.h"

/**
* @brief Updates density vector ρ at time n+1 for each space node (x_i i in [[1,Nx+1]])
 *
 * @param ρ_np1 density values p_i (i in [1,Nx+1]) at time n+1 to compute
 * @param ρ_n density values p_i (i in [1,Nx+1]) at time n
 * @param Φ macroscopic fluxes in space interfaces x_j+1/2 (i in [1,Nx])
 * @param δ information about time and space discretization
 */
void density_update(double *ρ_np1, const double *ρ_n, const double *Φ, const Discretization &δ);

/**
 * @brief Updates (with BKG formula) distribution matrix F at time n+1 for each space node (x_i i in [[1,Nx+1]]) and each
 *        velocity v_j (j in [[-N,N]])
 *
 * @param F distribution matrix F^n to be updated into F^n+1
 * @param φ microscopic fluxes in interfaces x_i+1/2,j  (i in [1,Nx], j in [-N,N])
 * @param ρ_np1 density values for each velocity v_j (j in [[-N,N]]) at time n+1 !
 * @param bgk constant of the BGK problem
 * @param δ information about time and space discretization
 */
void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Pb_BGK &bgk, const Discretization &δ);


// [TO DO] : documentation
void time_step(Matrix &F, double *ρ_np1, double *Φ, Matrix &φ, const double* ρ_n, const Problem &pb);


Matrix solve(const Problem &pb);



#endif //SOLVER_H
