#ifndef PROBLEM_H
#define PROBLEM_H

#include <functional>
#include "matrix.h"

class Pb_BGK;
// (?3) Is the vector X useless -> if so delete it -> not really
/**
 * @brief Gather information about time, space and velocity discretizations
 */
struct Discretization {
    double dt; ///< time step.
    int Nt; ///< number of time step
    double *V; ///< array of discrete velocities.
    int N; ///< half of discretization points number for the velocity domain [-v_max,+v_max].
    double normV2; ///< square of V's euclidian norm.
    double L; ///< length of the space domain.
    int Nx; ///< number of cells @warning here the number of space node is Nx+1 !
    double dx; ///< ∆x.
    double *X; ///< nodes of the spacial discretization

    /**
     * @brief Build and store the velocities and space domain + the time step
     *
     * @param dt ∆t
     * @param Tf final time of resolution
     * @param N ∆x
     * @param v_max maximum values of velocity (upper and -lower bound of the velocity domain)
     * @param L Length of the space domain [0,1]
     * @param Nx number of cells
     * @warning here the number of space node is Nx+1 !
     */
    Discretization(double dt, double Tf, int N, double v_max, double L, int Nx);

    ~Discretization();
};


/**
 * @brief Parameters that defines a problem
 *
 * @warning function as a member is not optimized and create a cost at each call
 *          not a problem for us because problem functions are only called in problem
 *          initialization
 */
class Problem {
public:
    // Attributes
    double σ;
    double eta;
    double ε;
    std::function<double(double, double)> f0; ///< Initial distribution
    std::function<double(double)> ρ0; ///< Initial density

    Problem(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
            const std::function<double(double)> &ρ0);

    virtual void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ) const =
    0;


    inline virtual double λ_star() const = 0;

    /// @note inline to avoid cost due to call function each time we want the value of λ star
    virtual ~Problem() = default; /// @note Must define it virtual in case of an abstract class
};


class Pb_BGK final : public Problem {
public:
    Pb_BGK(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
           const std::function<double(double)> &ρ0);

    double λ_star() const override { return -1.; }

    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ) const override;
};


class Pb_FockerPlank final : public Problem {
public:
    Pb_FockerPlank(double σ, double eta, double ε, const std::function<double(double, double)> &f0,
                   const std::function<double(double)> &ρ0);

    double λ_star() const override { return -2.; }

    void distribution_update(Matrix &F, const Matrix &φ, const double *ρ_np1, const Discretization &δ) const override;
};


constexpr double C_INT = 0.14; // (1?) : do I need a more precise approximation


double f_ex_transport(double t, double x, double v); /// Exact distribution for the transport problem
// double ρ_ex_transport(double t, double x); /// Exact density for the transport problem
#endif //PROBLEM_H
