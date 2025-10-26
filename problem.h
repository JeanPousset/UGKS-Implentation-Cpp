#ifndef PROBLEM_H
#define PROBLEM_H

#include "collision.h"

#include <functional>
#include <memory> // for unique pointers
#include <string>

class Pb_BGK;


/**
 * @brief Parameters that defines a problem
 *
 * @warning function as a member is not optimized and create a cost at each call
 *          not a problem for us because problem functions are only called in problem
 *          initialization
 */
struct Problem {
    // Constants
    double σ_;
    double eta_;
    double ε_;
    double A_;
    double C_;
    double D_;

    const Discretization &δ_; /**< Space, velocity and time discretization information -> reference to not make a copy
                                    that will create problem with the dynamic arrays */
    std::unique_ptr<Collision> collision_; ///< Pointer to an instance of a subclass of Collision (polymorphism)
    std::function<double(double, double)> f0; ///< Initial distribution
    std::function<double(double)> ρ0; ///< Initial density

    Problem(double σ, double eta, double ε, const Discretization &δ, std::unique_ptr<Collision> collision,
            const std::function<double(double, double)> &f0, const std::function<double(double)> &ρ0);

    void export_json(const std::string &json_name) const;
};


constexpr double C_INT = 0.14; // (1?) : do I need a more precise approximation


double f_ex_transport(double t, double x, double v); /// Exact distribution for the transport problem
// double ρ_ex_transport(double t, double x); /// Exact density for the transport problem
#endif //PROBLEM_H
