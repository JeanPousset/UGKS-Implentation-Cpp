
% Import results
pb = read_json("pb_transport.json");
rho = read_CSV_matrix("ρ_transport.csv");

x = linspace(0,1,400);
rho_tf = arrayfun(@rho_exact_transport, x); 

% graphic parameters
ms = 8; % marker size
fs = 20; % font size

figure(1); hold on
plot(pb.X, rho(1,:), "k-", 'LineWidth', 1);
plot(pb.X, rho(floor(end/2),:)',"bx", 'MarkerSize', ms);
plot(pb.X, rho(end,:)',"rh", 'MarkerSize', ms);
plot(x,rho_tf,"g-",'LineWidth',2);
xlabel("$x$",'Interpreter',"latex", 'FontSize', fs);
ylabel("$\rho~(density)$",'Interpreter',"latex", 'FontSize', fs);
legend(["Initial data","$BGK_i$","$BGK_f$","$\rho_{ex}(t_f)$"], 'Interpreter', "latex", 'FontSize', fs, 'Location', "south");
hold off

