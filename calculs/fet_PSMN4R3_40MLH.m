FET_Name = "PSMN4R3-40MLH";

%FET parameters
  Ton = 30e-9; %s
  Toff= 24.3e-9; %s
  Rds_linear = 16e-3; %Ohm
  Rds_on = 4e-3; %Ohm

  thermal_resistance_jtoa = 130; % W/°C
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-30 30 120];
  a_rds_vs_t_Yaxis = [0.8 1.05 1.6];
