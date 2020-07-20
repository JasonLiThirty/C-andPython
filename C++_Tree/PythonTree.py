import Python_Wrapper
from TreeVisual import visualization

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

    def trans_to_c(self):
        btree_wrapper = Python_Wrapper.BTreeWrapper(B_Tree.ingore)
        btree_wrapper.Generate(B_Tree.preorder)
        return btree_wrapper
	
def convert_to_tree(btree_wrapper):
	return Python_Wrapper.BTreetoTree(btree_wrapper)


#call
def btree_to_tree():
    root = B_Tree("A")
    b = B_Tree("B")
    c = B_Tree("C")
    d = B_Tree("D")
    e = B_Tree("E")
    f = B_Tree("F")
    g = B_Tree("G")
    h = B_Tree("H")
    i = B_Tree("I")
    j = B_Tree("J")
    #k = B_Tree("K")
    #l = B_Tree("L")
    #m = B_Tree("M")
    #n = B_Tree("N")

    root.left = b
    b.left = c
    b.right = d
    d.left = e
    d.right = f
    e.right = g
    g.left = h
    g.right = i
    f.left = j
    #c.left = k
    #k.left = l
    #l.right = m
    #m.right = n

    root.generate_pre_order()
    print("----Preorder List----")
    print(root.preorder)

    c_btree = root.trans_to_c()
	
    print("\n")
    print("----Preorder----")
    c_btree.Preorder()
    print("\n")
    print("----Inorder----")
    c_btree.Inorder()
    print("\n")
    print("----Postorder----")
    c_btree.Postorder()
    print("\n")

    c_tree = convert_to_tree(c_btree)
    print("----Levelorder----")
    c_tree.Levelorder()

    #btree_visual(c_btree)
    #tree_visual(c_tree)
    visualization(c_btree, c_tree)