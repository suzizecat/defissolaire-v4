from math import pi
from math import log10

from scipy import signal
from numpy import polymul
from matplotlib import pyplot as plt
from numpy import logspace

from quantiphy import Quantity

class Capacitor:
    def __init__(self,capacity,esr) :
        self.cap = Quantity(capacity,"F")
        self.esr = Quantity(esr,"Ohm")

    @property
    def zero(self) :
        
        return 1/(2*pi*self.cap*self.esr)


class TPS61178_System:
    def __init__(self): 

        
        self.d_cycle = 0.9
        self.cout = Capacitor(45e-6,1e-3)
        #self.cout = Capacitor(10,1e-3)
        self.l = 1.5e-6

        self.max_pin = Quantity(48,"W")
        self.iout    = Quantity(48/8,"A")
        self.vin     = 8
        self.f_sw    = 600e3
        self.rout_up = 12e3
        self.rout_down = 1.8e3

        self._RDSON_LS = 25e-3
        self._R_SENSE = 0.083
        self._V_FB = 1.1

        self._GEA = 195e-6
        self._Kcomp = 12
        self._REA = 20e6

        self.c_zero_comp = 470e-12
        self.r_comp = 68e3
        self.c_pole_comp = None

        self.USR_f_crossover = None
        self.USR_k_error_amp_gain = None
        self.USR_r_load = None


    @property
    def r_load(self) :
        if self.USR_r_load is None : 
            return Quantity((self.output_voltage**2)/self.max_pin,"Ohm")
        else :
            return Quantity(self.USR_r_load ,"Ohm")

    @r_load.setter
    def r_load(self,v) :
        self.USR_r_load = v

    def poly(self,s,cst) :
        return 1+(s/(2*pi*cst))

    def npoly(self,s,cst) :
        return 1-(s/(2*pi*cst))


    def set_output_voltage(self,v) :
        k = self._V_FB /v
        self.rout_down = k * self.rout_up / (1-k)

    @property
    def output_voltage(self) :
        return Quantity(self._V_FB / self.output_bridge_factor,"V")



    @property
    def transfert_function(self) :
        gps_gain = ((self.r_load * (1- self.d_cycle)) / (2*self._R_SENSE))
        gps_a = 1/(2*pi*self.f_esr)
        gps_b = -1/(2*pi*self.f_rhp_z)

        gps_pole = 1/(2*pi*self.f_p)
        base_num = [(gps_a*gps_b) ,(gps_a + gps_b),1]

        #base_bpg_fct = signal.TransferFunction(polymul(base_num,[gps_gain]),[gps_pole])
        base_bpg_fct = signal.TransferFunction(base_num,[gps_pole])

        he_denum = [1/((pi*self.f_sw)**2),
        ((1+(self.comp_slew_rate/self.inductor_slew_rate)) * (1-self.d_cycle) - 0.5 )/self.f_sw ,
        1]

        base_he_fct = signal.TransferFunction([1],he_denum)

        combination = signal.TransferFunction(polymul(base_bpg_fct.num,base_he_fct.num),polymul(base_bpg_fct.den,base_he_fct.den))
        return combination


    def gps(self,freq):
        s = freq
        ret = ((self.r_load * (1- self.d_cycle)) / (2*self._R_SENSE))
        ret *= self.poly(s,self.f_esr)
        ret *= self.npoly(s,self.f_rhp_z)
        ret /= self.poly(s,self.f_p)
        ret *= self.he(s)
        return  ret 
        # ((self.r_load * (1- self.d_cycle)) / (2*self._R_SENSE)) * (self.poly(s,self.f_esr) * self.npoly(s,self.f_rhp_z)/self.poly(s,self.f_p)) * self.he(s)
        #

    def he(self,freq):
        s = freq

        return  1/(1+ ((s * ( (1+(self.comp_slew_rate/self.inductor_slew_rate)) * (1-self.d_cycle) - 0.5 ))/self.f_sw) + ((s ** 2 ) / ((pi*self.f_sw)**2) ) )


    @property
    def inductor_slew_rate(self) :
        return (self.vin / self.l) * self._R_SENSE

    @property
    def comp_slew_rate(self):
        return 0.06 * self._RDSON_LS * self.f_sw/(1-self.d_cycle)



    @property
    def f_p(self):
        """
        Power stage single pole
        """
        return 1/(2*pi*self.r_load*self.cout.cap)

    @property
    def f_esr(self) :
        return self.cout.zero

    @property
    def f_rhp_z(self):
        """Right hand plane zero"""
        return (self.r_load*(1-self.d_cycle)**2)/(2*pi*self.l)

    @property
    def comp_pole_1(self):
        return 1/(2*pi* self._REA * self.c_zero_comp)

    @property
    def comp_pole_2(self) :
        if self.c_pole_comp is None : 
            return None
        else :
            return 1/(2*pi * self.r_comp * self.c_pole_comp)

    @property
    def comp_zero(self) :
        return 1/(2*pi* self.r_comp * self.c_zero_comp)


    @property
    def f_crossover(self) :
        if self.USR_f_crossover is not None :
            return self.USR_f_crossover
        else :
            return min(self.f_sw/10, self.f_rhp_z/5)

    @property
    def output_bridge_factor(self) :
        return self.rout_down/(self.rout_down+self.rout_up)

    @property
    def ea_gain(self):
        return 20*log10(self._GEA * self.r_comp * self.output_bridge_factor)

    def compute_c_pole(self) :
        return Quantity(self.cout.cap * self.cout.esr / self.r_comp,"F")

    def compute_rcomp(self) :
        print(f"Computing R_comp, this may take a while...")
        
        approx = 0.01 # 5% approx

        f_crossover = self.f_crossover
        target = -self.gps(f_crossover)

        if self.r_comp is None :
            self.r_comp = 1

        value = self.ea_gain
        imax = 1000
        i = 0
        while i < imax and value < ((target * (1-approx)) or value > (target * (1+approx))) :
            delta = target - value

            req_udpate = 1/20 * delta
            value += 10**req_udpate

        return Quantity(value,"Ohm")

    def compute_ccomp(self):
        return Quantity((self.cout.cap * self.r_load) / (2*self.r_comp),"F")

    def compute_cout(self) :
        c_val = self.iout * (self.output_voltage - self.vin) / (self.f_sw * 0.1 * self.output_voltage)
        return Capacitor(Quantity(c_val,"F"),Quantity("1 mOhm"))

    def compute(self):
        print("# Compute step")
        if self.cout is None :
            print("Computing the output capacitor requirement")
            self.cout = self.compute_cout()
        if self.USR_f_crossover is None :
            print(f"Computing f_crossover...")
            self.USR_f_crossover = self.f_crossover
        if self.r_comp is None :
            print(f"Computing r_comp...")
            self.r_comp = self.compute_rcomp()
        if self.c_zero_comp is None :
            print("Computing the zero compensation capacitor")
            self.c_zero_comp = self.compute_ccomp()
        if self.c_pole_comp is None :
            print("Computing the pole compensation capacitor")
            self.c_pole_comp = self.compute_c_pole()

        print()

    def _print_value(self, name, value) :
        
        v =  value if isinstance(value,Quantity) else Quantity(value)
        print(f"{name:.<20s} = {v:>12.3q}")

    def _print_condition(self,condition_descr, condition_val) :
        ret = f"Condition  '{condition_descr}' is {'PASSED' if condition_val else 'FAILED'}"
        print(ret)
        return condition_val



    def report(self) :
        
        print("# Pre-tests")
        self._print_value("Sn",self.inductor_slew_rate)
        self._print_value("Sr",self.comp_slew_rate)
        self._print_condition("Sn > Sr", self.inductor_slew_rate > self.comp_slew_rate)
        print()
        print("# Report")
        self._print_value("Vout",self.output_voltage)
        self._print_value("Iout",self.iout)
        self._print_value("Rload",self.r_load)
        self._print_value("Cout",self.cout.cap)
        self._print_value("Resr",self.cout.esr)
        self._print_value("Fcross",self.f_crossover)
        self._print_value("Rcomp",self.r_comp)
        self._print_value("Ccomp",self.c_zero_comp)
        if self._print_condition("Cpole required", self.c_pole_comp > 10e-12) :
            self._print_value("Cpole",self.c_pole_comp)

        print("")
        print("# Bode output")
        tf = self.transfert_function
        print(tf)
        w, mag, phase = signal.bode(tf,w=logspace(0,8,num=80))
        fig, axs = plt.subplots(2)
        
        axs[0].semilogx(w,mag)
        axs[0].set_title("Gain")
        axs[1].semilogx(w,phase)
        axs[1].set_ylim((-200,200))
        axs[1].set_title("Phase")

        for ax in axs :
            ax.set_xlim(1,1e8)
            ax.minorticks_on()
            ax.grid(True,'both')
        plt.show()


        



if __name__ == "__main__" :
    Quantity.set_prefs(preferred_units={"Ω": "Ohms Ohm ohms ohm"})
    t = TPS61178_System()
    
    t.r_comp = None
    t.c_zero_comp = None
    vout = 16 # 12V will give 3 Ohm load drive
    #t.r_load = 5
    t.iout  = Quantity(48/vout, "A")
    t.set_output_voltage(vout)

    t.compute()
    t.cout = Capacitor(10,1)
    t.report()

    

    
