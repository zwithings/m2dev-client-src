#include "StdAfx.h"
#include "PythonNetworkDatagram.h"
/*
PyObject * udpEnable(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkDatagram::Instance().Enable();
	return Py_BuildNone();
}

PyObject * udpDisable(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkDatagram::Instance().Disable();
	return Py_BuildNone();
}
*/

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_udp(void)
{
	/*
	static PyMethodDef s_methods[] =
	{
		{ "Enable",		udpEnable,					METH_VARARGS },
		{ "Disable",	udpDisable,					METH_VARARGS },
		
		{ NULL,						NULL,							NULL		 }
	};

	static PyModuleDef udpmodule = {
		PyModuleDef_HEAD_INIT,
		"udp",
		NULL,
		-1,
		s_methods
	};

	return PyModule_Create(&udpmodule);
	*/
	Py_RETURN_NONE;
}
#else
void initudp()
{
	/*
	static PyMethodDef s_methods[] =
	{
		{ "Enable",		udpEnable,					METH_VARARGS },
		{ "Disable",	udpDisable,					METH_VARARGS },
		
		{ NULL,						NULL,							NULL		 }
	};

	PyObject * poModule = Py_InitModule("udp", s_methods);
	*/
}
#endif
