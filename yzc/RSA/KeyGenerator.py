#a^b % mo
def exp(a, b, mo):
    res = 1;
    while b:
        if (b&1):
            res = res * a % mo
        b >>= 1
        a = a*a % mo
    return res
    
def gcd(a, b):
    while b:
        k = b        
        b = a % b
        a = k
    return a
    
def exgcd(a, b):
    if b == 0:
        return (1, 0)
    (x, y) = exgcd(b, a%b)
    return (y, x - a/b*y)
    
def generateKey(p1, p2):
    n = p1 * p2
    phi_n = (p1 - 1) * (p2 - 1)
    
    while True:
        d = random.randint(2, phi_n - 1)
        if gcd(d, phi_n) == 1:
            break
    
    (e, y) = exgcd(d, phi_n)
    e %= phi_n
    
    print "n=", n
    print "d=", d
    print "e=", e

p1 = 6874940209628679296815932839524399950706186608086088067500097307495279405412284771358314336134820073107612965458778989497544676113070472689427394743554777
p2 = 10817503570870027803700611065607447166831107239070636640488245496982747207605853888576293698606378598852475873580895306314210688895014203434982680570111687
generateKey(p1, p2)
