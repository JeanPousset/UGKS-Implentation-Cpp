
% Import results
pb = read_json("pb_transport.json");
rho = read_CSV_matrix("ρ_transport.csv");

x = linspace(0,1,400);
rho_tf = arrayfun(@rho_exact_transport, x); 

% graphic parameters
ms = 8; % marker size
fs = 20; % font size

figure(1); hold on
plot(pb.X, rho(1,:), "k-.", 'LineWidth', 1);
plot(x,rho_tf,'Color', [0, 0.01, 0.8],'LineWidth',1.5);
% plot(pb.X, rho(floor(end/2),:)',"bx", 'MarkerSize', ms);
plot(pb.X, rho(end,:)',"r+", 'MarkerSize', ms);
xlabel("$x$",'Interpreter',"latex", 'FontSize', fs);
ylabel("$\rho~(density)$",'Interpreter',"latex", 'FontSize', fs);
title("Densities for the transport case at final time t=0.1", 'FontSize',fs);
legend(["Initial data","$\rho_{ex}(t_f)$","$BGK_f$"], 'Interpreter', "latex", 'FontSize', 0.8*fs, 'Location', "south");
hold off

