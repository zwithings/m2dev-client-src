#include "StdAfx.h"

extern IPythonExceptionSender * g_pkExceptionSender;

PyObject* dbgLogBox(PyObject* poSelf, PyObject* poArgs)
{	
	char* szMsg;
	char* szCaption;
	if (!PyTuple_GetString(poArgs, 0, &szMsg))
		return Py_BuildException();
	if (!PyTuple_GetString(poArgs, 1, &szCaption))
	{
		LogBox(szMsg);
	}
	else
	{
		LogBox(szMsg,szCaption);
	}
	return Py_BuildNone();	
}

PyObject* dbgTrace(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg))
		return Py_BuildException();

	Trace(szMsg);
	return Py_BuildNone();
}

PyObject* dbgTracen(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg)) 
		return Py_BuildException();

	Tracen(szMsg);
	return Py_BuildNone();
}

PyObject* dbgTraceError(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg)) 
		return Py_BuildException();

	TraceError( "%s", szMsg );
	return Py_BuildNone();
}

PyObject* dbgRegisterExceptionString(PyObject* poSelf, PyObject* poArgs)
{
	char* szMsg;
	if (!PyTuple_GetString(poArgs, 0, &szMsg)) 
		return Py_BuildException();

	if (g_pkExceptionSender)
		g_pkExceptionSender->RegisterExceptionString(szMsg);

	return Py_BuildNone();
}

static PyMethodDef s_methods[] =
{
	{ "LogBox",						dbgLogBox,					METH_VARARGS },
	{ "Trace",						dbgTrace,					METH_VARARGS },
	{ "Tracen",						dbgTracen,					METH_VARARGS },
	{ "TraceError",					dbgTraceError,				METH_VARARGS },
	{ "RegisterExceptionString",	dbgRegisterExceptionString,	METH_VARARGS },
	{ NULL, NULL},
};

#ifdef PYTHON_3
static PyModuleDef dbgmodule = {
	PyModuleDef_HEAD_INIT,
	"dbg",
	"Debug module for logging and tracing",
	-1,
	s_methods,
	NULL,
	NULL,
	NULL,
	NULL
};

PyMODINIT_FUNC PyInit_dbg(void)
{
	return PyModule_Create(&dbgmodule);
}
#else
void initdbg()
{
	Py_InitModule("dbg", s_methods);
}
#endif