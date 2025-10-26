#include "problem.h"
#include <cmath>
#include <iostream>


// --------------------- Basic evaluations ---------------------//

/// @note hypothesis : param A and C correspond to the same parameters set (δt,eta, ...)
double compute_A(double λ, double σ, double eta, double ε,  double dt) {
    const double w = λ * σ * dt / (eta * ε);
    return (exp(w) - 1.) / (eta * w);
}

double compute_C(double eta, double A) {
    return 1. / eta - A;
}

double compute_D(double λ, double σ, double eta, double ε, double dt, double A, double C) {
    const double w = λ * σ * dt / (eta * ε);
    return ε / (σ * λ) * (C - A) + ε * exp(w) / (eta * σ * λ);
}


// ----- Problem constructors -----
Problem::Problem(double σ, double eta, double ε, const Discretization &δ, std::unique_ptr<Collision> collision,
                 const std::function<double(double, double)> &f0,
                 const std::function<double(double)> &ρ0) : σ_(σ), eta_(eta), ε_(ε), δ_(δ), f0(f0), ρ0(ρ0) {
     collision_ = std::move(collision); // Need to move it to respect unique pointer proprieties
    A_ = compute_A(collision_->λ_star(), σ_, eta_, ε_, δ_.dt);
    C_ = compute_C(eta_, A_);
    D_ = compute_D(collision_->λ_star(), σ_, eta_, ε_, δ_.dt, A_, C_);
}

// ----- Discretization constructor and destructor -----

// Constructor


// ---------------- MEMBER FUNCTIONS ----------------

// (?6) : verify formula for the distribution update
//          F^n+1 - α*2kc(ρ_i^n*1 - F^n+1)
//          => F^n+1 = 1/(1-α*2kc) * (F^n -ρ_i^n+1 - ∆t/∆x(Φ_+1/2 - Φ_-1/2)

// (?7) : Must we store distributions for all times n, or we just need the current one


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
