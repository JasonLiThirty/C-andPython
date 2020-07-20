#ifndef TREE_STRUCTURE_H
#define TREE_STRUCTURE_H

#include<list>
#include<queue>
#include<iostream>

template<typename T>
struct BinaryNode
{
public:
	BinaryNode(T info, BinaryNode<T> *left = nullptr, BinaryNode<T> *right = nullptr) :
		data(info), leftChild(left), rightChild(right) {}

	T data;
	BinaryNode<T> *leftChild;
	BinaryNode<T> *rightChild;
};

template<typename T>
class BinaryTree
{
public:
	BinaryTree(BinaryNode<T> *node) :m_rootNode(node) {}
	BinaryTree(T flag) : m_rootNode(nullptr)
	{
		m_ignoreSign = flag;
	}
	~BinaryTree() { Free(m_rootNode); }


	void GenerateByPreorder(std::list<T> &nodeList)
	{
		GenerateByPreorder(nodeList, m_rootNode);
	}


	void Preorder()
	{
		Preorder(m_rootNode);
	}


	void Inorder()
	{
		Inorder(m_rootNode);
	}


	void Postorder()
	{
		Postorder(m_rootNode);
	}

	BinaryNode<T> *Root()
	{
		return m_rootNode;
	}

private:
	void Free(BinaryNode<T> *node)
	{
		if (node != nullptr)
		{
			Free(node->leftChild);
			Free(node->rightChild);
			delete node;
			node = nullptr;
		}
	}

	void GenerateByPreorder(std::list<T> &nodeList, BinaryNode<T> *&node)
	{
		if (!nodeList.empty())
		{
			auto item = nodeList.front();
			nodeList.pop_front();


			if (item != m_ignoreSign)
			{
				node = new BinaryNode<T>(item);
				GenerateByPreorder(nodeList, node->leftChild);
				GenerateByPreorder(nodeList, node->rightChild);
			}
			else
			{
				node = nullptr;
			}
		}
	}


	void Preorder(BinaryNode<T> *&node)
	{
		if (node != nullptr)
		{
			std::cout << node->data << "";
			Preorder(node->leftChild);
			Preorder(node->rightChild);
		}
	}


	void Inorder(BinaryNode<T> *&node)
	{
		if (node != nullptr)
		{
			Inorder(node->leftChild);
			std::cout << node->data << "";
			Inorder(node->rightChild);
		}
	}


	void Postorder(BinaryNode<T> *&node)
	{
		if (node != nullptr)
		{
			Postorder(node->leftChild);
			Postorder(node->rightChild);
			std::cout << node->data << "";
		}
	}


private:
	BinaryNode<T> *m_rootNode;
	T			   m_ignoreSign;
};




template<typename T>
struct TreeNode
{
public:
	TreeNode(T info) : data(info) { childList.clear(); }

	T data;
	std::list<TreeNode<T>*> childList;
};




template<typename T>
class Tree
{
public:
	Tree()
	{
		m_rootNode = nullptr;
	}

	Tree(TreeNode<T>* node)
	{
		m_rootNode = node;
	}

	~Tree() { Free(m_rootNode); }


	TreeNode<T> *Root()
	{
		return m_rootNode;
	}


	void Levelorder()
	{
		Levelorder(m_rootNode);
	}


protected:
	void Free(TreeNode<T> *node)
	{
		if (node != nullptr)
		{
			for (auto child : node->childList)
			{
				Free(child);
			}
			delete node;
			node = nullptr;
		}
	}


private:
	void Levelorder(TreeNode<T> *&node)
	{
		std::list<TreeNode<T>*> levelList;
		std::list<TreeNode<T>*> container;


		if (node == nullptr)
		{
			return;
		}


		if (node != nullptr)
		{
			container.push_back(node);
			while (container.size() > 0)
			{
				TreeNode<T>* tNode = container.front();
				levelList.push_back(tNode);
				for (auto &child : tNode->childList)
				{
					container.push_back(child);
				}
				container.pop_front();
			}
		}


		for (auto &item : levelList)
		{
			std::cout << item->data << "";
		}
	}


private:
	TreeNode<T> *m_rootNode;
};


template<typename T>
Tree<T>* ConverttoTree(BinaryTree<T>* BTree)
{
	return new Tree<T>(ConvertortoTree(BTree->Root()));
}


template<typename T>
TreeNode<T>* ConvertortoTree(BinaryNode<T>* BNode)
{
	if (BNode == nullptr)
	{
		return nullptr;
	}


	TreeNode<T>* node = new TreeNode<T>(BNode->data);
	BinaryNode<T> *left = BNode->leftChild;
	while (left != nullptr)
	{
		node->childList.push_back(ConvertortoTree(left));
		left = left->rightChild;
	}
	return node;
}


#endif // TREE_STRUCTURE_H