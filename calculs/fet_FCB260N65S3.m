FET_Name = "FCB260N65S3";

%FET parameters
  Ton = 10*18e-9; %s
  Toff= 10*12e-9; %s
  Rds_linear = 5; %Ohm
  Rds_on = 226e-3; %Ohm

  %thermal_resistance_jtoa = 40; % W/°C
  thermal_resistance_jtoa = 40; % W/°C
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-50 25 150];
  a_rds_vs_t_Yaxis = [0.5 1 2.5];