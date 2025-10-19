#include "evaluations.h"
#include <cmath>


// (?2) : Is it ok to use the class as parameter or it creates too
// much indirect accesses and it'd be better to use direct values as parameters


// --------------------- Basic evaluations ---------------------//
double A(const Problem &pb, double dt) {
    const double w = pb.λ_star() * pb.σ * dt / (pb.eta * pb.ε);
    return (exp(w) - 1.) / (pb.eta * w);
}

double C(const Problem &pb, double dt) {
    return 1. / pb.eta - A(pb, dt);
}

double D(const Problem &pb, double dt) {
    const double w = pb.λ_star() * pb.σ * dt / (pb.eta * pb.ε);
    return pb.ε / (pb.σ * pb.λ_star()) * (C(pb, dt) - A(pb, dt)) + pb.ε * exp(w) / (pb.eta * pb.σ * pb.λ_star());
}

// [TO DO] : Formulate this into a mat / vector product to speed up (using Blas) -> adapt other function in consequences
// J_i^(-,n)
double J_i_m(const double *V, const double *F_n_i, int N) {
    double res = 0.0;
    for (int i = 0; i < N; ++i) {
        res += V[i] * F_n_i[i];
    }
    return res / (2 * N);
}

// J_i^(-,+)
double J_i_p(const double *V, const double *F_n_i, int N) {
    double res = 0.0;
    for (int j = N + 1; j < 2 * N; ++j) {
        res += V[j] * F_n_i[j];
    }
    return res / (2 * N);
}

double ρ_i_m(const double *F_n_i, int N) {
    double res = 0.0;
    for (int i = 0; i < N; ++i) {
        res += F_n_i[i];
    }
    return res / (2 * N);
}

// J_i^(-,+)
double ρ_i_p(const double *F_n_i, int N) {
    double res = 0.0;
    for (int j = N + 1; j < 2 * N; ++j) {
        res += F_n_i[j];
    }
    return res / (2 * N);
}

// --------------------- Interface evaluations ---------------------//

// Evaluate microscopic interface values Φ_i+1/2,j for (i,j) in [1,Nx]x[1:2N]
// (?4) : Should param φ be a reference ?
void microscopic_flux(Matrix &φ, const Matrix &F, const double *ρ, double A, double C, double D,
                      const Discretization &δ) {
    const int N = δ.N;
    double v = 0;
    for (int i = 0; i < δ.Nx; ++i) {
        // case where v < 0 (take F^n_(i+1,j) instead of F^n(i,j))
        for (int j = 0; j < N; ++j) {
            v = δ.V[j];
            φ[i][j] = A * F[i + 1][j] * v + C * (ρ_i_p(F[i], N) + ρ_i_m(F[i + 1], N)) * v + D * v * v * (
                          ρ[i + 1] - ρ[i]) / δ.dx;
        }
        // case where v > 0 (take F^n_(i,j) instead of F^n(i+1,j))
        for (int j = N; j < 2*N; ++j) {
            v = δ.V[j];
            φ[i][j] = A * F[i][j] * v + C * (ρ_i_p(F[i], N) + ρ_i_m(F[i + 1], N)) * v + D * v * v * (
                          ρ[i + 1] - ρ[i]) / δ.dx;
        }
    }
}

// Evaluate macroscopic interface values Φ_i+1/2 for i in [1:Nx]
void macroscopic_flux(double *Φ, const double *V, const Matrix &F_n, const double *ρ_n, const Problem &pb,
                      const Discretization &δ) {
    const int N = δ.N;
    for (int i = 0; i < δ.Nx; ++i) {
        Φ[i] = A(pb, δ.dt) * (J_i_m(V, F_n[i], N) + J_i_p(V, F_n[i], N)) + D(pb, δ.dt) * (ρ_n[i + 1] - ρ_n[i]) *
               δ.normV2 / (2 * N * δ.dx);
    }
}
