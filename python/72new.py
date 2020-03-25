#!/usr/bin/python3
# -*- coding: utf-8 -*-


from functools import reduce

#ex1

def dotlist(llista):
    return reduce(lambda acc,y: acc*y,llista,1)
    
#l = eval(input('? '))
#print (dotlist(l)) 
print(dotlist([1,2,3,4]))

def doteven(llista):
    return dotlist(filter(lambda x:x%2 == 0,llista))

print(doteven([1,2,3,4]))

#reverse with reduce
def myreverse(llista):
    n = len(llista)

    lsub = llista[1:n]
    if (n==0):
        return []
    else:
       lr =  myreverse(lsub)
       lr.append(llista[0])
       return lr

print(myreverse([1,2,3,4]))

#myreverse v2
def myreverse2(llista):
    n = len(llista)

    lsub = llista[1:n]
    if (n==0):
        return []
    else:
       lr =  myreverse(lsub)
       lr.append(llista[0])
       return lr


print(myreverse2([1,2,3,4]))


def countElemOccurs(llista,y):
    return len(list(filter(lambda x: x==y,llista)))


def elemInLists(llistallistas,elem):
    res = []
    for lista in llistallistas:
        res.append(countElemOccurs(lista,elem))
    return res
        
    
print(elemInLists([[1,2,3,4],[1,2,3,4],[1,2,4]],3))









