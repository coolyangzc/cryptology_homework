import random

testTimes = 100

#a^b % mo
def exp(a, b, mo):
    res = 1;
    while b:
        if (b&1):
            res = res * a % mo
        b >>= 1
        a = a*a % mo
    return res
    
def MillerRabinTest(x):
    if x == 2:
        return True
    if x < 2 or x & 1 == 0:
        return False
        
    #x-1 = 2^t * u        
    t = 0
    u = x - 1
    while (u&1 == 0):
        t += 1
        u >>= 1
    
    for i in range(1, testTimes):
        a = random.randint(1, x - 1)
        e = exp(a, u, x)
        if e % x == 1 or e % x == x-1:
            continue
        check = False
        for j in range(1, t):
            e = e * e % x
            if e % x == 1:
                return False
            if e % x == x-1:
                check = True
                break
        if check:
            continue
        return False
    return True
    
def createPrime(bitLength):
    while True:
        p = random.randrange(2 ** (bitLength - 1) + 1, 2 ** bitLength - 1, 2)
        if MillerRabinTest(p):
            return p

p1 = createPrime(512)
p2 = createPrime(512)
n = p1 * p2
print "p1=", p1
print "p2=", p2
print "n=", n


