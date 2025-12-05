#ifndef COLLISION_H
#define COLLISION_H


#include "matrix.hpp"
#include "discretization.hpp"

#include <string>


/** @note CONSTRUCTORS : Default constructors because these classes don't have any attributes
 *  -> necessary here because we don't declare other constructors.
 */

/**
 * @class Collision
 * @brief abstract class to handle various collision operators with polymorphism
 */
class Collision {
public:
    /** @brief default constructor */
    Collision() = default;

    /** @brief getter for star operator eigenvalue */
    inline virtual double λ_star() const = 0;

    /**
     * @brief Compute distribution at time n+1
     *
     * @param     F      distribution F_n to be updated into F_n+1
     * @param[in] φ      microscopic fluxes
     * @param[in] ρ_np1  densities at time n+1
     * @param[in] δ      discretization
     * @param[in] σ      collision characteristic frequency
     * @param[in] eta    coefficient in front of df/dt
     * @param[in] ε      diffusion behaviour coefficient (normalized mean free path)
     */
    virtual void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                                     double eta, double ε) const = 0;

    /** @brief default destructor */
    virtual ~Collision() = default;

    /** @brief Return the name of the derived class (useful for JSON problem export) */
    virtual std::string name() const = 0;
};

/**
 * @class BGK
 * @brief class for the BGK collision operators, inherits form @ref Collision
 */
class BGK final : public Collision {
public:
    /** @brief default constructor */
    BGK() = default;

    /** @brief override star eigenvalue getter @ref Collision::λ_star() */
    double λ_star() const override { return -1.; }

    /** @brief gives collision operator name, overrides @ref Collision::name() */
    std::string name() const override { return "BGK"; }

    /** @brief compute the distribution update (F) for the BGK operator, overrides @ref Collision::distribution_update */
    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                             double eta, double ε) const override;
};

/**
 * @class FockerPlank
 * @warning [TO DO !]
 */
class FockerPlank final : public Collision {
public:
    FockerPlank() = default;

    double λ_star() const override { return -2.; }
    std::string name() const override { return "FockerPlank"; }

    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ, double σ,
                             double eta, double ε) const override;
};

#endif //COLLISION_H
