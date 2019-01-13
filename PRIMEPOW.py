'''
Created on Jan 12, 2019

@author: tiwarl
'''
import decimal
import fractions
import math
import random
import sys

write = sys.stdout.write


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def mr_pass(a, s, d, n):
    a_to_power = pow(a, d, n)
    if a_to_power == 1:
        return True
    for i in range(s - 1):
        if a_to_power == n - 1:
            return True
        a_to_power = (a_to_power * a_to_power) % n
    return a_to_power == n - 1


def is_prime(n):
    if n in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71, 79, 83, 89, 97, 101, 103, 107, 109, 113]:
        return True
    if n < 2047:prime = [2, 3]
    if n < 1373653:prime = [2, 3]
    if n < 9080191:prime = [31, 73]
    if n < 25326001:prime = [2, 3, 5]
    if n < 3215031751:prime = [2, 3, 5, 7]
    if n < 4759123141:prime = [2, 7, 61]
    if n < 1122004669633:prime = [2, 13, 23, 1662803]
    if n < 2152302898747:prime = [2, 3, 5, 7, 11]
    if n < 3474749660383:prime = [2, 3, 5, 7, 11, 13]
    if n < 341550071728321:prime = [2, 3, 5, 7, 11, 13, 17]
    if n < 3825123056546413051:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    if n < 18446744073709551616:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]
    if n < 318665857834031151167461:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    if n < 3317044064679887385961981:prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    else:  prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 47, 53, 59, 61, 67, 71]
    d = n - 1
    s = 0
    while d % 2 == 0:
        d >>= 1
        s += 1
    for repeat in range(len(prime)):
        a = prime[repeat]
        if not mr_pass(a, s, d, n):
            return False
    return True


# Determines whether n is a power a ^ b, O(lg n (lg lg n) ^ 2)
def is_power(n):
    lgn = 1 + (len(bin (abs (n))) - 2)
    # print("len = ",lgn)
    for b in range(lgn, 0, -1):
        # b lg a = lg n
        lowa = 1
        higha = 1 << (lgn // b + 1)
        # print("higha = ",higha)
        while lowa < higha - 1:
            mida = (lowa + higha) >> 1
            ab = pow(mida, b) 
            if ab > n:   higha = mida
            elif ab < n: lowa = mida
            else:   return (1, mida, b)  # mida ^ b
    return (0, 0)


def main():
    for cs in range(int(input())):
        n = int(sys.stdin.readline().strip())
        aux = is_power(n)
        if(aux[0] != 0 and is_prime(aux[1])):
            write("%d %d\n" % (aux[1], aux[2]))
        else:
            write("Invalid order\n")


main()
