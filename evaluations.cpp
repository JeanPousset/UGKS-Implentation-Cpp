#include "evaluations.hpp"

// J_i^(-,n)
double J_i_m(const double *V, const double *F_n_i, int N) {
    double res = 0.0;
    for (int i = 0; i < N; ++i) {
        res += V[i] * F_n_i[i];
    }
    return res / (2 * N);
}

// J_i^(+,n)
double J_i_p(const double *V, const double *F_n_i, int N) {
    double res = 0.0;
    for (int j = N + 1; j < 2 * N; ++j) {
        res += V[j] * F_n_i[j];
    }
    return res / (2 * N);
}

// ρ_i^(-,n)
double ρ_i_m(const double *F_n_i, int N) {
    double res = 0.0;
    for (int j = 0; j < N; ++j) {
        res += F_n_i[j];
    }
    return res / (2. * N);
}

// ρ_i^(+,n)
double ρ_i_p(const double *F_n_i, int N) {
    double res = 0.0;
    for (int j = N + 1; j < 2 * N; ++j) {
        res += F_n_i[j];
    }
    return res / (2. * N);
}

// --------------------- Interface evaluations ---------------------//



// Evaluate microscopic and macroscopic (avg) interface values φ_i+1/2,j for (i,j) in [1,Nx]x[1:2N] and Φ_i+1/2 for  i in [1,Nx]
void micro_macro_flux(Matrix &φ, double *Φ, const Matrix &F, const double *ρ, const Discretization &δ, double A,
                      double C, double D) {
    const int N = δ.N;
    double v = 0.;
    for (int i = 0; i < δ.Nx; ++i) {
        Φ[i] = 0.0; // reset macroscopic interface value Φ_i+1/2

        // case where v < 0 (take F^n_(i+1,j) instead of F^n(i,j))
        for (int j = 0; j < N; ++j) {
            v = δ.V[j];
            φ[i][j] = A * F[i + 1][j] * v + C * (ρ_i_p(F[i], N) + ρ_i_m(F[i + 1], N)) * v + D * v * v * (
                          ρ[i + 1] - ρ[i]) / δ.dx;
            Φ[i] += φ[i][j];
        }

        // case where v > 0 (take F^n_(i,j) instead of F^n(i+1,j))
        for (int j = N; j < 2 * N; ++j) {
            v = δ.V[j];
            φ[i][j] = A * F[i][j] * v + C * (ρ_i_p(F[i], N) + ρ_i_m(F[i + 1], N)) * v + D * v * v * (
                          ρ[i + 1] - ρ[i]) / δ.dx;
            Φ[i] += φ[i][j];
        }

        Φ[i] /= 2 * N; // divide at the end to get the average
    }
}
