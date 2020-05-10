#ifndef PY_INVOKER_H
#define PY_INVOKER_H

#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>
#include <python.h>
#include <vector>
#include <string>
#include <list>
#include "ToPyConverter.h"
#include "ToCppConverter.h"


class _declspec(dllexport) PyInvoker
{
public:
	PyInvoker() {};
	~PyInvoker() {};


	static bool Initialize();
	static void Finalize();
	static void ImportModule(std::string path);
	static void Trail();
	static void RunFunc(std::string module, std::string func);
	static int RunParasFunc(std::string module, std::string func, std::vector<int> paras);


	template<class T>
	static T Add(std::string module, std::string func, std::vector<T> paras);
};

/*
template<class T>
T PyInvoker::Add(std::string module, std::string func, std::vector<T> paras)
{
	PyLock lock;
	T result;
	try
	{
		boost::python::object pyModule(boost::python::import(module.c_str()));
		boost::python::object pyResult(pyModule.attr(func.c_str())(boost::python::object(paras[0]), boost::python::object(paras[1])));

		result = boost::python::extract<T>(pyResult);
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
	return result;
}
*/


template<class T>
T PyInvoker::Add(std::string module, std::string func, std::vector<T> paras)
{
	PyLock lock;
	T result;
	try
	{
		boost::python::object pyModule(boost::python::import(module.c_str()));
		boost::python::object paramOne = ToPy<T>(paras[0]);
		boost::python::object paramTwo = ToPy<T>(paras[1]);
		boost::python::object pyResult(pyModule.attr(func.c_str())(paramOne, paramTwo));


		result = ToCpp<T>(pyResult);
	}
	catch (...)
	{
		PyErr_Print();
		PyErr_Clear();
	}
	return result;
}


class _declspec(dllexport) PyLock
{
public:
	PyLock()
	{
		m_state = PyGILState_Ensure();
	}


	~PyLock()
	{
		PyGILState_Release(m_state);
	}
private:
	PyGILState_STATE m_state;
};


#endif //PY_INVOKER_H