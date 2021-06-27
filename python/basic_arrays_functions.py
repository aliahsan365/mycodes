

def myLength(l):
    i = 0
    for x in l:
        i = i + 1
    return i


# print(myLength([1,3,6,1]))


def myMaximum(l):
    m = l[0]
    for x in l:
        if x > m:
            m = x
    return m

#print(myMaximum(['josep', 'jordi', 'albert']))
#print( myMaximum([4,3,1,5,4,5,2]) )


def average(l):
    n = myLength(l)
    suma = 0
    for x in l:
        suma = suma + x
    return suma/n


# print(average([1,2,3]))

def buildPalindrome(l):
    return l[::-1] + l

#print (buildPalindrome(['pa','amb','oli']))


def flatten(ll):
    if ll == []:
        return ll
    if isinstance(ll[0], list):
        return flatten(ll[0]) + flatten(ll[1:])
    else:
        return [ll[:1]] + flatten(ll[1:])


# print(flatten([[2,6],[[8,1,4],[3,'uau']],[[],[1]],[[]]]))


def remove_one(l, e):
    lres = l
    for x in l:
        if x == e:
            lres = l.remove(x)
    return lres


def remove(l1, l2):
    lres = l1
    for y in l2:
        remove_one(l1, y)
    return lres

#print(remove([1,4,5,3,4,5,1,2,7,4,2], [2,4]))


def oddsNevens(l):
    s = []
    p = []
    for x in l:
        if (x % 2 != 0):
            # es senar
            s = s + [x]
        else:
            p = p + [x]
    return (s, p)


# print(oddsNevens([1,4,5,3,4,5,1,2,7,4,2]))

def isPrime(x):
    d = 2
    res = True
    while d < x and res == True:
        if x % d == 0:
            res = False
        d = d + 1
    return res


def primeDivisors(n):
    lp = []
    for i in range(2, n):
        if (n % i == 0 and isPrime(i)):
            lp = lp + [i]
    return lp


# print(primeDivisors(255))
