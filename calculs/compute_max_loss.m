function [MaxLoss] = compute_max_loss(base_PLoss, thermal_resistance, max_delta_t, rds_vs_temp_x, rds_vs_temp_y)
  MaxLoss = base_PLoss;
  delta_loss = MaxLoss;
  
  i = 0;
  result_loss = 0;
  local_delta_t = 0;
  do
    [result_loss local_delta_t] = compute_fet_runaway(MaxLoss, thermal_resistance, max_delta_t, rds_vs_temp_x, rds_vs_temp_y);
    i += 1;
    
    if(delta_loss < 0.01 && local_delta_t != Inf)
      break
     endif
    
    if(delta_loss >= 0.01)
      delta_loss = delta_loss/2;
    endif
    if (local_delta_t == Inf)
      MaxLoss -= delta_loss;
    else
      MaxLoss += delta_loss;
    endif
      
  until(i > 10000)
  
  if (i > 10000)
    printf("\tToo many iterations\n");   
  endif
endfunction
