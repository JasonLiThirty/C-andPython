#ifndef TO_PY_CONVERTER_H
#define TO_PY_CONVERTER_H

#include "Common.h"
#include <boost/python.hpp>
#include <list>
#include <string>


template<class T>
struct ToPy
{
	boost::python::object obj;

	ToPy(T data)
	{
		obj = boost::python::object(data);
	}

	operator boost::python::object()
	{
		return obj;
	}
};


template<>
struct ToPy<CustomType>
{
	boost::python::object obj;

	ToPy(CustomType data)
	{
		boost::python::list pyList;
		for (CustomType::iterator iter = data.begin(); iter != data.end(); ++iter)
		{
			pyList.append(boost::python::object(*iter));
		}
		obj = pyList;
	}

	operator boost::python::object()
	{
		return obj;
	}
};

#endif