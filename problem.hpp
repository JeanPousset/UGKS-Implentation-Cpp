#ifndef PROBLEM_H
#define PROBLEM_H

#include "collision.hpp"
#include "evaluations.hpp"

#include <functional>
#include <memory> // for unique pointers
#include <string>

class Pb_BGK;


/**
 * @struct Problem
 * @brief Parameters that defines a problem
 *
 * @warning function as a member is not optimized and create a cost at each call
 *          not a problem for us because problem functions are only called in problem
 *          initialization
 */
struct Problem {
    // Constants
    double σ_; ///< collision characteristic frequency
    double eta_; ///< coefficient in front of df/dt
    double ε_; ///< diffusion behaviour coefficient (normalized mean free path)
    double A_; ///< A(∆t,σ,η,ε) coefficient
    double C_; ///< C(∆t,σ,η,ε) coefficient
    double D_; ///< D(∆t,σ,η,ε) coefficient

    const Discretization &δ_; /**< Space, velocity and time discretization information -> reference to not make a copy
                                    that will create problem with the dynamic arrays */
    std::unique_ptr<Collision> collision_; ///< Pointer to an instance of a subclass of Collision (polymorphism)
    std::function<double(double, double)> f0; ///< Initial distribution
    std::function<double(double)> ρ0; ///< Initial density

    Problem(double σ, double eta, double ε, const Discretization &δ, std::unique_ptr<Collision> collision,
            const std::function<double(double, double)> &f0, const std::function<double(double)> &ρ0);

    /**
     * @brief exports problem data into a json file
     * @param json_name
     */
    void export_json(const std::string &json_name) const;

    /**
     * @brief Updates density vector ρ at time n+1 for each space node (x_i i in [[1,Nx+1]])
     * @param ρ_np1 densities at time n+1 (to be computed)
     * @param[in] ρ_n densities at time n
     * @param[in] Φ macroscopic fluxes
     */
    void density_update(double *ρ_np1, const double *ρ_n, const double *Φ) const;


    /**
     * @brief Computes problem variables (distribution F and densities ρ) at time n+1
     * @param     F distribution F_n to be updated into F_n+1
     * @param     ρ_np1 densities at time n+1
     * @param[in] Φ macroscopic fluxes
     * @param[in] φ microscopics fluxes
     * @param[in] ρ_n
     */
    void time_step(Matrix &F, double *ρ_np1, double *Φ, Matrix &φ, const double *ρ_n) const;

    /**
     * @brief Solves the diffusion / transport problem with UGKS
     * @return densities values for each time step t_k / space node x_i, (k,i) in [1,Nt]x[1,Nx+1]
     */
    Matrix solve() const;
};

constexpr double C_INT = 0.14; // example constant

#endif //PROBLEM_H
