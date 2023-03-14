from quantiphy import Quantity
import  numpy as np
from numpy.polynomial import Polynomial
from numpy.polynomial.polynomial import polyval
from math import sqrt

import matplotlib as mpl
import matplotlib.pyplot as plt
import typing as T

class DesignParameter:
    def __init__(self,temp_ambient, temp_max, i_load, duty_cycle) -> None:
        self.temp_ambient = Quantity(temp_ambient)
        self.temp_max = Quantity(temp_max)
        self.i_load = Quantity(i_load)
        self.duty_cycle = Quantity(duty_cycle)

    def __str__(self) :
        return f"Ambient : {self.temp_ambient}, Load : {self.i_load}, Duty : {self.duty_cycle}"

class MOSFET:
    def __init__(self, ton, toff, rdson, rdslin, qsw,  rth_jtoa, normalized_rds : T.List[T.Tuple[int, float]]) -> None:
        self.ton = Quantity(ton)
        self.toff = Quantity(toff)
        self.rdson = Quantity(rdson)
        self.rdslin = Quantity(rdslin)
        self.q_sw  = Quantity(qsw)
        self.rth_jtoa = Quantity(rth_jtoa)
        
        x = np.array([x[0] for x in normalized_rds])
        y = np.array([x[1] for x in normalized_rds])
        
        self.normalized_rds_function = Polynomial.fit(x,y,len(normalized_rds)-1)

        self._current_op = None

    def __str__(self):
        return f"Ton = {self.ton}, Toff = {self.toff}, RDSon = {self.rdson}, RDSlin = {self.rdslin}"
    def __repr__(self):
        return f"Ton = {float(self.ton)}, Toff = {float(self.toff)}, RDSon = {float(self.rdson)}, RDSlin = {float(self.rdslin)}"

    @property
    def tlinear(self):
        return self.ton + self.toff
    
    def delta_t(self,power) :
        return self.rth_jtoa * power


class Driver:
    def __init__(self, drive_voltage, min_r,  max_r) -> None:
        self.drive_voltage = Quantity(drive_voltage)
        self.min_r = Quantity(min_r)
        self.max_r = Quantity(max_r)


class Bench:
    def __init__(self, mosfet : MOSFET, base_op : DesignParameter, driver : Driver) -> None:
        self.fet = mosfet
        self.initial_op = base_op
        self.drv = driver

        self._op = base_op
        self.thermal_ovr = False

    def reset(self) :
        self._op = self.initial_op
        self.thermal_ovr = False

    def get_fet_switch_time(self, i_drv) :
        return self.get_gate_capa() * self.drv.drive_voltage / i_drv

    def get_fet_switch_current(self, t_sw) :
        return self.get_gate_capa() * self.drv.drive_voltage / t_sw

    def get_gate_capa(self) :
        return Quantity(self.drv.drive_voltage * self.fet.q_sw, "F")

    def get_switching_losses(self, fsw) :
        # thermal_coeff = self.fet.normalized_rds_function(self._op.temp_ambient)
        return (self._op.i_load ** 2) * self.fet.tlinear * fsw
    
    def get_conduction_losses(self) :
        return (self._op.i_load ** 2) * (self.fet.rdson) * self._op.duty_cycle

    def get_mosfet_losses(self, fsw) :
        sw_loss = self.get_switching_losses(fsw)
        cond_loss = self.get_conduction_losses()
        return sw_loss + cond_loss
    
    def _get_thermal_runnaway_mosfet_losses(self, fsw, min_dt = 0.1, autoreset = False) :
        if autoreset :
            self.reset()
        max_delta_t = self._op.temp_max - self._op.temp_ambient
        delta_t = 0
        delta_t_diff = np.inf
        loss_at_fsw = np.inf
        sw_loss = np.inf
        cond_loss = np.inf

        while delta_t < max_delta_t and delta_t_diff > min_dt :
            thermal_coeff = self.fet.normalized_rds_function(self._op.temp_ambient)
            
            sw_loss = self.get_switching_losses(fsw) * thermal_coeff
            cond_loss = self.get_conduction_losses() *thermal_coeff
            loss_at_fsw = sw_loss + cond_loss
            temp = self.fet.delta_t(loss_at_fsw)
            delta_t_diff = np.abs(delta_t - temp)
            delta_t = temp
            self._op.temp_ambient += delta_t
            
        print(f"Run at {fsw} done, dt is {delta_t}")
        self.thermal_ovr = delta_t > max_delta_t

        

        return Quantity(sw_loss,"W"), Quantity(cond_loss,"W") ,Quantity(loss_at_fsw,"W"), Quantity(self._op.temp_ambient + delta_t," °C")
    
    def get_thermal_runnaway_mosfet_losses(self, fsw, min_dt = 0.1) :
        if isinstance(fsw,np.ndarray) :
            return np.array([self._get_thermal_runnaway_mosfet_losses(f,min_dt,True) for f in fsw])
        else:
            return self._get_thermal_runnaway_mosfet_losses(fsw,min_dt,False)
    

if __name__ == "__main__" :
    Quantity.set_prefs(input_sf = Quantity.get_pref('input_sf') + '%')
    fet = MOSFET("100 ns", "100 ns", "7.2 mOhm", "40 mOhm", "15.1 nC",  "22.5 K/W", [(0,0.005 / 7.2e-3),(140,0.008 / 7.2e-3)])
    design = DesignParameter("25 °C","125 °C","6 A","50 %")
    driver = Driver("7.5 V", "1.2 Ohm", "2.8 Ohm")

    tb = Bench(fet,design, driver)


    print(fet)
    print(repr(fet))
    fsw = np.arange(50e3,1e6,50e3)
    f = tb.get_thermal_runnaway_mosfet_losses(np.array(fsw),1)


    print(f"Computed thermal runnaway is\n {f}")
    print(f.shape)
    i = -1
    for v in f :
        print(v)
        if max(v) == np.inf :
            print(f"Inf value detected at i={i}")
            break
        else :
            i += 1

    psw = f[:,0][:i]
    pcond = f[:,1][:i]
    pfull = f[:,2][:i]
    temp = f[:,3][:i]

    x = fsw[:i]

    fig, (ax_losses, ax_fsw) = plt.subplots(2,1, sharex=True)
    ax_losses.plot(x,psw,label="Switching loss")
    ax_losses.plot(x,pcond, label="Conduction loss")
    ax_losses.plot(x,pfull, label="Total loss")

    ax_losses.set(xlim=(fsw[0], fsw[i-1]), ylabel="Power loss (W)")
    plt.xticks(fsw[:i],[f"{Quantity(v,'Hz')}" for v in fsw[:i]])
    ax_losses.grid(True,'both','both')

    ax_losses.legend()


    # # percentage_timing_lost = (fet.tlinear) * x *100
    # # ax_fsw.set(xlabel="Switching frequency", ylabel="Time passed in switching (%)")
    # current_drive = tb.get_fet_switch_current()
    # ax_fsw.set(xlabel="Switching frequency", ylabel="Time passed in switching (%)")
    # ax_fsw.plot(x,percentage_timing_lost)
    # ax_fsw.grid(True,'both','both')

    
    plt.show()

