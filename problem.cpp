#include "problem.hpp"
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


// -------- METHODS --------


// Updates density vector ρ at time n+1 for each space node (x_i i in [[1,Nx+1]])
void Problem::density_update(double *ρ_np1, const double *ρ_n, const double *Φ) const {
    const double δ_ratio = δ_.dt / δ_.dx;
    // special case for the first and last nodes (x = 0, L) with periodic boundary conditions
    ρ_np1[0] = ρ_n[δ_.Nx] - δ_ratio * (Φ[0] - Φ[δ_.Nx - 1]);
    ρ_np1[δ_.Nx] = ρ_np1[0];
    for (int i = 1; i < δ_.Nx; ++i) {
        ρ_np1[i] = ρ_n[i] - δ_ratio * (Φ[i] - Φ[i-1]);
    }
}


void Problem::time_step(Matrix &F, double *ρ_np1, double *Φ, Matrix &φ, const double *ρ_n) const {
    // compute flux :
    micro_macro_flux(φ, Φ, F, ρ_n, δ_, A_, C_, D_);

    // density update
    this->density_update(ρ_np1, ρ_n, Φ);

    // distribution update
    collision_->distribution_update(F, φ, ρ_np1, δ_, σ_, eta_, ε_);
}


Matrix Problem::solve() const {
    const Discretization &δ = δ_; // Simple reference for easier reading
    // Dynamic allocation
    Matrix F(δ.Nx + 1, 2 * δ.N); // Distribution at time n
    double *Φ = new double[δ.Nx];
    Matrix φ(δ.Nx, 2 * δ.N);
    Matrix ρ(δ.Nt, δ.Nx + 1); /// @warning must be deleted when return

    //  Distribution and density initializations based on problem data
    for (int i = 0; i < δ.Nx + 1; i++) {
        ρ[0][i] = ρ0(δ.X[i]); // density initialization
        for (int j = 0; j < 2 * δ.N; ++j) {
            F[i][j] = f0(δ.X[i], δ.V[j]); // distribution initialization
        }
    }

    // Solve for each time step
    for (int k = 0; k < δ.Nt - 1; ++k) {
        this->time_step(F, ρ[k + 1], Φ, φ, ρ[k]);

        if (k % 1000 == 0) {
            std::cout << "\t time step : " << k << "/" << δ.Nt << std::endl;
        }
    }

    // Clean memory
    delete[] Φ;

    return ρ;
    // Move constructor is called to move ρ data into the matrix returned, then the destructor
    // is called on ρ that is now en empty matrix with a nullptr
}