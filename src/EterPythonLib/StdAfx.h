#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "EterLib/StdAfx.h"
#include "ScriptLib/StdAfx.h"

#include "PythonGraphic.h"
#include "PythonWindowManager.h"

#ifdef PYTHON_3
	PyMODINIT_FUNC PyInit_grp(void);
	PyMODINIT_FUNC PyInit_grpImage(void);
	PyMODINIT_FUNC PyInit_grpText(void);
	PyMODINIT_FUNC PyInit_grpThing(void);
	PyMODINIT_FUNC PyInit_wndMgr(void);
#else
	void initgrp();
	void initgrpImage();
	void initgrpText();
	void initgrpThing();
	void initwndMgr();
#endif