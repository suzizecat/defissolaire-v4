from quantiphy import Quantity

fsw      = Quantity(150e3, "Hz")
ig       = Quantity(2, "A")
vg       = Quantity(7.5, "V")
qsw      = Quantity(15e-9, "C")
avg_rdrv = Quantity(3,"Ohm")
Rg       = Quantity(1.7,"Ohm")

print(f"Design parameters :")
print(f"   Fsw    = {fsw}")
print(f"   IDrive = {ig}")
print(f"   Vg     = {vg}")
print(f"   Rg     = {Rg}")
print(f"   Rpupd  = {avg_rdrv}")


Cg = Quantity(qsw / vg,"F")
Rgtot = Quantity(vg/ig ,"Ohm")

if Rgtot < Rg + avg_rdrv : 
    print(f"       Impossible to reach requested current {ig}, min Rg is {Quantity(Rg + avg_rdrv,'Ohm')} while {Rgtot} would be required.")
    Rgtot = Quantity(Rg + avg_rdrv,"Ohm")
    ig = Quantity(vg/Rgtot,"A")
    print(f"       Update Rgtot = {Rgtot}")
    print(f"       Update Ig    = {ig}")


print("Gate characteristics :")
print(f"   Qgate  = {qsw}")
print(f"   Cg     = {Cg}")
print(f"   Rgtot  = {Rgtot}")

Rgext = Quantity(Rgtot - Rg - avg_rdrv, "Ohm")
if Rgtot > Rg + avg_rdrv :
    print(f"   Rgext  = {Rgext}")
else :
    print(f"   Rgext    Not needed")


tau = Quantity(Rgtot * Cg,"s")

trise = Quantity(3*tau,"s")
print(f"Giving :")
dcycle = trise * fsw
i_avg = Quantity(2 * ig * dcycle,"A")

print(f"   trise = {trise}")
print(f"   duty  = {dcycle:.2%}")
print(f"   Iavg  = {i_avg}")

psw_int = Quantity(avg_rdrv * (i_avg**2),"W")
psw_int_tot = Quantity(2*psw_int,"W")

psw_ext = Quantity(Rgext * (i_avg**2),"W")
psw_ext_tot = Quantity(2*psw_ext,"W")

psw = Quantity(Rgtot * (i_avg**2),"W")
psw_tot = Quantity(2*psw,"W")

print(f"Average power to internally dissipate is {psw_int} per channel ({psw_int_tot} total)")
print(f"Average power to externally dissipate is {psw_ext} per channel ({psw_ext_tot} total)")
print(f"Average power to totally    dissipate is {psw    } per channel ({psw_tot    } total)")



