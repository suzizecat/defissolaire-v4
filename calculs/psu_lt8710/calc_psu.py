
cell_v_oc = 0.682
cell_i_sc = 6.24

cell_v_mpp = 0.574
cell_i_mpp = 5.83
pow_temp_derating = -0.0032 # -0.0032 W/°C 
ncell = 14

ratio_lum_fr = 0.800 # 800W/m2 instead of 1kW/m2


selected_vin_nom = ncell * cell_v_mpp



selected_f = 250e3
selected_vout = 18

selected_dcmax = (selected_vout) / (0.9*selected_vin_nom + selected_vout)

print(f"DC Max is {selected_dcmax:7.2%}")

max_curr_limit = 31e-3 # mv

max_rsense1 = 0.58*(max_curr_limit/cell_i_sc) * (1-selected_dcmax)
max_rsense2 = 0.05/(1.6*cell_i_sc)
print(f"Rsense1 MAX is {max_rsense1:10.4f}")
print(f"Rsense2 MAX is {max_rsense2:10.4f}")