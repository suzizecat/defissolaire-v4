FET_Name = "STD16N52M2";


%FET parameters
  Ton = 17.2e-9; %s
  Toff= 42e-9; %s
  Rds_linear = 5/13; %Ohm
  Rds_on = 0.28; %Ohm

  thermal_resistance_jtoa = 50; % W/°C
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-50 25 125];
  a_rds_vs_t_Yaxis = [0.55 1 2.1];
