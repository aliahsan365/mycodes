def foo( l):
    #cuando se reasigna la lista en foo, se vuelve var de funcion exclusivamente.

    print(l)
    l =  ["banana"]
    #print(l)

def f2(l):
    l.append('rainbow')


l = ['algo']
foo(l)
f2(l)
print(l)



