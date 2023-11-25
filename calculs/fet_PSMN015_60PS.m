FET_Name = "PSMN015-60PS";


%FET parameters
  Ton = 13e-9; %s
  Toff= 7e-9; %s
  Rds_linear = 1/5; %Ohm
  Rds_on = 0.034; %Ohm

  % Per spec
  % thermal_resistance_jtoa = 60; % K/W
  % With a heatsink :
  thermal_resistance_jtoa = 1.5+22; % K/W
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [25 120];
  a_rds_vs_t_Yaxis = [1  1.8];
