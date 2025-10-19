#ifndef PROBLEM_H
#define PROBLEM_H

/**
 * Parameters that defines a problem
 */
class Problem {
public:
    double σ;
    double eta;
    double ε;
    Problem(double σ, double eta, double ε);
    inline virtual double λ_star() const = 0 ;
    // inline to avoid cost due to call function each time we want the value of λ star
    virtual ~Problem() = default; // Must define it virtual in case of an abstract class
};



class Pb_BGK : public Problem {
public:
    Pb_BGK(double σ, double eta, double ε);
    double λ_star() const override {return -1.;}
};


class Pb_FockerPlank : public Problem {
public:
    Pb_FockerPlank(double σ, double eta, double ε);
    double λ_star() const override {return -2.;}

};

// (?3) Is the vector X useless -> if so delete it
/**
 * @Brief Gather information about time, space and velocity discretizations
 */
struct Discretization {
    double dt; ///< time step.
    int N; ///< half of discretization points number for the velocity domain [-v_max,+v_max].
    double* V; ///< array of discrete velocities.
    double normV2; ///< square of V's euclidian norm.
    double L; ///< length of the space domain.
    int Nx; ///< number of cells @warning here the number of space node is Nx+1 !
    double dx; ///< ∆x.
    double* X; ///< nodes of the spacial discretization

    /**
     * @brief Build and store the velocities and space domain + the time step
     *
     * @param dt ∆t
     * @param N ∆x
     * @param v_max maximum values of velocity (upper and -lower bound of the velocity domain)
     * @param L Length of the space domain [0,1]
     * @param Nx number of cells
     * @warning here the number of space node is Nx+1 !
     */
    Discretization(double dt, int N, double v_max, double L, int Nx);
    ~Discretization();
};


constexpr double C_INT = 0.14; // (1?) : do I need a more precise approximation

double f0(double x, double v); /// Initial distribution
double ρ0(double x); /// Initial density

double f_ex_transport(double t, double x, double v); /// Exact distribution for the transport problem
double ρ_ex_transport(double t, double x); /// Exact density for the transport problem
#endif //PROBLEM_H
