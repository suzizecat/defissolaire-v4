FET_Name = "TK4R3E06PL";


%FET parameters
  Ton = 10e-9; %s
  Toff= 18e-9; %s
  Rds_linear = 0.04; %Ohm
  Rds_on = 0.0072; %Ohm

  % Per spec
  thermal_resistance_jtoa = 83; % K/W
  % With a heatsink :
  %thermal_resistance_jtoa = 0.5+22; % K/W
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [0 140];
  a_rds_vs_t_Yaxis = [0.005  0.008] / Rds_on;
