#!/usr/bin/python3
# -*- coding: utf-8 -*-

#ex1
def diffelements(llista):
    return len((list(set(llista))))

print(diffelements([1,2,3,4,4,5,4]))


#ex2
def maxlista(llista):
    maxim = llista[0]
    for x in llista:
        if x > maxim:
            maxim = x
    return maxim

print (maxlista([1,2,3,4,5,6,6,8,0]))   

#ex3
def listmitj(llista):
    suma = 0
    for x in llista:
        suma = suma + x
    return suma/len(llista)


print(listmitj([1,2,3,4]))



#ex6

def parellsenar(llista):
    parell = []
    senar =  []
    for x in llista:
        if (x%2==0):
            parell.append(x)
        else:
            senar.append(x)
    return (parell,senar)
#primer ejemplo de imprimir tuplas
(lparell,lsenar) = parellsenar([1,2,3,4,5,6])
print((lparell,lsenar))
#tuplaparellsenar
tps = parellsenar([1,2,3,4,5,6])
#ejemplo de imprimir tuplas
for x in range(len(tps)):
    print(tps[x],end = " ")








    




