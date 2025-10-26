#include "problem.h"
#include <cmath>
#include <fstream>


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


// -------- CONSTRUCTOR --------
Problem::Problem(double σ, double eta, double ε, const Discretization &δ, std::unique_ptr<Collision> collision,
                 const std::function<double(double, double)> &f0,
                 const std::function<double(double)> &ρ0) : σ_(σ), eta_(eta), ε_(ε), δ_(δ), f0(f0), ρ0(ρ0) {
     collision_ = std::move(collision); // Need to move it to respect unique pointer proprieties
    A_ = compute_A(collision_->λ_star(), σ_, eta_, ε_, δ_.dt);
    C_ = compute_C(eta_, A_);
    D_ = compute_D(collision_->λ_star(), σ_, eta_, ε_, δ_.dt, A_, C_);
}

void Problem::export_json(const std::string &json_name) const {

    // build json
    json j = δ_.to_json();  // includes discretization data
    j["σ"] = σ_;
    j["eta"] = eta_;
    j["ε"] = ε_;
    j["Collision"] = collision_->name();

    std::ofstream file(json_name);
    file << std::setw(4) << j; // use json.hpp operator overload with 4 space for indentation
    std::cout << "==> " << json_name << " successfully exported" << std::endl;

    file.close();
}