FET_Name = "IPD50P04P4-13";

%FET parameters
  Ton = 27e-9; %s
  Toff= 50e-9; %s
  Rds_linear = 25e-3; %Ohm
  Rds_on = 9.2e-3; %Ohm

  thermal_resistance_jtoa = 62; % W/°C
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-20 20 140];
  a_rds_vs_t_Yaxis = [7.9e-3 9e-3 13e-3]./Rds_on;
