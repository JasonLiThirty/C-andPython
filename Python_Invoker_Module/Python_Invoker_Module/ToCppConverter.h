#ifndef TO_CPP_CONVERTER_H
#define TO_CPP_CONVERTER_H

#include "Common.h"
#include <boost/python.hpp>
#include <list>
#include <string>

template<class T>
struct ToCpp
{
	boost::python::object obj;

	ToCpp(boost::python::object data) :obj(data)
	{
		;
	}

	operator T()
	{
		return boost::python::extract<T>(obj);
	}
};


template<>
struct ToCpp<CustomType>
{
	boost::python::object obj;
	ToCpp(boost::python::object data) :obj(data)
	{
		;
	}

	operator CustomType()
	{
		CustomType cppList;
		boost::python::list pyList = boost::python::extract<boost::python::list>(obj);
		for (int i = 0; i < boost::python::len(pyList); i++)
		{
			std::string value = boost::python::extract<std::string>(pyList[i]);
			cppList.push_back(value);
		}
		return cppList;
	}
};


#endif