// C++_Python_Wrapper.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#define BOOST_PYTHON_STATIC_LIB
#define BOOST_NUMPY_STATIC_LIB

#include <boost/python.hpp>
//#include <boost/python/numpy/ndarray.hpp>

#include "ExportDefinition.h"


BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(CalculatorPro_overloads, Func, 1, 3);
BOOST_PYTHON_FUNCTION_OVERLOADS(FuncofDefaultParas_overload, FuncofDefaultParas, 1, 3);


BOOST_PYTHON_MODULE(Python_Wrapper)
{
	boost::python::class_<BNodeWrapper>("BNodeWrapper", boost::python::init<>())
		.def("Data", &BNodeWrapper::Data)
		.def("HaveLeft", &BNodeWrapper::HaveLeft)
		.def("HaveRight", &BNodeWrapper::HaveRight)
		.def("Left", &BNodeWrapper::Left)
		.def("Right", &BNodeWrapper::Right);

	boost::python::class_<BTreeWrapper>("BTreeWrapper", boost::python::init<std::string>())
		.def("Generate", &BTreeWrapper::Generate)
		.def("Preorder", &BTreeWrapper::Preorder)
		.def("Inorder", &BTreeWrapper::Inorder)
		.def("Postorder", &BTreeWrapper::Postorder)
		.def("Root", &BTreeWrapper::Root);

	boost::python::class_<NodeWrapper>("NodeWrapper", boost::python::init<>())
		.def("Data", &NodeWrapper::Data)
		.def("Child", &NodeWrapper::Child);

	boost::python::class_<TreeWrapper>("TreeWrapper", boost::python::init<>())
		.def("Levelorder", &TreeWrapper::Levelorder)
		.def("Root", &TreeWrapper::Root);

	boost::python::def("BTreetoTree", BTreetoTree, boost::python::return_value_policy<boost::python::manage_new_object>());
	/*
	//function
	boost::python::def("greet", greet);

	//const

	boost::python::scope newScope = boost::python::class_<Message>("Message")
	.def("Set", &Message::Set)
	.def("Get", &Message::Get);

	boost::python::scope().attr("yes") = 1;
	boost::python::scope().attr("no") = 0;

	//enum
	boost::python::enum_<MessageType>("MessageType")
	.value("MT_START", MT_START)
	.value("MT_PROCESS", MT_PROCESS)
	.value("MT_DONE", MT_DONE)
	.value("MT_EXCEPTION", MT_EXCEPTION);



	//struct
	boost::python::class_<StructionData>("StructionData")
	.def("hello", &StructionData::hello)
	.def("printmsg", &StructionData::printmsg);

	//class of default constructor
	boost::python::class_<Message>("Message")
	.def("Set", &Message::Set)
	.def("Get", &Message::Get);


	//class of custom constructor
	boost::python::class_<Sum>("Sum", boost::python::init<std::string>())
	.def(boost::python::init<double, double>())
	.def("Set", &Sum::Set)
	.def("Get", &Sum::Get)
	.def("Result", &Sum::Result);

	//data member of class
	boost::python::class_<User>("User", boost::python::init<std::string>())
	.def_readonly("name", &User::m_name)
	.def_readwrite("number", &User::m_number);

	//add properties to class
	boost::python::class_<MessagePro>("MessagePro")
	.add_property("info", &MessagePro::Get, &MessagePro::Set);

	//inherited
	boost::python::class_<Base>("Base", boost::python::init<>())
	.def("Name", &Base::Name);

	boost::python::class_<Derived, boost::python::bases<Base>>("Derived")
	.def("Name", &Derived::Name);

	boost::python::def("BaseName", BaseName);
	boost::python::def("DerivedName", DerivedName);

	boost::python::def("factory", factory, boost::python::return_value_policy<boost::python::manage_new_object>());

	//virtual function
	boost::python::class_<VFObjWrapper, boost::noncopyable>("VFObj")
	.def("Func", &VFObj::Func, &VFObjWrapper::Func);

	//pure virtual function
	boost::python::class_<PVFObjWrapper, boost::noncopyable>("PVFObj")
	.def("Func", boost::python::pure_virtual(&PVFObj::Func));

	//operator
	boost::python::class_<Operand>("Operand", boost::python::init<>())
	.def(boost::python::init<int>())
	.def("num", &Operand::num)
	.def(boost::python::self + boost::python::self)
	.def(boost::python::self + int())
	.def(boost::python::self - boost::python::self)
	.def(boost::python::self - int())
	.def(boost::python::self += boost::python::self)
	.def(boost::python::self += int())
	.def(boost::python::self -= boost::python::self)
	.def(boost::python::self -= int())
	.def(boost::python::self < boost::python::self)
	.def("abs", &Operand::abs)
	.def(str(boost::python::self));

	//function overload of class
	boost::python::class_<Calculator>("Calculator", boost::python::init<>())
	.def("Func", Func1)
	.def("Func", Func2)
	.def("Func", Func3);

	//function's default parameters of class
	boost::python::class_<CalculatorPro>("CalculatorPro", boost::python::init<>())
	.def(boost::python::init<int, boost::python::optional<double, int>>())
	.def("Func", &CalculatorPro::Func, CalculatorPro_overloads())
	.def("Value", &CalculatorPro::Value);

	//function's default parameters
	boost::python::def("FuncofDefaultParas", FuncofDefaultParas, FuncofDefaultParas_overload());

	//smart point;
	boost::python::class_<Data>("Data", boost::python::init<>())
	.def("Set", &Data::Set)
	.def("Get", &Data::Get);

	boost::python::register_ptr_to_python<DataPtr>();

	boost::python::scope().attr("pData") = pData;



	//////////////////////////////////////////////////////////

	//
	boost::python::class_<A>("A", boost::python::init<>())
	.def_readwrite("value", &A::value);

	boost::python::class_<B>("B", boost::python::init<>())
	.def_readwrite("a", &B::a);

	boost::python::def("getA", getA, boost::python::return_internal_reference<1>());
	//boost::python::def("getA", getA, boost::python::return_value_policy<boost::python::reference_existing_object>());


	boost::python::class_<C>("C", boost::python::init<>())
	.def_readwrite("value", &C::value);

	boost::python::def("getC", getC, boost::python::return_value_policy<boost::python::manage_new_object>());


	boost::python::class_<D>("D", boost::python::init<>())
	.def_readwrite("value", &D::value);

	boost::python::def("getD", getStaticD, boost::python::return_value_policy<boost::python::reference_existing_object>());

	boost::python::class_<E>("E", boost::python::init<>())
	.def_readwrite("value", &E::value);

	//boost::python::class_<E>("EClone", boost::python::init<>())
	//	.def_readwrite("value", &E::value);
	*/
}


