// Python_Invoker_Module.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "PyInvoker.h"
#include "TreeStructure.h"
#include <windows.h>
#include <iostream>
#include <thread>


void str_replace(std::string &s1, const std::string &s2, const std::string &s3)
{
	std::string::size_type pos = 0;
	std::string::size_type a = s2.size();
	std::string::size_type b = s3.size();
	while ((pos = s1.find(s2, pos)) != std::string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
}


std::string GetCurrentDir()
{
	char path[MAX_PATH];

	if (GetModuleFileNameA(NULL, path, MAX_PATH) > 0)
	{
		std::string cur_dir(path);
		str_replace(cur_dir, "\\", "/");
		auto last_pos = cur_dir.find_last_of("/");
		cur_dir = cur_dir.substr(0, last_pos + 1);
		return cur_dir;
	}
	else
		return "";
}


void RepeatedAdd(int count)
{
	std::vector<int> parasInt;
	for (int i = count; i <= count + 100; i++)
	{
		parasInt.push_back(i);
		parasInt.push_back(i + 10);
		PyInvoker::RunParasFunc("PythonCalc", "Add", parasInt);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		parasInt.clear();
	}
}

/*
int main()
{
if (!PyInvoker::Initialize())
{
std::cout << "----Python Enviorment Initialized Failed!----" << std::endl;
return -1;
}


//std::cout << "----Trail----" << std::endl;
//PyInvoker::Trail();


PyInvoker::ImportModule(GetCurrentDir() + "pyscripts");


PyInvoker::RunFunc("PythonGreet", "Hello");


//std::vector<int> parasInt;
//parasInt.push_back(3);
//parasInt.push_back(4);
//std::cout << "Result = " << PyInvoker::RunParasFunc("PythonCalc", "Add", parasInt) << std::endl;

std::vector<int> parasInt;
parasInt.push_back(3);
parasInt.push_back(4);
std::cout << "Result = " << PyInvoker::Add<int>("PythonCalc", "Add", parasInt) << std::endl;

std::vector<float> parasFloat;
parasFloat.push_back((float)2.7);
parasFloat.push_back((float)3.1);
std::cout << "Result = " << PyInvoker::Add<float>("PythonCalc", "Add", parasFloat) << std::endl;

std::vector<std::string> parasString;
parasString.push_back(std::string("Hello "));
parasString.push_back(std::string("world!"));
std::cout << "Result = " << PyInvoker::Add<std::string>("PythonCalc", "Add", parasString).c_str() << std::endl;


std::vector<CustomType> parasList;
CustomType One;
One.push_back(std::string("The "));
One.push_back(std::string("World "));
CustomType Two;
Two.push_back(std::string("is "));
Two.push_back(std::string("Font!"));
parasList.push_back(One);
parasList.push_back(Two);
CustomType resultList = PyInvoker::Add<CustomType>("PythonCalc", "Add", parasList);

std::cout << "list after merged:" << std::endl;
for (CustomType::iterator iter = resultList.begin(); iter != resultList.end(); ++iter)
{
std::cout << (*iter).c_str() << std::endl;
}

PyInvoker::Finalize();
return 0;
}
*/


int main()
{
	//Generate BTree By Preorder List
	/*std::list<std::string> NList{ "A", "B", "C", "*", "*", "D", "E", "*", "G", "H", "*", "*", "I", "*", "*", "F", "J", "*", "*", "*" };
	BinaryTree<std::string> bTree("*");
	bTree.GenerateByPreorder(NList);

	std::cout << "----Preorder----" << std::endl;
	bTree.Preorder();
	std::cout << " " << std::endl;

	std::cout << "----Inorder----" << std::endl;
	bTree.Inorder();
	std::cout << " " << std::endl;

	std::cout << "----Postorder----" << std::endl;
	bTree.Postorder();
	std::cout << " " << std::endl;

	std::cout << "----BTree Convert to Tree----" << std::endl;
	std::shared_ptr<Tree<std::string>> tree(ConverttoTree<std::string>(&bTree));
	tree->Levelorder();*/

	/////////////////////////////////////////////
	if (!PyInvoker::Initialize())
	{
		std::cout << "----Python Enviorment Initialized Failed!----" << std::endl;
		return -1;
	}

	PyInvoker::ImportModule(GetCurrentDir());

	PyInvoker::RunFunc("PythonTree", "btree_to_tree");

	PyInvoker::Finalize();
	return 0;
}

