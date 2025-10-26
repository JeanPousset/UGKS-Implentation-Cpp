#include "problem.h"
#include <cmath>
#include <iostream>
#include <stdexcept>


// ----- Problem constructors -----
Problem::Problem(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
                 const std::function<double(double)> &ρ0) : σ(σ), eta(eta), ε(ε), f0(f0), ρ0(ρ0) {
};

Pb_BGK::Pb_BGK(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
               const std::function<double(double)> &ρ0) : Problem(σ, eta, ε, f0, ρ0) {
};

Pb_FockerPlank::Pb_FockerPlank(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
                               const std::function<double(double)> &ρ0) : Problem(σ, eta, ε, f0, ρ0) {
};


// ----- Discretization constructor and destructor -----

// Constructor
Discretization::Discretization(double dt, double Tf, int N, double v_max, double L,
                               int Nx) : dt(dt), N(N), L(L), Nx(Nx) {
    // Time discretization
    const double Nt_tmp = Tf / dt;
    if (std::abs(Nt_tmp - std::round(Nt_tmp)) > 1e-12) {
        // check if Tf is divisible by dt (allow error because of numeric encoding of fload)
        std::cout << "mod(" << Tf << "," << dt << ") = " << std::fmod(Tf, dt) << std::endl;
        throw std::invalid_argument("Error in discretization : please choose a final time Tf divisible by dt");
    }
    Nt = static_cast<int>(Nt_tmp);
    // Linear discretization of the (symmetric) velocity domain [-v_max, v_max]
    // -> it's made so to optimize the number of multiplication / division performed
    V = new double[2 * N];
    double v = 0.;
    const double dv = v_max / N;
    normV2 = 0.;
    for (int i = 0; i < N; ++i) {
        v = i * dv;
        V[i] = -v;
        V[N + i] = v;
        normV2 += v * v;
    }

    // Linear discretization of the space domain
    X = new double[Nx];
    dx = L / Nx; // Here the number of space node is Nx+1
    for (int i = 0; i < Nx + 1; ++i) { X[i] = dx * i; }
}

/// Delete the velocity and space arrays (dynamically allocated)
Discretization::~Discretization() {
    delete[] V;
    delete[] X;
}

// ---------------- MEMBER FUNCTIONS ----------------

// (?6) : verify formula for the distribution update
//          F^n+1 - α*2kc(ρ_i^n*1 - F^n+1)
//          => F^n+1 = 1/(1-α*2kc) * (F^n -ρ_i^n+1 - ∆t/∆x(Φ_+1/2 - Φ_-1/2)

// (?7) : Must we store distributions for all times n, or we just need the current one

// Updates (with BKG formula) distribution matrix F at time n+1 for each space node (x_i i in [[1,Nx+1]]) and each velocity v_j(j in [[-N,N]])
void Pb_BGK::distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ) const {
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
void Pb_FockerPlank::distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1,
                                         const Discretization &δ) const {
}


// ----- Problem functions -----

double f0(double x, double v) {
    return exp(-(x - 0.5) * (x - 0.5) - 10 * (1 - v) * (1 - v));
}

double ρ0(double x) {
    return C_INT * exp(-(x - 0.5) * (x - 0.5));
}

double f_ex_transport(double t, double x, double v) {
    return f0(std::fmod(x - v * t, 1.0), v);
}

// [TO DO] : implement approximation for exact density solution
//double ρ_ex_transport(double t, double x, double v) {};
