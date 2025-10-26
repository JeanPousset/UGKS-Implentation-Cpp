#include "solver.h"
#include <iostream>


Matrix solve(const Problem &pb, const Discretization &δ) {
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

    // Pre-compute coefficients
    const double A = compute_A(pb, δ.dt);
    const double C = compute_C(pb, δ.dt);
    const double D = compute_D(pb, δ.dt);


    // Solve for each time step
    for (int k = 0; k < δ.Nt - 1; ++k) {
        time_step(F, ρ[k + 1], Φ, φ, ρ[k], pb, δ, A, C, D);
        std::cout << "\t time step : " << k << "/" << δ.Nt << std::endl;
    }


    // Clean memory
    delete[] Φ;

    return ρ;
    // Move constructor is called to move ρ data into the matrix returned, then the destructor
    // is called on ρ that is now en empty matrix with a nullptr
}
