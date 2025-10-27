function rho = rho_exact_transport(x)
% Return exact value rho(x)
%   rho(x, t = 0.1) = ∫_{-1}^{1} exp(-((x - v*t) mod 1 - 0.5)^2 - 10*(1-v)^2) dv
%
%   decomposition depending of x intervals :
%   - [0, 0.1) : k = -1 and 0
%   - [0.1, 0.9] : k = 0
%   - (0.9, 1] : k = 0 and 1
% 
%   where (x-v*t) mod 1 = x-v*t-k

   t = 0.1;
    a = t^2 + 10;
    alpha = sqrt(a);
    sqrtpi = sqrt(pi);

    % analytic sub-functions
    erfpart = @(v_a, v_b, k) ...
        (sqrtpi/(2*alpha)) * exp(((-2*(x - k - 0.5)*t - 20)^2)/(4*a) - ((x - k - 0.5)^2 + 10)) * ...
        (erf(alpha*(v_b + ((-2*(x - k - 0.5)*t - 20)/(2*a)))) - ...
         erf(alpha*(v_a + ((-2*(x - k - 0.5)*t - 20)/(2*a)))));

    % Définition par morceaux selon x
    if x < 0.1
        rho = 0.5*(erfpart(-1, 10*x, 0) + erfpart(10*x, 1, -1));
    elseif x <= 0.9
        rho = 0.5*erfpart(-1, 1, 0);
    else
        rho = 0.5*(erfpart(-1, 10*(x-1), 1) + erfpart(10*(x-1), 1, 0));
    end
end
