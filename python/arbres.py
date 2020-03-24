class Tree:
    def __init__(self,x,hijos):
        self.rt = x
        self.child = hijos

    def root(self):
        return self.rt

    def ith_child(self,i):
        return self.child.append(i)

    def num_children(self):
        return len(self.child)

    def planta(self,father,childs):

        pos = 0
        res = True
        for x in self.child:
            if x == father:
                #plantar



            pos = pos + 1








t = Tree(1)
t.add_child(2)
t.add_child(3)
t.add_child(4)
print(t.root())
print(t.num_children())
print (t.ith_child(0))






