from quantiphy import Quantity
import  numpy as np
from numpy.polynomial import Polynomial
from math import sqrt
import typing as T
class VoltageCorner:
    def __init__(self, v, i) -> None:
        self.v = Quantity(v,"V")
        self.i = Quantity(i,"A")

    @property
    def power(self):
        return Quantity(self.v * self.i,"W")


class DesignRequirements:
    def __init__(self, name) -> None:
        self.name = name
        self.input = VoltageCorner(8,6)
        self.out   = VoltageCorner(16,3)




class Design:
    def __init__(self, reqs) -> None:
        self.reqs = reqs

        self.K_ONTIME = Quantity("100 ns")
        self.K_OFFTIME = Quantity("100 ns")
        self.K_MAX_F   = Quantity("1 MHz")

        self.K_MAX_RIPPLE_I = 0.3
        
        self.K_MAX_RIPPLE_V = Quantity(0.05,"V")

        self.K_L = Quantity("4.7uH")
        self.Rth_rsense = 25
        self.rsense = None
        
        self.K_CT1110_G = 0.004
        self.isense_rg = None
        self.fsw = None
        self.cout = None

        self.di_tran = Quantity(1,"A")
        self.dv_tran = Quantity(0.5, "V")

        self.K_VFB = Quantity(1.22, "V")


    @property
    def Dcycle(self) :
        ret = {}
        for req in self.reqs :
            ret[req.name] = (req.out.v - req.input.v )/ req.out.v

        return ret

    @property
    def f_sw_ontime(self):
        dmin = min(self.Dcycle.values())
        return Quantity(dmin/self.K_ONTIME,"Hz")

    @property
    def f_sw_offtime(self):
        dmax = max(self.Dcycle.values())
        return Quantity((1-dmax)/self.K_OFFTIME,"Hz")

    def min_fsw(self, L = None):
        L = L if L is not None else self.K_L
        vomax = max([v.out.v for v in self.reqs])
        iimax = max([i.input.i for i in self.reqs])
        ret = 1/(4*L)
        ret *= vomax / (iimax * self.K_MAX_RIPPLE_I)

        return Quantity(ret ,"Hz")

    def min_l(self, f = None):
        f = f if f is not None else self.min_fsw()
        vomax = max([v.out.v for v in self.reqs])
        iimax = max([i.input.i for i in self.reqs])
        ret = 1/(4*f)
        ret *= vomax / (iimax * self.K_MAX_RIPPLE_I)

        return Quantity(ret ,"H")
    

    @property
    def IL_rms(self):
        dmax = max(self.Dcycle.values())
        iimax = max([i.out.i for i in self.reqs])
        vinmin = min([v.input.v for v in self.reqs])
        ret = (iimax/(1-dmax)) **2
        ret += ((vinmin * dmax) / (sqrt(12)* self.K_L * self.fsw)) ** 2
        return Quantity(sqrt(ret),"A")

    @property
    def IL_pk(self):
        dmax = max(self.Dcycle.values())
        iimax = max([i.out.i for i in self.reqs])
        vinmin = min([v.input.v for v in self.reqs])
        ret = (iimax/(1-dmax))
        ret += ((vinmin * dmax) / (2* self.K_L * self.fsw)) 
        return Quantity(ret,"A")
    
    @property
    def r_sense(self):
        return Quantity(70e-3 / (1.2*(self.IL_pk)),"ohm")
    
    @property
    def r_sense_dissip(self):
        return Quantity(self.rsense * (self.IL_pk ** 2),"W")

    @property
    def r_sense_dv(self):
        return Quantity(self.rsense * self.IL_pk,"V")

    @property
    def r_sense_dt_mid_pad(self):
        return Quantity(self.r_sense_dv * self.IL_pk * self.Rth_rsense,"°C")

    def pcb_rth(self, area) :
        sqin_area = area / (0.0254**2)
        return sqin_area * 125

    def diag_rsense(self, r) :
        return Quantity(70e-3 / (1.2*(r)),"A")

    @property
    def external_isense_g_r(self):
        # For 8A max
        return Quantity(3/(self.rsense * self.K_CT1110_G * 8),"ohm")
    
    def eval_ipk_for_rg(self,rg):
        return Quantity(3/(self.rsense * self.K_CT1110_G * rg),"A")
    
    def eval_fb_ratio(self,vout) :
        return self.K_VFB/vout
    
    @property
    def f_rhpz(self) :
        iout = max([i.out.i for i in self.reqs])
        vout = min([v.out.v for v in self.reqs])
        vin = min([v.input.v for v in self.reqs])
        return Quantity(((vout / iout) / (2*np.pi*self.K_L)) * ((vin/vout)**2),"Hz")
    
    @property
    def r_zcomp(self) :
        vout = min([v.out.v for v in self.reqs])
        vinmin = min([v.input.v for v in self.reqs])
        inv_ratio = 1/(self.eval_fb_ratio(vout))
        #print(self.cout , self.r_sense , vout , (self.f_rhpz/4) , inv_ratio)
        #print(vinmin)
        r = (40/3) * (2*np.pi * self.cout * self.r_sense * vout * (self.f_rhpz/4) * inv_ratio) / (vinmin * 1100e-6) 
        
        return Quantity(r,"Ohm")
    
    @property
    def c_zcomp(self) :
        return Quantity(1/(2*np.pi * (self.f_rhpz/40) * self.r_zcomp),"F")
    
    @property
    def min_cout(self):
        cout_bw = self.di_tran/(2*np.pi*(self.f_rhpz/4)*self.dv_tran)
        
        dcycle = max(self.Dcycle.values())
        iout = max([i.out.i for i in self.reqs])
        cout_vripple = dcycle * iout / (self.fsw*self.K_MAX_RIPPLE_V)

        return Quantity(max(cout_bw, cout_vripple),'F')
    
    @property
    def min_cin(self):
        iripple = self.K_MAX_RIPPLE_I * max([i.out.i for i in self.reqs])
        vin_ripple = 0.05

        return Quantity(iripple/(4*self.fsw*vin_ripple),"F")

if __name__ == "__main__" :
    
    nom = DesignRequirements("nom")
    worst = DesignRequirements("worst")
    equi = DesignRequirements("equi") 
    low = DesignRequirements("low")

    worst.input.v = Quantity(5,"V")
    worst.input.i = Quantity(1,"A")
    worst.out.v = Quantity(10,"V")
    worst.out.i = Quantity(0.5,"A")
    equi.input.v = Quantity(8,"V")
    equi.out.v = Quantity(12,"V")
    equi.out.i = Quantity(4,"A")

    low.input.v = Quantity("8 V")
    low.input.i = Quantity("6 A")
    low.out.v = Quantity("8.1 V")
    low.out.i = Quantity("6 A")
    d = Design([nom])

    print(f"Maximum rippled current : {(1 + d.K_MAX_RIPPLE_I) * nom.input.i}")

    print(f"Duty cycle is {d.Dcycle}")
    fon = d.f_sw_ontime
    foff = d.f_sw_offtime
    print(f"f_ontime   is {d.f_sw_ontime}")
    if fon > d.K_MAX_F :
        print(f"    Not limiting")
    print(f"f_offtime  is {d.f_sw_offtime}")
    flimit = min(foff,fon,d.K_MAX_F)
    print(f"Selected SW freq : {flimit}")

    

    
    d.fsw = Quantity("122 kHz")
    #d.fsw = Quantity("200 kHz")
    d.K_L = Quantity("22 uH")
    print(f"Using fixed value of L as {d.K_L}")
    print(f"Choosing fsw = {d.fsw}, giving >= {d.min_l(d.fsw)} ({Quantity(d.min_l(d.fsw)/0.85,'H')} with margin)")
    print(f"Choosing L   = {d.K_L}, giving  >= {d.min_fsw(d.K_L)} ({d.min_fsw(0.85*d.K_L)} with margin)")

    print(f"Irms    = {d.IL_rms}")
    print(f"Ipk     = {d.IL_pk}")
    print(f"Rsense  = {d.r_sense}")

    d.rsense = Quantity("8 mOhm")
    print(f"Choosing rsense = {d.rsense}, giving Ipk = {d.diag_rsense(d.rsense)}")
    print(f"Giving at peak {d.r_sense_dissip} of dissipation and a drop of {d.r_sense_dv}")
    print(f"Giving approximative DT between center and pads of {d.r_sense_dt_mid_pad}")

    print(f"The required ZXCT1110 value for 3V gain is : {d.external_isense_g_r}")
    
    d.isense_rg = Quantity("12 kohm")
    print(f"Select {d.isense_rg} value, giving max current at {d.eval_ipk_for_rg(d.isense_rg)}")

    print(f"\nFor compensation : frhpz = {d.f_rhpz}")
    print(f"                   fco   = {Quantity(d.f_rhpz/4,'Hz')}")

    print(f"Cout > {d.min_cout} (derated {Quantity(d.min_cout/0.8,'F')})")
    d.cout = Quantity(7*47e-6,"F")
    print(f"Selected Cout = {d.cout}")
    print(f"Selected Cin  = {d.min_cin}")

    print()
    print(d.eval_fb_ratio(16))
    print(f"Compensation components :")
    print(f"    R_zcomp : {d.r_zcomp}")
    print(f"    C_zcomp : {d.c_zcomp}")


    