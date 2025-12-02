#include "problem.hpp"

#include <cmath>
#include <utility> // for move constructor / assignment tests

void transport_test(const std::string &csv_path, const std::string &json_path) {
    // Discretization
    constexpr double dt = 1e-5, Tf = 0.1;
    constexpr double v_max = 1.;
    constexpr int N = 50;
    constexpr double L = 1.;
    constexpr int Nx = 100;
    const Discretization δ(dt, Tf, N, v_max, L, Nx);

    // Collision (unique Collision ptr for polymorphism)
    std::unique_ptr<Collision> collision_ptr = std::make_unique<BGK>();

    // Problem definition
    auto ρ0 = [](double x) {return C_INT * exp(-(x - 0.5) * (x - 0.5));};
    auto f0 = [](double x, double v) {return exp(-(x - 0.5) * (x - 0.5) - 10. * (1. - v) * (1. - v));};
    constexpr double σ = 1., eta = 1., ε = 100.;
    const Problem pb(σ,eta,ε, δ, (std::move(collision_ptr)), f0,ρ0);


    const Matrix ρ = pb.solve();

    // Save results
    ρ.exportToCSV(csv_path);
    pb.export_json(json_path);
}

void diffusion_test(const std::string &csv_path, const std::string &json_path) {
    // Discretization
    constexpr double dt = 1e-5, Tf = 0.1;
    constexpr double v_max = 1.;
    constexpr int N = 50;
    constexpr double L = 1.;
    constexpr int Nx = 100;
    const Discretization δ(dt, Tf, N, v_max, L, Nx);

    // Collision (unique Collision ptr for polymorphism)
    std::unique_ptr<Collision> collision_ptr = std::make_unique<BGK>();

    // Problem definition
    auto ρ0 = [](double x) {return 2+cos(2*M_PI*x);};
    auto f0 = [](double x, double v) {return 2+cos(2*M_PI*x);};
    constexpr double σ = 1., eta = 1e-4, ε = 1e-4;
    const Problem pb(σ,eta,ε, δ, (std::move(collision_ptr)), f0,ρ0);
    const Matrix ρ = pb.solve();

    // Save results
    ρ.exportToCSV(csv_path);
    pb.export_json(json_path);
}
