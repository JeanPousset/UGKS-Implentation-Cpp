#include "solver.h"
#include <iostream>


// Updates density vector ρ at time n+1 for each space node (x_i i in [[1,Nx+1]])
void density_update(double *ρ_np1, const double *ρ_n, const double *Φ, const Discretization &δ) {
    const double δ_ratio = δ.dt / δ.dx;
    // special case for the first and last nodes (x = 0, L) with periodic boundary conditions
    ρ_np1[0] = ρ_n[δ.Nx] - δ_ratio * (Φ[0] - Φ[δ.Nx - 1]);
    ρ_np1[δ.Nx] = ρ_np1[0];
    for (int i = 1; i < δ.Nx; ++i) {
        ρ_np1[i] = ρ_n[i] - δ_ratio * (Φ[i] - Φ[i-1]);
    }
}


// [TO DO] : Do a function distribution update for each pb. Just change one parameter (!= signature)
//           So it allows polymorphism. (?5) -> Does it really ?


void time_step(Matrix &F, double *ρ_np1, double *Φ, Matrix &φ, const double *ρ_n, const Problem &pb) {
    // compute flux :
    micro_macro_flux(φ, Φ, F, ρ_n, pb.δ_, pb.A_, pb.C_, pb.D_);

    // density update
    density_update(ρ_np1, ρ_n, Φ, pb.δ_);

    // distribution update
    pb.collision_->distribution_update(F, φ, ρ_np1, pb.δ_, pb.σ_, pb.eta_, pb.ε_);
}


Matrix solve(const Problem &pb) {

    const Discretization &δ = pb.δ_; // Simple reference for easier reading
    // Dynamic allocation
    Matrix F(δ.Nx + 1, 2 * δ.N); // Distribution at time n
    double *Φ = new double[δ.Nx];
    Matrix φ(δ.Nx, 2 * δ.N);
    Matrix ρ(δ.Nt, δ.Nx + 1); /// @warning must be deleted when return

    //  Distribution and density initializations based on problem data
    for (int i = 0; i < δ.Nx + 1; i++) {
        ρ[0][i] = pb.ρ0(δ.X[i]); // density initialization
        for (int j = 0; j < 2 * δ.N; ++j) {
            F[i][j] = pb.f0(δ.X[i], δ.V[j]); // distribution initialization
        }
    }

    // Solve for each time step
    for (int k = 0; k < δ.Nt - 1; ++k) {
        time_step(F, ρ[k + 1], Φ, φ, ρ[k], pb);

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
