function rho = rho_exact_diffusion(t,x,sigma,l_star)
% Returns ρ exact values in the diffusion case for ρ0(t,x) = 2 + cos(2πx)

% Arguments : 
% - `t` : a column vector for time discretization
% - `x` : a row vector for space discretization
% - `sigma` : sigma parameter of the problem
% - `l_star` : pseudo eigenvalue

% Return : 
% - `rho` : discretization of the exact solution

    kappa = 1/(3*sigma*abs(l_star)); 
    rho = 2 + exp(-4*pi^2*kappa*t) .* cos(2*pi*x);
end
