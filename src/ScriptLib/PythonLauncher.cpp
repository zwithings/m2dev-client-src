#include "StdAfx.h"
#ifdef PYTHON_3
#include "../UserInterface/StdAfx.h"
#include <frameobject.h>
#else
#include <python/frameobject.h>
#endif
#ifdef BYTE
#undef BYTE
#endif

#include "PackLib/PackManager.h"

#include "PythonLauncher.h"
#include <utf8.h>

CPythonLauncher::CPythonLauncher()
{
#ifdef PYTHON_3
	// Register all Python modules before Py_Initialize()
	// ScriptLib modules
	PyImport_AppendInittab("dbg", PyInit_dbg);
	
	// PackLib module
	PyImport_AppendInittab("pack", PyInit_pack);
	
	// EterPythonLib modules
	PyImport_AppendInittab("grp", PyInit_grp);
	PyImport_AppendInittab("grpImage", PyInit_grpImage);
	PyImport_AppendInittab("grpText", PyInit_grpText);
	PyImport_AppendInittab("grpThing", PyInit_grpThing);
	PyImport_AppendInittab("wndMgr", PyInit_wndMgr);
	
	// UserInterface modules
	PyImport_AppendInittab("udp", PyInit_udp);
	PyImport_AppendInittab("app", PyInit_app);
	PyImport_AppendInittab("ime", PyInit_ime);
	PyImport_AppendInittab("systemSetting", PyInit_systemSetting);
	PyImport_AppendInittab("chr", PyInit_chr);
	PyImport_AppendInittab("chrmgr", PyInit_chrmgr);
	PyImport_AppendInittab("player", PyInit_player);
	PyImport_AppendInittab("item", PyInit_item);
	PyImport_AppendInittab("nonplayer", PyInit_nonplayer);
	PyImport_AppendInittab("exchange", PyInit_exchange);
	PyImport_AppendInittab("chat", PyInit_chat);
	PyImport_AppendInittab("textTail", PyInit_textTail);
	PyImport_AppendInittab("net", PyInit_net);
	PyImport_AppendInittab("miniMap", PyInit_miniMap);
	PyImport_AppendInittab("profiler", PyInit_profiler);
	PyImport_AppendInittab("event", PyInit_event);
	PyImport_AppendInittab("effect", PyInit_effect);
	PyImport_AppendInittab("fly", PyInit_fly);
	PyImport_AppendInittab("snd", PyInit_snd);
	PyImport_AppendInittab("eventMgr", PyInit_eventMgr);
	PyImport_AppendInittab("shop", PyInit_shop);
	PyImport_AppendInittab("skill", PyInit_skill);
	PyImport_AppendInittab("quest", PyInit_quest);
	PyImport_AppendInittab("background", PyInit_background);
	PyImport_AppendInittab("messenger", PyInit_messenger);
	PyImport_AppendInittab("safebox", PyInit_safebox);
	PyImport_AppendInittab("guild", PyInit_guild);
	PyImport_AppendInittab("ServerStateChecker", PyInit_ServerStateChecker);
#endif
	Py_Initialize();
}

CPythonLauncher::~CPythonLauncher()
{
	Clear();
}

void CPythonLauncher::Clear()
{
	Py_Finalize();
}

std::string g_stTraceBuffer[512];
int	g_nCurTraceN = 0;

void Traceback()
{
	std::string str;

	for (int i = 0; i < g_nCurTraceN; ++i)
	{
		str.append(g_stTraceBuffer[i]);
		str.append("\n");
	}
	
	PyObject * exc;
	PyObject * v;
	PyObject * tb;
	PyErr_Fetch(&exc, &v, &tb);
#ifdef PYTHON_3
	PyObject* pyStr = PyObject_Str(v);
	if (pyStr)
	{
		const char* errStr = PyUnicode_AsUTF8(pyStr);
		if (errStr)
		{
			str.append("Error: ");
			str.append(errStr);
			Tracef("%s\n", errStr);
		}
		Py_DECREF(pyStr);
	}
#else
	const char * errStr;
	if (PyString_Check(v))
	{
		errStr = PyString_AS_STRING(v);
		str.append("Error: ");
		str.append(errStr);

		Tracef("%s\n", errStr);
	}
#endif
	Py_DECREF(exc);
	Py_DECREF(v);
	Py_DECREF(tb);
	LogBoxf("Traceback:\n\n%s\n", str.c_str());
}

int TraceFunc(PyObject * obj, PyFrameObject * f, int what, PyObject *arg)
{
	const char * funcname;
	char szTraceBuffer[128];
#ifdef PYTHON_3
	int lineno;
	PyCodeObject* code = nullptr;
#endif

	switch (what)
	{
		case PyTrace_CALL:
			if (g_nCurTraceN >= 512)
				return 0;

#ifdef PYTHON_3
			code = (PyCodeObject*)PyFrame_GetCode(f);
			lineno = PyFrame_GetLineNumber(f);

			funcname = PyUnicode_AsUTF8(code->co_name);

			snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Call: File \"%s\", line %d, in %s",
				PyUnicode_AsUTF8(code->co_filename),
				lineno,
				funcname);
			Py_DECREF(code);
#else
			if (Py_OptimizeFlag)
				f->f_lineno = PyCode_Addr2Line(f->f_code, f->f_lasti);

			funcname = PyString_AsString(f->f_code->co_name);

			_snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Call: File \"%s\", line %d, in %s", 
					  PyString_AsString(f->f_code->co_filename), 
					  f->f_lineno,
					  funcname);
#endif

			g_stTraceBuffer[g_nCurTraceN++]=szTraceBuffer;			
			break;

		case PyTrace_RETURN:
			if (g_nCurTraceN > 0)
				--g_nCurTraceN;
			break;

		case PyTrace_EXCEPTION:
			if (g_nCurTraceN >= 512)
				return 0;
			
			PyObject * exc_type, * exc_value, * exc_traceback;

			PyTuple_GetObject(arg, 0, &exc_type);
			PyTuple_GetObject(arg, 1, &exc_value);
			PyTuple_GetObject(arg, 2, &exc_traceback);

			Py_ssize_t len;
#ifdef PYTHON_3
			const char* exc_str = PyUnicode_AsUTF8AndSize(exc_type, &len);

			code = (PyCodeObject*)PyFrame_GetCode(f);
			lineno = PyFrame_GetLineNumber(f);

			snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Exception: File \"%s\", line %d, in %s",
				PyUnicode_AsUTF8(code->co_filename),
				lineno,
				PyUnicode_AsUTF8(code->co_name));
			Py_DECREF(code);
#else
			const char * exc_str;
			PyObject_AsCharBuffer(exc_type, &exc_str, &len);
			
			_snprintf(szTraceBuffer, sizeof(szTraceBuffer), "Exception: File \"%s\", line %d, in %s", 
					  PyString_AS_STRING(f->f_code->co_filename), 
					  f->f_lineno,
					  PyString_AS_STRING(f->f_code->co_name));
#endif

			g_stTraceBuffer[g_nCurTraceN++]=szTraceBuffer;
			
			break;
	}
	return 0;
}

void CPythonLauncher::SetTraceFunc(int (*pFunc)(PyObject * obj, PyFrameObject * f, int what, PyObject *arg))
{
	PyEval_SetTrace(pFunc, NULL);
}

bool CPythonLauncher::Create(const char* c_szProgramName)
{
	NANOBEGIN
#ifdef PYTHON_3
	wchar_t wszProgramName[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, c_szProgramName, -1, wszProgramName, MAX_PATH);

	PyStatus status;
	PyConfig config;
	PyConfig_InitPythonConfig(&config);
	status = PyConfig_SetString(&config, &config.program_name, wszProgramName);
	if (PyStatus_Exception(status)) {
		PyConfig_Clear(&config);
		Py_ExitStatusException(status);
		return false;
	}
	status = Py_InitializeFromConfig(&config);
	if (PyStatus_Exception(status)) {
		PyConfig_Clear(&config);
		Py_ExitStatusException(status);
		return false;
	}
	PyConfig_Clear(&config);
#else
	Py_SetProgramName((char*)c_szProgramName);
#endif
#ifndef PYTHON_3
#ifdef _DEBUG
	PyEval_SetTrace(TraceFunc, NULL);
#endif
#endif
	m_poModule = PyImport_AddModule((char *) "__main__");

	if (!m_poModule)
		return false;
	
	m_poDic = PyModule_GetDict(m_poModule);

#ifdef PYTHON_3
	PyObject* builtins = PyImport_ImportModule("builtins");
#else
	PyObject * builtins = PyImport_ImportModule("__builtin__");
#endif
	PyModule_AddIntConstant(builtins, "TRUE", 1);
	PyModule_AddIntConstant(builtins, "FALSE", 0);
	PyDict_SetItemString(m_poDic, "__builtins__", builtins);
	Py_DECREF(builtins);

	if (!RunLine("import __main__"))
		return false;
	
	if (!RunLine("import sys"))
		return false;

	NANOEND
	return true;
}

bool CPythonLauncher::RunCompiledFile(const char* c_szFileName)
{
	NANOBEGIN
	// UTF-8 → UTF-16 conversion for Unicode path support
	std::wstring wFileName = Utf8ToWide(c_szFileName);
	FILE * fp = _wfopen(wFileName.c_str(), L"rb");

	if (!fp)
		return false;

#ifdef PYTHON_3
	PyObject *co;
#else
	PyCodeObject *co;
#endif
	PyObject *v;
	long magic;
	long PyImport_GetMagicNumber(void);

	magic = _PyMarshal_ReadLongFromFile(fp);

	if (magic != PyImport_GetMagicNumber())
	{
		PyErr_SetString(PyExc_RuntimeError, "Bad magic number in .pyc file");
		fclose(fp);
		return false;
	}

	_PyMarshal_ReadLongFromFile(fp);
	v = _PyMarshal_ReadLastObjectFromFile(fp);

	fclose(fp);

	if (!v || !PyCode_Check(v))
	{
		Py_XDECREF(v);
		PyErr_SetString(PyExc_RuntimeError, "Bad code object in .pyc file");
		return false;
	}

#ifdef PYTHON_3
	co = (PyObject *) v;
#else
	co = (PyCodeObject *) v;
#endif
	v = PyEval_EvalCode(co, m_poDic, m_poDic);
/*	if (v && flags)
		flags->cf_flags |= (co->co_flags & PyCF_MASK);*/
	Py_DECREF(co);
	if (!v)
	{
		Traceback();
		return false;
	}

	Py_DECREF(v);
#ifndef PYTHON_3
	if (Py_FlushLine()) 
		PyErr_Clear();
#endif

	NANOEND
	return true;
}


bool CPythonLauncher::RunMemoryTextFile(const char* c_szFileName, UINT uFileSize, const VOID* c_pvFileData)
{
	NANOBEGIN
	const CHAR* c_pcFileData=(const CHAR*)c_pvFileData;

	std::string stConvFileData;
	stConvFileData.reserve(uFileSize);
	stConvFileData+="exec(compile('''";

	// ConvertPythonTextFormat
	{
		for (UINT i=0; i<uFileSize; ++i)
		{
			if (c_pcFileData[i]!=13)
				stConvFileData+=c_pcFileData[i];
		}
	}

	stConvFileData+= "''', ";
	stConvFileData+= "'";
	stConvFileData+= c_szFileName;
	stConvFileData+= "', ";
	stConvFileData+= "'exec'))";

	const CHAR* c_pcConvFileData=stConvFileData.c_str();
	NANOEND
	return RunLine(c_pcConvFileData);
}

bool CPythonLauncher::RunFile(const char* c_szFileName)
{
	TPackFile file;
	CPackManager::Instance().GetFile(c_szFileName, file);
		
	if (file.empty())
		return false;
		
	return RunMemoryTextFile(c_szFileName, file.size(), file.data());
}

bool CPythonLauncher::RunLine(const char* c_szSrc)
{
	PyObject * v = PyRun_String((char *) c_szSrc, Py_file_input, m_poDic, m_poDic);

	if (!v)
	{
		Traceback();
		return false;
	}

	Py_DECREF(v);
	return true;
}

const char* CPythonLauncher::GetError()
{
	PyObject* exc;
	PyObject* v;
	PyObject* tb;

	PyErr_Fetch(&exc, &v, &tb);        

#ifdef PYTHON_3
	if (PyUnicode_Check(v))
		return PyUnicode_AsUTF8(v);
#else
	if (PyString_Check(v))
		return PyString_AS_STRING(v);
#endif
	
	return "";
}
