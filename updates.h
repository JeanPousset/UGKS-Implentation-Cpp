#ifndef UPDATES_H
#define UPDATES_H

#include "problem.h"

// [TO DO] : precise length  of Φ and ρ
void density_update(double *ρ, const double *Φ, const Discretization &δ);
#endif //UPDATES_H


void distribution_update(double *F_i, const double *ρ, const Problem &pb, const Discretization &δ);
