#include "problem.h"
#include <cmath>

// ----- Problem constructors -----
Problem::Problem(double σ, double eta, double ε) : σ(σ), eta(eta), ε(ε) {
};

Pb_BGK::Pb_BGK(double σ, double eta, double ε) : Problem(σ, eta, ε) {
};

Pb_FockerPlank::Pb_FockerPlank(double σ, double eta, double ε) : Problem(σ, eta, ε) {
};


// ----- Discretization constructor and destructor -----

//
Discretization::Discretization(double dt, int N, double v_max, double L, int Nx) : dt(dt), N(N), L(L), Nx(Nx) {
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
double ρ_ex_transport(double t, double x, double v) {
};
