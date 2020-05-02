// Python_Invoker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>
#include <python.h>
#include <string>
#include <windows.h>
#include <iostream>
#include <vector>


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

bool RunPythonStatement()
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return false;
	}

	try
	{
		PyRun_SimpleString("import sys\n");
		PyRun_SimpleString("sys.stdout.write('Hello, Hello, Hello!\\n')\n");
		PyRun_SimpleString("sys.stdout.write('3 + 4 = {}\\n'.format(3+4))\n");
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
		Py_Finalize();
		return false;
	}
	Py_Finalize();
	return true;
}

//
bool InvokeNonParasFuncByAPI(std::string path, std::string module, std::string func)
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return false;
	}

	try
	{
		PyRun_SimpleString("import sys\n");
		std::string importDir = "sys.path.append('" + path + "')\n";
		PyRun_SimpleString(importDir.c_str());

		PyObject* moduleName = PyUnicode_FromString(module.c_str());
		PyObject* pModule = PyImport_Import(moduleName);
		if (!pModule)
		{
			std::cout << "Import Module Failed!" << std::endl;
			return false;
		}

		PyObject* pFunc = PyObject_GetAttrString(pModule, func.c_str());

		if (!pFunc || !PyCallable_Check(pFunc))
		{
			std::cout << "Get Function Failed!" << std::endl;
			return false;
		}

		PyObject* pResult = PyObject_CallObject(pFunc, nullptr);

		if (!pResult)
		{
			std::cout << "Get Result of Function Failed!" << std::endl;
			return false;
		}
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
		Py_Finalize();
		return false;
	}
	Py_Finalize();
	return true;
}


bool InvokeFuncbyAPI(std::string path, std::string module, std::string func, std::vector<int> paras)
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return false;
	}

	try
	{
		PyRun_SimpleString("import sys\n");
		std::string importDir = "sys.path.append('" + path + "')\n";
		PyRun_SimpleString(importDir.c_str());

		PyObject* moduleName = PyUnicode_FromString(module.c_str());
		PyObject* pModule = PyImport_Import(moduleName);
		if (!pModule)
		{
			std::cout << "Import Module Failed!" << std::endl;
			return false;
		}

		PyObject* pFunc = PyObject_GetAttrString(pModule, func.c_str());

		if (!pFunc || !PyCallable_Check(pFunc))
		{
			std::cout << "Get Function Failed!" << std::endl;
			return false;
		}

		PyObject* pResult = nullptr;

		PyObject* args = PyTuple_New((int)paras.size());
		for (int i = 0; i < (int)paras.size(); i++)
		{
			PyTuple_SetItem(args, i, PyLong_FromLong(paras[i]));
		}

		pResult = PyObject_CallObject(pFunc, args);

		if (!pResult)
		{
			std::cout << "Get Result of Function Failed!" << std::endl;
			return false;
		}

		std::cout << "Result = " << PyLong_AsLong(pResult) << " by python api" << std::endl;
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
		Py_Finalize();
		return false;
	}
	Py_Finalize();
	return true;
}

bool InvokeNonParasFuncByBoost(std::string path, std::string module, std::string func)
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return false;
	}

	try
	{
		PyRun_SimpleString("import sys\n");
		std::string importDir = "sys.path.append('" + path + "')\n";
		PyRun_SimpleString(importDir.c_str());

		boost::python::object pyModule(boost::python::import(module.c_str()));
		pyModule.attr(func.c_str())();

	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
		Py_Finalize();
		return false;
	}
	Py_Finalize();
	return true;
}


bool InvokeFuncbyBoost(std::string path, std::string module, std::string func, std::vector<int> paras)
{
	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return false;
	}

	try
	{
		PyRun_SimpleString("import sys\n");
		std::string importDir = "sys.path.append('" + path + "')\n";
		PyRun_SimpleString(importDir.c_str());

		boost::python::object pyModule(boost::python::import(module.c_str()));
		boost::python::object pyResult(pyModule.attr(func.c_str())(boost::python::object(paras[0]), boost::python::object(paras[1])));
		std::cout << "Result = " << boost::python::extract<int32_t>(pyResult) << " by boost::python" << std::endl;

	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
		Py_Finalize();
		return false;
	}
	Py_Finalize();
	return true;
}


int main()
{
	/*std::cout << "----Run Python Statement----" << std::endl;
	RunPythonStatement()*/;


	std::vector<int> paras;
	paras.push_back(3);
	paras.push_back(4);

	/*std::cout << "----Invoke Python Script by API----" << std::endl;
	InvokeNonParasFuncByAPI(GetCurrentDir() + "pyscripts", "PythonGreet", "Hello");
	InvokeFuncbyAPI(GetCurrentDir() + "pyscripts", "PythonCalc", "Add", paras);*/

	std::cout << "----Invoke Python Script by boost::python----" << std::endl;
	InvokeNonParasFuncByBoost(GetCurrentDir() + "pyscripts", "PythonGreet", "Hello");
	InvokeFuncbyBoost(GetCurrentDir() + "pyscripts", "PythonCalc", "Add", paras);
	return 0;
}
