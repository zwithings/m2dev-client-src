#include "StdAfx.h"
#include "EterLib/Profiler.h"

PyObject * profilerPush(PyObject * poSelf, PyObject * poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	return Py_BuildNone();
}

PyObject * profilerPop(PyObject * poSelf, PyObject * poArgs)
{
	char * szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();

	return Py_BuildNone();
}

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_profiler(void)
#else
void initProfiler()
#endif
{
	static PyMethodDef s_methods[] =
	{
		{ "Push",				profilerPush,				METH_VARARGS },
		{ "Pop",				profilerPop,				METH_VARARGS },

		{ NULL,					NULL,						NULL		 },
	};

#ifdef PYTHON_3
	static PyModuleDef profilermodule = {
		PyModuleDef_HEAD_INIT,
		"profiler",
		NULL,
		-1,
		s_methods
	};

	return PyModule_Create(&profilermodule);
#else
	Py_InitModule("profiler", s_methods);
#endif
}