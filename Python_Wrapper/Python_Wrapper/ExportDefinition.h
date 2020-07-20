#ifndef EXPORT_DEFINITION_H
#define EXPORT_DEFINITION_H

#include<iostream>
#include<string>
#include<ostream>
#include <memory.h>
#include <list>
#include"TreeStructure.h"

char const* greet()
{
	return "Hello world!";
}

class Message
{
public:
	void Set(std::string msg)
	{
		m_msg = msg;
	}

	std::string Get()
	{
		return m_msg;
	}

private:
	std::string m_msg;
};

enum MessageType
{
	MT_START = 1,
	MT_PROCESS,
	MT_DONE,
	MT_EXCEPTION
};



struct StructionData
{
	void hello()
	{
		std::cout << "hello, this is boost::python sample!" << std::endl;
	}
	void printmsg()
	{
		std::cout << "print message done!" << std::endl;
	}
};

class Sum
{
public:
	Sum(std::string data) :m_data(data) {}
	Sum(double a, double b) :m_a(a), m_b(b) {}

	void Set(std::string data)
	{
		m_data = data;
	}

	std::string Get()
	{
		return m_data;
	}

	double Result()
	{
		return m_a + m_b;
	}
private:
	std::string m_data;
	double m_a;
	double m_b;
};


class User
{
public:
	User(std::string name) :m_name(name), m_number(-1) {}
	std::string m_name;
	int m_number;
};

class MessagePro
{
public:
	void Set(std::string msg)
	{
		m_msg = msg;
	}

	std::string Get()
	{
		return m_msg;
	}

private:
	std::string m_msg;
};

//
class Base
{
public:
	virtual ~Base() {};
	virtual std::string Name()
	{
		return "Base";
	}
};


class Derived : public Base
{
public:
	std::string Name()
	{
		return "Derived";
	}
};

void BaseName(Base *base)
{
	std::cout << base->Name().c_str() << std::endl;
}

void DerivedName(Derived *derived)
{
	std::cout << derived->Name().c_str() << std::endl;
}

Base *factory()
{
	return new Derived();
}

//
class VFObj
{
public:
	virtual ~VFObj() {};
	virtual int Func() { return 0; }
};

class VFObjWrapper : public VFObj, public boost::python::wrapper<VFObj>
{
public:
	int Func()
	{
		if (boost::python::override Func = this->get_override("Func"))
		{
			return Func();
		}
		return VFObj::Func();
	}

	int default_Func()
	{
		return this->VFObj::Func();
	}
};

class PVFObj
{
public:
	virtual ~PVFObj() {}
	virtual int Func() = 0;
};

class PVFObjWrapper : public PVFObj, public boost::python::wrapper<PVFObj>
{
public:
	int Func()
	{
		return this->get_override("Func")();
	}
};


//
class Operand
{
public:
	Operand() :m_num(0) {}
	Operand(int num) :m_num(num) {}

	int num()
	{
		return m_num;
	}

	Operand& operator+(const Operand& other)
	{
		m_num += other.m_num;
		return *this;
	}

	Operand& operator+(int num)
	{
		m_num += num;
		return *this;
	}

	Operand& operator-(const Operand& other)
	{
		m_num -= other.m_num;
		return *this;
	}

	Operand& operator-(int num)
	{
		m_num -= num;
		return *this;
	}

	Operand& operator+=(const Operand& other)
	{
		return operator+(other);
	}


	Operand& operator+=(int num)
	{
		return operator+(num);
	}

	Operand& operator-=(const Operand& other)
	{
		return operator-(other);
	}

	Operand& operator-=(int num)
	{
		return operator-(num);
	}

	bool operator<(const Operand& other)
	{
		return (m_num < other.m_num);
	}

	int abs()
	{
		m_num = std::abs(m_num);
		return m_num;
	}

private:
	int m_num;
};

std::ostream& operator<<(std::ostream& out, Operand opr)
{
	out << opr.num();
	return out;
}

//
class Calculator
{
public:

	int Func(int a)
	{
		return a;
	}

	int Func(int a, int b)
	{
		return a + b;
	}

	int Func(int a, int b, int c)
	{
		return a + b - c;
	}
};

int(Calculator::*Func1)(int) = &Calculator::Func;
int(Calculator::*Func2)(int, int) = &Calculator::Func;
int(Calculator::*Func3)(int, int, int) = &Calculator::Func;

//
class CalculatorPro
{
public:
	CalculatorPro()
	{
		m_value = 0.0;
	}

	CalculatorPro(int a, double b = 2.0, int c = 10)
	{
		m_value = a + b + c;
	}

	double Func(int a, double b = 3.0, int c = 5)
	{
		return a + b - c;
	}

	double Value()
	{
		return m_value;
	}

private:
	double m_value;
};


double FuncofDefaultParas(int a, double b = 2.0, double c = 3.0)
{
	return a + b + c;
}

//

class Data
{
public:
	void Set(int data)
	{
		m_data = data;
	}

	int Get()
	{
		return m_data;
	}

private:
	int m_data;
};

using DataPtr = std::shared_ptr<Data>;

DataPtr pData(new Data);

//


//
class A
{
public:
	int value;
};

class B
{
public:
	A a;
};

A& getA(B &b)
{
	return b.a;
}


class D
{
public:
	int value;
};


D& getStaticD()
{
	static D d;
	d.value = 10;
	return d;
}

class C
{
public:
	int value;
};

C* getC()
{
	return new C();
}

class E
{
public:
	int value;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class __declspec(dllexport) BNodeWrapper
{
public:
	BNodeWrapper()
	{
		node.reset(new BinaryNode<std::string>(""));
	}

	BNodeWrapper(BinaryNode<std::string> *other)
	{
		node.reset(other);
	}

	std::string Data()
	{
		return node->data;
	}

	BNodeWrapper Left()
	{
		return BNodeWrapper(node->leftChild);
	}

	BNodeWrapper Right()
	{
		return BNodeWrapper(node->rightChild);
	}

	bool HaveLeft()
	{
		return (node->leftChild != nullptr);
	}

	bool HaveRight()
	{
		return (node->rightChild != nullptr);
	}


private:
	std::shared_ptr<BinaryNode<std::string>> node;
};

class __declspec(dllexport) BTreeWrapper
{
public:
	BTreeWrapper(std::string flag)
	{
		bTree.reset(new BinaryTree<std::string>(flag));
	}

	void Generate(boost::python::list data)
	{
		std::list<std::string> NodeList;
		for (int i = 0; i < boost::python::len(data); i++)
		{
			std::string value = boost::python::extract<std::string>(data[i]);
			NodeList.push_back(value);
		}
		bTree->GenerateByPreorder(NodeList);
	}

	void Preorder()
	{
		bTree->Preorder();
	}

	void Inorder()
	{
		bTree->Inorder();
	}

	void Postorder()
	{
		bTree->Postorder();
	}

	BinaryTree<std::string>* Tree()
	{
		return bTree.get();
	}

	BNodeWrapper Root()
	{
		return BNodeWrapper(bTree->Root());
	}

private:
	std::shared_ptr<BinaryTree<std::string>> bTree;
};

class  __declspec(dllexport) NodeWrapper
{
public:
	NodeWrapper()
	{
		node.reset(new TreeNode<std::string>(""));
	}

	NodeWrapper(TreeNode<std::string> *other)
	{
		node.reset(other);
	}

	std::string Data()
	{
		return node->data;
	}

	boost::python::list Child()
	{
		boost::python::list childList;
		for (auto &child : node->childList)
		{
			childList.append(NodeWrapper(child));
		}
		return childList;
	}

private:
	std::shared_ptr<TreeNode<std::string>> node;
};

class __declspec(dllexport) TreeWrapper
{
public:
	TreeWrapper()
	{
		tree.reset(new Tree<std::string>());
	}

	TreeWrapper(Tree<std::string>* other)
	{
		tree.reset(other);
	}

	void Levelorder()
	{
		tree->Levelorder();
	}

	NodeWrapper Root()
	{
		return NodeWrapper(tree->Root());
	}

private:
	std::shared_ptr<Tree<std::string>> tree;
};


TreeWrapper* BTreetoTree(BTreeWrapper bTree)
{
	return new TreeWrapper(ConverttoTree<std::string>(bTree.Tree()));
}

#endif // ! EXPORT_DEFINITION_H