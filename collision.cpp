#include "collision.h"


// DISTRIBUTION UPDATES

// Updates (with BKG formula) distribution matrix F at time n+1 for each space node (x_i i in [[1,Nx+1]]) and each velocity v_j(j in [[-N,N]])
void BGK::distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ, double eta, double ε) const {
    // precomputed coefficients to avoid useless multiplication and divisions
    // -> the optimal way would be to compute these coef at the beginning of the solver, but it'll lose the genericity of the formulation
    const double K = σ * δ.dt / (ε * eta);
    const double coef = 1. / (1. + K);
    const double δ_ratio = δ.dt / δ.dx;

    // Special case for the first and last space nodes (x = 0, L) => periodic conditions
    for (int j = 0; j < 2 * δ.N; ++j) {
        F[0][j] = coef * (F[0][j] + K * ρ_np1[0] - δ_ratio * (φ[0][j] - φ[δ.Nx - 1][j]));
        F[δ.Nx][j] = F[0][j]; // Same value (periodic conditions)
    }
    // Other nodes
    for (int i = 1; i < δ.Nx; ++i) {
        for (int j = 0; j < 2 * δ.N; ++j) {
            F[i][j] = coef * (F[i][j] + K * ρ_np1[i] - δ_ratio * (φ[i][j] - φ[i-1][j]));
        }
    }
}

// [TO DO]
void FockerPlank::distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ, double eta, double ε) const {
}
