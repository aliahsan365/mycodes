from p5 import my_map
import functools
from functools import reduce


def evens_product(l):
    return reduce((lambda acc,x: acc * x),filter((lambda x:True if (x%2 == 0) else False),l),1)


#print(evens_product([1,2,4,3]))


def reverse(l):
    return []
    
print(reverse([1,2,3]))

print(my_map(lambda x: 2*x,[1,2,3]))














