#ifndef COLLISION_H
#define COLLISION_H


#include "matrix.h"
#include "discretization.h"


/** @note CONSTRUCTORS : Default constructors because these classes don't have any attributes
 *  -> note necessary here because we don't declare other constructors.
 */

// [TO DO] Document these classes and member functions

class Collision {
public:
    Collision() = default;

    inline virtual double λ_star() const = 0;

    virtual void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                                     double eta, double ε) const = 0;

    virtual ~Collision() = default;
};

class BGK final : public Collision {
public:
    BGK() = default;

    double λ_star() const override { return -1.; }

    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                             double eta, double ε) const override;
};

class FockerPlank final : public Collision {
public:
    FockerPlank() = default;

    double λ_star() const override { return -2.; }

    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                             double eta, double ε) const override;
};

#endif //COLLISION_H
