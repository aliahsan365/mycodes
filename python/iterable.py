from functools import reduce
def count_unique(l):
    return len(set(l))    



#print(count_unique([1, 3, 2, 2, 3, 4]))


def remove_duplicates(l):
    return set(l)

#print(remove_duplicates([3, 1, 3, 2, 3, 2, 3, 4]))
#
#
def flatten(ll):
    return reduce(lambda l1,l2: l1 + l2,[])


#print(flatten([[2, 6], [8, 1, 4], [], [1]]))

def flatten_rec(ll):
    if ll == []:
        return []
    else :
        l = []
        if isinstance(ll[0],list):
            l = l + flatten_rec(ll[0]) +  flatten_rec(ll[1:])
        else:
            l = l + [ll[0]] + flatten_rec(ll[1:])
        return l

#print(flatten_rec([[2, 6], [8, 1, 4], [], [1]]))

