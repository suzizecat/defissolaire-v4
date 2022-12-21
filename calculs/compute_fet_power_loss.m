function [PLoss, conduction_loss, switching_loss] = compute_fet_power_loss(Iload,Fsw,Ton,Toff,Rds_linear,Rds_on, duty)
  switching_loss = (Iload^2) * (Ton + Toff) * Rds_linear * Fsw;
  conduction_loss= (Iload^2) * Rds_on * duty;
  
  PLoss = switching_loss + conduction_loss;
endfunction
