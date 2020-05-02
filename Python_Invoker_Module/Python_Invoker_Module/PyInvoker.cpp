#include "PyInvoker.h"
#include <iostream>
#include <thread>


#define PYTHON_IMPORT_SYS			"import sys\n"
#define PYTHON_IMPORT_DIR_PREF		"sys.path.append('"
#define PYTHON_IMPORT_DIR_SUF		"')\n"


bool PyInvoker::Initialize()
{
	Py_Initialize();
	if (!Py_IsInitialized())
	{
		return false;
	}

	PyEval_InitThreads();
	PyEval_ReleaseThread(PyThreadState_Get());
	return true;
}


void PyInvoker::Finalize()
{
	PyGILState_Ensure();
	Py_Finalize();
}


void PyInvoker::Trail()
{
	PyLock lock;
	try
	{
		PyRun_SimpleString(PYTHON_IMPORT_SYS);
		PyRun_SimpleString("sys.stdout.write('Hello, Hello, Hello!\\n')\n");
		PyRun_SimpleString("sys.stdout.write('3 + 4 = {}\\n'.format(3+4))\n");
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
}


void PyInvoker::ImportModule(std::string path)
{
	PyLock lock;
	try
	{
		PyRun_SimpleString(PYTHON_IMPORT_SYS);
		std::string dir = PYTHON_IMPORT_DIR_PREF + path + PYTHON_IMPORT_DIR_SUF;
		PyRun_SimpleString(dir.c_str());
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
}

void PyInvoker::RunFunc(std::string module, std::string func)
{
	PyLock lock;
	try
	{
		boost::python::object pyModule(boost::python::import(module.c_str()));
		pyModule.attr(func.c_str())();
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
}

int PyInvoker::RunParasFunc(std::string module, std::string func, std::vector<int> paras)
{
	PyLock lock;
	int result = -1;
	try
	{
		boost::python::object pyModule(boost::python::import(module.c_str()));
		boost::python::object pyResult(pyModule.attr(func.c_str())(boost::python::object(paras[0]), boost::python::object(paras[1])));

		result = boost::python::extract<int>(pyResult);

		std::cout << "Thread = " << std::this_thread::get_id() << " Result = " << result << std::endl;
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
	return result;
}

void PyInvoker::RunCounterFunc(std::string module, std::string func)
{
	PyLock lock;
	try
	{
		boost::python::object pyModule(boost::python::import(module.c_str()));
		boost::python::object pyResult(pyModule.attr(func.c_str())());

		int result = boost::python::extract<int>(pyResult);
		std::cout << "Thread = " << std::this_thread::get_id() << "Result = " << result << std::endl;
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
}
