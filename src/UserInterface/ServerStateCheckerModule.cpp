#include "StdAfx.h"
#include "ServerStateChecker.h"

PyObject * ServerStateCheckerCreate(PyObject* poSelf, PyObject* poArgs)
{
	PyObject * poWnd;
	if (!PyTuple_GetObject(poArgs, 0, &poWnd))
		return Py_BadArgument();

	CServerStateChecker::Instance().Create(poWnd);
	return Py_BuildNone();
}

PyObject * ServerStateCheckerUpdate(PyObject* poSelf, PyObject* poArgs)
{
	CServerStateChecker::Instance().Update();
	return Py_BuildNone();
}

PyObject * ServerStateCheckerRequest(PyObject* poSelf, PyObject* poArgs)
{
	CServerStateChecker::Instance().Request();
	return Py_BuildNone();
}

PyObject * ServerStateCheckerAddChannel(PyObject* poSelf, PyObject* poArgs)
{
	int nServerIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &nServerIndex))
		return Py_BuildException();

	char * szAddr;
	if (!PyTuple_GetString(poArgs, 1, &szAddr))
		return Py_BuildException();

	int nPort;
	if (!PyTuple_GetInteger(poArgs, 2, &nPort))
		return Py_BuildException();

	CServerStateChecker::Instance().AddChannel(nServerIndex, szAddr, nPort);
	return Py_BuildNone();
}

PyObject * ServerStateCheckerInitialize(PyObject* poSelf, PyObject* poArgs)
{
	CServerStateChecker::Instance().Initialize();
	return Py_BuildNone();
}

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_ServerStateChecker(void)
#else
void initServerStateChecker()
#endif
{
	static PyMethodDef s_methods[] =
	{
		{ "Create",		ServerStateCheckerCreate,		METH_VARARGS },
		{ "Update",		ServerStateCheckerUpdate,		METH_VARARGS },
		{ "Request",	ServerStateCheckerRequest,		METH_VARARGS },
		{ "AddChannel",	ServerStateCheckerAddChannel,	METH_VARARGS },
		{ "Initialize",	ServerStateCheckerInitialize,	METH_VARARGS },
		{ NULL,			NULL,							NULL },
	};

#ifdef PYTHON_3
	static PyModuleDef ServerStateCheckermodule = {
		PyModuleDef_HEAD_INIT,
		"ServerStateChecker",
		NULL,
		-1,
		s_methods
	};

	return PyModule_Create(&ServerStateCheckermodule);
#else
	//PyObject * poModule = Py_InitModule("ServerStateChecker", s_methods);
	Py_InitModule("ServerStateChecker", s_methods);
#endif
}