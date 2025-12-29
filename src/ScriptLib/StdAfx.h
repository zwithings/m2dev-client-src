#pragma once

#include "EterLib/StdAfx.h"
#include "EterGrnLib/StdAfx.h"

// Required for Python 3.10+ - must be defined before Python.h
#ifdef PYTHON_3
	#define PY_SSIZE_T_CLEAN
#endif

//#include <crtdbg.h>
#ifdef _DEBUG
	#undef _DEBUG
	#ifdef PYTHON_3
		#include <Python.h>
	#else
		#include <python/python.h>
	#endif
	#define _DEBUG
#else
	#ifdef PYTHON_3
		#include <Python.h>
	#else
		#include <python/python.h>
	#endif
#endif

#ifdef PYTHON_3
	// Python 3.12 compatibility - headers available in Python.h
	#include <compile.h>
	#include <marshal.h>
	
	// Python 3 compatibility macros - map old Python 2 API to Python 3 API
	// String functions (PyString_* -> PyUnicode_*)
	#define PyString_FromString         PyUnicode_FromString
	#define PyString_FromStringAndSize  PyBytes_FromStringAndSize
	#define PyString_AsString           PyUnicode_AsUTF8
	#define PyString_AS_STRING          PyUnicode_AsUTF8
	#define PyString_Check              PyUnicode_Check
	#define PyString_Size               PyUnicode_GET_LENGTH
	#define PyString_GET_SIZE           PyUnicode_GET_LENGTH
	#define PyString_InternFromString   PyUnicode_InternFromString
	
	// Integer functions (PyInt_* -> PyLong_*)
	#define PyInt_FromLong          PyLong_FromLong
	#define PyInt_AsLong            PyLong_AsLong
	#define PyInt_AS_LONG           PyLong_AS_LONG
	#define PyInt_Check             PyLong_Check
	#define PyInt_CheckExact        PyLong_CheckExact
	
	// File functions (removed in Python 3)
	#define PyFile_Check(op)        (0)
	
#else
	#include <python/node.h>
	#include <python/grammar.h>
	#include <python/token.h>
	#include <python/parsetok.h>
	#include <python/errcode.h>
	#include <python/compile.h>
	#include <python/eval.h>
	#include <python/marshal.h>
#endif

#ifdef BYTE
#undef BYTE
#endif

#include "PythonUtils.h"
#include "PythonLauncher.h"
#include "PythonMarshal.h"
#include "Resource.h"

#ifdef PYTHON_3
	PyMODINIT_FUNC PyInit_dbg(void);
#else
	void initdbg();
#endif

// PYTHON_EXCEPTION_SENDER
class IPythonExceptionSender
{
	public:
		void Clear()
		{
			m_strExceptionString = "";
		}

		void RegisterExceptionString(const char * c_szString)
		{
			m_strExceptionString += c_szString;
		}

		virtual void Send() = 0;

	protected:
		std::string m_strExceptionString;
};

extern IPythonExceptionSender * g_pkExceptionSender;

void SetExceptionSender(IPythonExceptionSender * pkExceptionSender);
// END_OF_PYTHON_EXCEPTION_SENDER
