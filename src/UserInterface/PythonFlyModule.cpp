#include "stdafx.h"
#include "GameLib/FlyingObjectManager.h"

PyObject * flyUpdate(PyObject * poSelf, PyObject * poArgs)
{
	CFlyingManager::Instance().Update();
	return Py_BuildNone();
}

PyObject * flyRender(PyObject * poSelf, PyObject * poArgs)
{
	CFlyingManager::Instance().Render();
	return Py_BuildNone();
}

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_fly(void)
#else
void initfly()
#endif
{
	static PyMethodDef s_methods[] =
	{
		{ "Update",						flyUpdate,					METH_VARARGS },
		{ "Render",						flyRender,					METH_VARARGS },
		
		{ NULL,							NULL,							NULL         },
	};

#ifdef PYTHON_3
	static PyModuleDef flymodule = {
		PyModuleDef_HEAD_INIT,
		"fly",
		NULL,
		-1,
		s_methods
	};

	return PyModule_Create(&flymodule);
#else	
	Py_InitModule("fly", s_methods);
#endif
}