function [PLoss, DeltaT] = compute_fet_runaway(base_PLoss, thermal_resistance, max_delta_t, rds_vs_temp_x, rds_vs_temp_y)
  
  poly_rds_factors = polyfit(rds_vs_temp_x,rds_vs_temp_y,length(rds_vs_temp_x) - 1);
  DeltaT = 0;
  DeltaT_diff = 0;
  do
    rds_factor = polyval(poly_rds_factors,25+DeltaT);  
    PLoss = base_PLoss * rds_factor;
    DeltaT_diff = DeltaT;
    DeltaT = PLoss * thermal_resistance;
    DeltaT_diff -= DeltaT; 
  until( abs(DeltaT_diff) < 1 | DeltaT > max_delta_t)
  
  if (DeltaT > max_delta_t)
    DeltaT = inf;
   endif
  
endfunction

