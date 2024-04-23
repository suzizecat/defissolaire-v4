import pcbnew

def run(ref_src = None, ref_dst=None) :
    pcb = pcbnew.GetBoard()

    interesting_fp = [f for f in pcb.GetFootprints() if f.IsSelected()]

    for f in interesting_fp :
        print(f"Selected {f.GetReference()}")

    rdes_src = str(ref_src) if ref_src is not None else input("SOURCE reference designator: ") 
    rdes_trg = str(ref_dst) if ref_dst is not None else input("TARGET reference designator: ")

    confirm = input(f"Confirm replacing R{rdes_src}xx by R{rdes_trg}xx [Y/n]: ")
    confirm = not confirm.strip().upper() == "N"
    for f in interesting_fp :
        src = f.GetReference()
        dst = src.replace(rdes_src,rdes_trg,1)
        print(f"Replacing {src:6s} by {dst}")
        f.SetReference(dst)

