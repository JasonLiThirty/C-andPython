import Python_Wrapper
from graphviz import Digraph
import datetime

NODE_ID = 0
def get_node_id():
    global NODE_ID
    NODE_ID += 1
    return NODE_ID

def bnode_visual(graph, node, parent_id, is_root = False):
    if node is not None:
        id = str(get_node_id())
        graph.node(id, node.Data())
        if not is_root:
            graph.edge(parent_id, id, splines='curved', fontsize='10', arrowType='vee')
        if node.HaveLeft():
            bnode_visual(graph, node.Left(), id)
        if node.HaveRight():
            bnode_visual(graph, node.Right(), id)
				
def btree_visual(btree_wrapper):
    dot = Digraph('Binary Tree', filename='Binary Tree', engine='dot')
    #dot.node_attr.update(style = 'filled', color='lightgrey')
    root = btree_wrapper.Root()
    bnode_visual(dot, root, 0, True)

    #dot.render('visualization/btree_visual.gv', view=True)
    return dot

def node_visual(graph, node, parent_id, is_root = False):
    if node is not None:
        id = str(get_node_id())
        graph.node(id, node.Data())
        if not is_root:
            graph.edge(parent_id, id, splines='curved', fontsize='10', arrowType='vee')        
        for child in node.Child():
            node_visual(graph, child, id)

def tree_visual(tree_wrapper):
    dot = Digraph('Tree', filename='Tree', engine='dot')

    root = tree_wrapper.Root()
    node_visual(dot, root, 0, True)

    #dot.render('visualization/tree_visual.gv', view=True)
    return dot
    
def arrow_visual():
    dot = Digraph('Arrow', filename='Arrow', engine='dot')
    dot.node('arrow', 'Conversion', width = '5' ,fontname = 'bold', fontsize='20', style = 'filled', color = 'lightgrey', shape = 'rarrow')
    return dot

def visualization(btree_wrapper, tree_wrapper):
    graph = Digraph('Visual', comment='Visual', engine='dot')
    graph.subgraph(btree_visual(btree_wrapper))
    graph.subgraph(arrow_visual())
    graph.subgraph(tree_visual(tree_wrapper))
    file = 'visualization/' + datetime.datetime.now().strftime('%H-%M-%S')
    graph.render(file, view=True)