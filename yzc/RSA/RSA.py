#a^b % mo
def exp(a, b, mo):
    res = 1;
    while b:
        if (b&1):
            res = res * a % mo
        b >>= 1
        a = a*a % mo
    return res
      
def encrypt(plainText, key, n):
    return exp(plainText, key, n)

def decrypt(cipherText, key, n):
    return exp(cipherText, key, n)
    
n = 74369690267176175798847701605091219721796824451305231086182378860904163718306715511137617045878346150177577465225458365204853957464101869559523483765085320069601430272934254954096047654042014054862412535552016947926547048794093660021069756876541319446717505309519036553673175630789889323979707525306292378799
d = 41246495774129519072973968428757519653270457691986864423779105021760194559494809805045560099552584158663920798905603280018640922386583676603686352414037045306937471597981241870020763728231412896458436675781906188358752584138244448784998312888014500223665599771383079029087068447742964289185402127341432168343
e = 13450494394088192845529080356588159929072764613917097127526472196665718656301197243898342154045835161554227499235238752606609378062252589686625501336922959593211404572521256514067542686812204905301949335877301422823757945714365009864931783866490322810770817344815928194680456406965500902849443483315673162535

plainText = 2013011377
cipherText = encrypt(plainText, d, n)
print "cipherText =", cipherText
print "plainText =", decrypt(cipherText, e, n)

