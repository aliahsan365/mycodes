
class A:

    def m(self):
        print("A::m")


class B(A):

    def m(self):
        print("B::m")


def f(x):
    x.m()


def main():
    a = A()
    a.m()

    b = B()
    b.m()

    print()

    f(a)
    f(b)

    print()

    v = [a, b]
    for x in v:
        x.m()


main()
