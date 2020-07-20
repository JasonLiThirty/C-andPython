import Python_Wrapper

class B_Tree():

    preorder = []
    ingore = '*'

    def __init__(self, data, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def generate_pre_order(self):
        B_Tree.preorder.append(self.data)
        if self.left is None:
            B_Tree.preorder.append(B_Tree.ingore)
        else:
            self.left.generate_pre_order()
        if self.right is None:
            B_Tree.preorder.append(B_Tree.ingore)
        else:
            self.right.generate_pre_order()

    def generate_to_c(self):
        c_btree = Python_Wrapper.TransBTree(B_Tree.ingore)
        c_btree.Generate(B_Tree.preorder)
        c_btree.Preorder()
        print("\n")
        c_btree.Inorder()
        print("\n")
        c_btree.Postorder()


a = B_Tree("A")
b = B_Tree("B")
c = B_Tree("C")
d = B_Tree("D")
e = B_Tree("E")
f = B_Tree("F")
g = B_Tree("G")

a.left = b
b.left = c
b.right = d
d.left = e
d.right = f
e.right = g

a.generate_pre_order()

print(a.preorder)

a.generate_to_c()