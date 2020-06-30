import plateio

addr = 36
cmd = 0x31
p1 = 0
p2 = 0
bytes = 16

val = plateio.sendCMD(addr, cmd, p1, p2, bytes, True);

print(val);
