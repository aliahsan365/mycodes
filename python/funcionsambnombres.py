
def absValue(x):
    if x < 0:
        return  x*(-1)
    return x


#print(absValue(-666))


def power(x,p):
    res = 1;
    while p > 0:
        res = res*x
        p = p - 1
    return res


#print(power(2, 4)) 


def isPrime(x):
    if (x < 2):
        return False
    d = 2
    res = True
    while d < x and res:
        if x%d == 0:
            res = False
        d = d + 1
    return res    
        

#print (isPrime(9))


def slowFib(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return slowFib(n-1) + slowFib(n-2)
    

#print(slowFib(8))


def quickFib(n):
    res = 0
    if n == 0:
        res = 0
    elif n == 1:
        res = 1
    else :
        a = 0
        b = 1
        i =  2
        while i <= n:
            c = a + b
            a = b
            b = c
            res = c
            i = i + 1
    return res

#print(quickFib(8))

