#include "updates.h"


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


void time_step(Matrix &F, double *ρ_np1, double *Φ, Matrix &φ, const double *ρ_n, const Problem &pb,
               const Discretization &δ, double A, double C, double D) {
    // compute flux :
    micro_macro_flux(φ, Φ, F, ρ_n, δ, A, C, D);

    // density update
    density_update(ρ_np1, ρ_n, Φ, δ);

    // distribution update
    pb.distribution_update(F, φ, ρ_np1, δ);
}
