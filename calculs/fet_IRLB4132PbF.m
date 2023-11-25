FET_Name = "IRLB4132PbF";


%FET parameters
  Ton = 92e-9; %s
  Toff= 36e-9; %s
  Rds_linear = 0.2/70; %Ohm
  Rds_on = 0.0045; %Ohm

  thermal_resistance_jtoa = 62; % °C/W
  
  % Normalized drain-source on-state resistance factor as a function of junction temperature
  a_rds_vs_t_Xaxis = [-40 25 125];
  a_rds_vs_t_Yaxis = [0.75 1 1.5];
