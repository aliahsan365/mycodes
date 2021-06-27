def fibs():
    a = 0
    yield a
    b = 1
    while True:
        yield b
        c = a + b
        a = b
        b = c


#g1 = fibs()
#print ([next(g1) for n in range(10)])


def roots(x):
    fn1 = x
    yield fn1
    fn = 0.5*(fn1+(x/fn1))
    while True:
        yield fn
        fn1 = fn
        fn = 0.5*(fn1+(x/fn1))


#g2 = roots(4)
#print([round(next(g2), 10) for n in range(10)])


def isPrime(x):
    d = 2
    res = True
    while d < x and res == True:
        if x % d == 0:
            res = False
        d = d + 1
    return res


def primes():
    n = 2
    while True:
        if isPrime(n):
            yield n
        n = n + 1


#g3 = primes()
#print([next(g3) for n in range(20)])

def hammings():
    n = 1
    yield n
    while True:
        if n % 2 == 0 or n % 3 == 0 or n % 5 == 0:
            yield n
        n = n + 1


g4 = hammings()
print([next(g4) for n in range(20)])
