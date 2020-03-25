fsuma = lambda x,y:x+y


def zipWith(f,l1,l2):
 
    return list(map(lambda t: f(t[0], t[1]), zip(l1,l2)))



print(zipWith(fsuma,[1,2,3],[1,2,3]))

def takeWhile(f,l):
    

#def takeWhile(func,llista):
#    res = []
#    for x in llista:
#        if func(x):
#            res.append(x)
#        else:
#            break
#    return res
#
#def dropWhile(func,llista):
#    res = []
#    for x in llista:
#        if not func(x):
#            res.append(x)
#        else:
#            break
#    return res


#def myfoldl(func, ini, llista):
    #res = ini
    #for x in llista:
        #temp = func(ini,x)
        #res = res + temp
        #ini = temp
    #return res

#ffold = lambda x,y:x+y

#print(myfoldl(ffold,0,[3, 2, (-1)]))



def countIf(func, llista):
    res = 0
    for x in llista:
        if func(x):
            res = res + 1
    return res

ftest = lambda x:x%2==0
#
#
#print(takeWhile(ftest,[2, 4, 6, 7, 8]))
#print(dropWhile(ftest,[2, 4, 6, 7, 8]))
#
print(countIf(ftest,[1,2,3,4]))
#
#from functools import reduce
#product = reduce((lambda x, y: x * y), [1, 2, 3, 4])
#print(product)
