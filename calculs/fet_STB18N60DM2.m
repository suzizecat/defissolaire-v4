FET_Name = "STB18N60DM2";

%FET parameters
  Ton = 30*21.5e-9; %s
  Toff= 30*42e-9; %s
  Rds_linear = 2; %Ohm
  Rds_on = 260e-3; %Ohm

  %thermal_resistance_jtoa = 40; % W/°C
  thermal_resistance_jtoa = 40; % W/°C
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-50 25 150];
  a_rds_vs_t_Yaxis = [0.5 1 2.4];