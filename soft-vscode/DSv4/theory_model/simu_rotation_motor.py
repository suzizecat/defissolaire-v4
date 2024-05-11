# On simule le déplacement des phases en face des aimants.
from math import pi
import typing as T

def compute_pole_polarity(aimants, poles, norm = 1) :
    ret = dict()
    for branche, pol in zip(poles, aimants) :
        if branche not in ret :
            ret[branche] = -pol
        else :
            ret[branche] -= pol
    

    return {b : p/norm for b,p in ret.items()}


aimants : T.List[int] = [1,1,1] + [-1,-1,-1] 
aimants *= 2

poles = ['a'] * 4 + ['b'] * 4 + ['c'] * 4

assert len(aimants) == len(poles)
print(f"Iteration x : " + " ".join([('+' if t == 1 else '-') for t in aimants]))
for i in range(6) :
    polarity = compute_pole_polarity(aimants,poles,2)
    disp = " ".join(poles) +  "   " + " ".join([f"{n} : {polarity[n]:-2.0f}" for n in sorted(polarity.keys())])
    print(f"Iteration {i} : {disp}")
    poles =  [poles[-1]] + poles[:-1]

n_aimants = 40
n_poles = 30

# Une periode est équivalente au déplacement de 2 aimants, donc 2/40 ème de tour.
delta_tour = 2/n_aimants
delta_step = delta_tour/6
reso = 1200
print(f"Using a resolution of {reso} evt per rotation, we get {delta_step * reso} evt per switch")

presc = delta_step * reso
freq = 10e3
max_rotation = delta_step * freq
print(f"With a processing frequency of {freq} Hz, maximum reachable speed would be {max_rotation:6.2f} tr/s ({max_rotation*60} tr/min)")

wheel_size = 40e-3 # m, rayon 

max_speed = 2*pi*wheel_size*max_rotation*3.6
print(f"Giving a max speed of {max_speed :6.2f} km/h")

target_speed = 25
target_rot_per_s = (target_speed /3.6) / (2*pi*wheel_size)
target_evt_per_s = target_rot_per_s * reso
print(f"Given a target of {target_speed} km/h there will be {target_evt_per_s:6.0f} evt/s of which {target_evt_per_s/presc:6.0f} to actually handle")