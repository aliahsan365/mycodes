
s = "abc"
it  = iter(s)
while True:
    try:
        print (it.__next__())
    except StopIteration:
        break 


def f2(f1):
    return f1(6)


myf = lambda x: 2*x

print(f2(myf))



def usafuncion(f):
    return f()


def funcionparaenviar():
    return 2+2

print(usafuncion(funcionparaenviar))
