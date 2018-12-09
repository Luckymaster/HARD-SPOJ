import sys
import math
from decimal import *
tc=int(sys.stdin.readline())
while tc:
    getcontext().prec = 90
    getcontext().rounding = ROUND_DOWN
    tc-=1
    r1,r2,r3 = [Decimal(x) for x in sys.stdin.readline().split()]
    s = r1+r2+r3
    m = r1*r2*r3
    p = r1*r2 + r2*r3 + r3*r1
    r4 = m / (p + Decimal(2.0) * (s * m).sqrt())
    #rd=str(r4)
    #i=rd.find('.')
    #print(rd[0:50+i+1])
    print(r4.quantize(Decimal(10) ** -50))
