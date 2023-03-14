FET_Name = "SUP90N06-6m0P";


%FET parameters
  Ton = 20e-9; %s
  Toff= 15e-9; %s
  Rds_linear = 1/20; %Ohm
  Rds_on = 0.010; %Ohm

  % Per spec
  thermal_resistance_jtoa = 60; % K/W
  % With a heatsink :
  %thermal_resistance_jtoa = 0.5+22; % K/W
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-20 25 125];
  a_rds_vs_t_Yaxis = [0.8 1  1.6];
