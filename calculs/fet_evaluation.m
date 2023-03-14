% Design parameters
  ambient = 40; % Celsius
  max_temp = 125; % Celsius
  ILoad = 7.3; %A
  %Fswitching = 475e3; %Hz
  Fswitching = 100e3; %Hz
  Duty = 0.5;
fet_TK4R3E06PL;
%fet_SUP90N06_6m0P;
%fet_PSMN015_60PS;
%fet_IRLB4132PbF;
%fet_PSMN4R3_40MLH;
%fet_FCB260N65S3;
%fet_STD16N52M2;

% Computations 


printf("Using MOSFET  %s\n",FET_Name);
printf("\tAmbient temp  %3.0f °C\n",ambient);
printf("\tMaximum temp  %3.0f °C\n",max_temp);
printf("\tMaximum delta %3.0f °C\n\n",max_temp- ambient);
  
[PLoss_base, conduction, switching] = compute_fet_power_loss(ILoad,Fswitching,Ton,Toff,Rds_linear,Rds_on, Duty);
printf("Base loss : %2.3f W\n",PLoss_base);
printf("\tConduction loss : %2.3f W\n",conduction);
printf("\tSwitching  loss : %2.3f W\n\n",switching);

[PLoss_ra, DeltaT] = compute_fet_runaway(PLoss_base, thermal_resistance_jtoa, ambient, 125 - ambient, a_rds_vs_t_Xaxis, a_rds_vs_t_Yaxis);
if(DeltaT != Inf)
  printf("No thermal runaway detected\n");
  printf("\tRunaway final loss     : %2.3f W\n",PLoss_ra);
  printf("\tRunaway DT             : %3.0f   K\n",DeltaT);
  printf("\tFinal Tjunction        : %3.0f  °C\n\n",DeltaT + ambient);
  thermal_ra_ploss_base = PLoss_base;
  do
    thermal_ra_ploss_base *= 2;
  until( nthargout(2,@compute_fet_runaway,thermal_ra_ploss_base, thermal_resistance_jtoa, ambient, 125 - ambient, a_rds_vs_t_Xaxis, a_rds_vs_t_Yaxis) == Inf)
 
 
  new_Ploss_base = compute_max_loss(thermal_ra_ploss_base, thermal_resistance_jtoa, ambient, 125 - ambient, a_rds_vs_t_Xaxis, a_rds_vs_t_Yaxis);
  printf("\tDetected max base loss : %2.3f W\n",new_Ploss_base);
  printf("\tPower margin           : %2.3f W\n",new_Ploss_base - PLoss_base);
  power_margin = (new_Ploss_base - PLoss_base)/(PLoss_base);
  printf("\t                       : %.0f %%\n",100*power_margin);
  power_factor = sqrt(1 + power_margin);  
  printf("\tCurrent margin         : %2.3f A\n",ILoad*(power_factor-1));
  current_margin = (ILoad + ILoad*(power_factor-1) - ILoad)/(ILoad);
  printf("\t                       : %.0f %%\n",100*current_margin);

  printf("\tMax current            : %2.3f A\n",ILoad*power_factor);
  
else
  printf("Thermal runaway detected.\n");
  new_Ploss_base = compute_max_loss(PLoss_base, thermal_resistance_jtoa, ambient,  125 - ambient, a_rds_vs_t_Xaxis, a_rds_vs_t_Yaxis);
  printf("\tDetected max base loss : %2.3f W\n",new_Ploss_base);
  [PLoss_ra, DeltaT] = compute_fet_runaway(new_Ploss_base, thermal_resistance_jtoa, ambient,  125 - ambient, a_rds_vs_t_Xaxis, a_rds_vs_t_Yaxis);
  
  printf("\tRunaway final loss     : %2.3f W\n",PLoss_ra);
  printf("\tRunaway DT             : %2.3f K\n",DeltaT);
endif  
