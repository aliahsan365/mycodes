class Tree:
    def __init__(self,x):
        self.rt = x
        self.child = []
        #x es root
        # child deberia ser lista de sus hijos
        # [Tree1,Tree2,....]
    def add_child(self, a):
        #a es un arbol
        self.child.append(a)
    def root(self):
        return self.rt
    def ith_child(self,i):
        return self.child[i]
    def num_children(self):
        return len(self.child)


# hay la variante de hacer preorder con if else recursivo , pero acaba siendo el mismo

class Pre(Tree):
    def preorder(self):
        l = [self.rt]
        for x in self.child:
            l.extend(x.preorder())
        return l    
        
#t = Pre(2)
#t.add_child(Pre(3))
#t.add_child(Pre(4))
#print(t.num_children())
#t.ith_child(1).add_child(Pre(5))
#print(t.preorder())

