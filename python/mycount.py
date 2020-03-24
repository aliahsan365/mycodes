

def myfinitecount(ini,final):
    while ini <= final:
        yield ini
        ini = ini + 1



for x in myfinitecount(1,2):
    print(x)


def myinfinitecount(ini):
    while True:
        yield ini
        ini = ini + 1



#for x in myinfinitecount(0):
 #   print(x)




def f(x): return x + 1
def g(x): return 2 * x


def compose(f,g):

    h = lambda x: f(g(x))
    return  h


#h = compose(f,g)

print(compose(f,g)(2))






