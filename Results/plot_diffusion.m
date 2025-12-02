%% Difffusion

% Import results
pb = read_json("pb_diffusion.json");
rho = read_CSV_matrix("ρ_diffusion.csv");
sigma = pb.sigma;
l_star = -1;


% exact solution 
t = linspace(0,pb.Nt*pb.dt,pb.Nt)';
x = linspace(pb.X(1),pb.X(end),400); % here we take more than Nx to get a clean curve
rho_diff = rho_exact_diffusion(t,x,sigma,l_star); % exact solution


% graphic parameters
ms = 8; % marker size
fs = 20; % font size

figure(2); hold on

plot(x,rho_diff(1,:), "g--.", 'LineWidth', 1)
plot(pb.X, rho(1,:), "k+");
plot(x, rho_diff(end,:), "b--.", 'LineWidth', 1)
plot(pb.X, rho(end,:)',"r+", 'MarkerSize', ms);

xlabel("$x$",'Interpreter',"latex", 'FontSize', fs);
ylabel("$\rho~(density)$",'Interpreter',"latex", 'FontSize', fs);
title("Densities for the diffusion case", 'FontSize',fs);
legend(["$\rho_{ex}(t_0)$","$BGK(t_0)$", "$\rho_{ex}(t_f)$", "$BGK(t_f)$"], 'Interpreter', "latex", 'FontSize', 0.8*fs, 'Location', "north");
hold off


% Check of exponential decreasing behaviour

decr_BGK = abs(max(rho-2,[],2));
decr_ex = abs(max(rho_diff-2, [], 2));
kappa = 1/(3*sigma*abs(l_star)); 
lw = 2;

figure(3); hold on

plot(t,exp(-4*pi^2*t*kappa),"k-", 'LineWidth', 1);
plot(t,decr_ex, "b--", 'LineWidth', lw);
plot(t,decr_BGK, "r--", 'LineWidth', lw)

xlabel("$t$",'Interpreter',"latex", 'FontSize', fs);
title("[Diffusion]: convergence towards equilibrium", 'FontSize', fs);
legend(["$e^{-\alpha t}$", "$\vert \max~\rho_{ex}-2\vert$", "$\vert \max~\rho_{BGK}-2\vert$"], 'Interpreter', "latex", 'FontSize',fs, 'location', "northeast");

hold off