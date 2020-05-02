// Python_Invoker_Module.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "PyInvoker.h"
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

int main()
{
	if (!PyInvoker::Initialize())
	{
		std::cout << "----Python Enviorment Initialized Failed!----" << std::endl;
		return -1;
	}
	/*
	std::cout << "----Trail----" << std::endl;
	PyInvoker::Trail();
	*/

	std::cout << "----ImportModule----" << std::endl;
	PyInvoker::ImportModule(GetCurrentDir() + "pyscripts");


	//std::cout << "----Call PythonGreet----" << std::endl;
	//PyInvoker::RunFunc("PythonGreet", "Hello");


	//std::cout << "----Call PythonCalc(Add)----" << std::endl;
	//std::vector<int> parasInt;
	//parasInt.push_back(5);
	//parasInt.push_back(6);
	//PyInvoker::RunParasFunc("PythonCalc", "Add", parasInt);

	std::cout << "----Test MultiThread Begin----" << std::endl;
	std::thread* th[10];
	for (int i = 0; i < 10; i++)
	{
		th[i] = new std::thread([&]()
		{
			RepeatedAdd(i + 10);
		});
	}

	RepeatedAdd(-1000);

	for (int i = 0; i < 10; i++)
	{
		th[i]->join();
		delete th[i];
	}
	std::cout << "----Test MultiThread End----" << std::endl;

	PyInvoker::Finalize();

	return 0;
}
