#include "StdAfx.h"
#include "GameLib/GameEventManager.h"

PyObject * eventMgrUpdate(PyObject * poSelf, PyObject * poArgs)
{
	float fx;
	if (!PyTuple_GetFloat(poArgs, 0, &fx))
		return Py_BuildException();
	float fy;
	if (!PyTuple_GetFloat(poArgs, 1, &fy))
		return Py_BuildException();
	float fz;
	if (!PyTuple_GetFloat(poArgs, 2, &fz))
		return Py_BuildException();

	CGameEventManager::Instance().SetCenterPosition(fx, fy, fz);
	CGameEventManager::Instance().Update();
	return Py_BuildNone();
}

#ifdef PYTHON_3
PyMODINIT_FUNC PyInit_eventMgr(void)
#else
void initeventmgr()
#endif
{
	static PyMethodDef s_methods[] = 
	{
		{ "Update",					eventMgrUpdate,					METH_VARARGS },
		{ NULL,						NULL,							NULL },
	};

#ifdef PYTHON_3
	static PyModuleDef eventMgrmodule = {
		PyModuleDef_HEAD_INIT,
		"eventMgr",
		NULL,
		-1,
		s_methods
	};

	return PyModule_Create(&eventMgrmodule);
#else
	Py_InitModule("eventMgr", s_methods);
#endif
}