#include "updates.h"
#include "evaluations.h"

void density_update(double *ρ, const double *Φ, const Discretization &δ) {
    for (int i = 0; i < δ.Nx; ++i) {
        ρ[i] = ρ[i] - δ.dt / δ.dx * (Φ[i + 1] - Φ[i]);
    }
    // special case for the last node with periodic boundary conditions:
    ρ[δ.Nx] = ρ[δ.Nx] - δ.dt / δ.dx * (Φ[0] - Φ[δ.Nx - 1]);
}



// [TO DO] : Do a function distribution update for each pb. Just change one parameter (!= signature)
//           So it allows polymorphism. (?5) -> Does it really ?