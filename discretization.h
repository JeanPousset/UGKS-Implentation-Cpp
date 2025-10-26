#ifndef DISCRETIZATION_H
#define DISCRETIZATION_H

#include <stdexcept>
#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json; // for easy json handle


// [TO DO]: delete normV2 because I think we no longer need it

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
    inline Discretization(double dt, double Tf, int N, double v_max, double L, int Nx);

    inline json to_json() const;

    inline ~Discretization();
};

Discretization::Discretization(double dt, double Tf, int N, double v_max, double L,
                               int Nx) : dt(dt), N(N), L(L), Nx(Nx) {
    // Time discretization
    const double Nt_tmp = Tf / dt;
    if (std::abs(Nt_tmp - std::round(Nt_tmp)) > 1e-12) {
        // check if Tf is divisible by dt (allow error because of numeric encoding of fload)
        std::cout << "mod(" << Tf << "," << dt << ") = " << std::fmod(Tf, dt) << std::endl;
        throw std::invalid_argument("Error in discretization : please choose a final time Tf divisible by dt");
    }
    Nt = static_cast<int>(Nt_tmp);
    // Linear discretization of the (symmetric) velocity domain [-v_max, v_max]
    // -> it's made so to optimize the number of multiplication / division performed
    V = new double[2 * N];
    double v = 0.;
    const double dv = v_max / N;
    normV2 = 0.;
    for (int i = 0; i < N; ++i) {
        v = i * dv;
        V[i] = -v;
        V[N + i] = v;
        normV2 += v * v;
    }

    // Linear discretization of the space domain
    X = new double[Nx+1];
    dx = L / Nx; // Here the number of space node is Nx+1
    for (int i = 0; i < Nx + 1; ++i) { X[i] = dx * i; }
}

json Discretization::to_json() const {
    json j;
    j["dt"] = dt;
    j["Nt"] = Nt;
    j["N"] = N;
    j["normV2"] = normV2;
    j["L"] = L;
    j["Nx"] = Nx;
    j["dx"] = dx;

    // Export arrays as std::vector for JSON
    j["V"] = std::vector<double>(V, V + 2 * N);
    j["X"] = std::vector<double>(X, X + Nx + 1);

    return j;
}

/// Delete the velocity and space arrays (dynamically allocated)
Discretization::~Discretization() {
    delete[] V;
    delete[] X;
}

#endif //DISCRETIZATION_H
