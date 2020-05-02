#ifndef PY_INVOKER_H
#define PY_INVOKER_H

#define BOOST_PYTHON_STATIC_LIB

#include <boost/python.hpp>
#include <python.h>
#include <thread>
#include <vector>
#include <string>


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
	static void RunCounterFunc(std::string module, std::string func);

};

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

