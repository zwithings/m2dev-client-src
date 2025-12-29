#pragma once

#pragma warning(disable:4702)
#pragma warning(disable:4100)
#pragma warning(disable:4201)
#pragma warning(disable:4511)
#pragma warning(disable:4663)
#pragma warning(disable:4018)
#pragma warning(disable:4245)
#pragma warning(disable:4995)

#include "EterLib/StdAfx.h"
#include "EterPythonLib/StdAfx.h"
#include "GameLib/StdAfx.h"
#include "ScriptLib/StdAfx.h"
#include "AudioLib/StdAfx.h"
#include "EffectLib/StdAfx.h"
#include "PRTerrainLib/StdAfx.h"
#include "SpeedTreeLib/StdAfx.h"

#ifndef __D3DRM_H__
#define __D3DRM_H__
#endif

#include <dshow.h>
#include "Locale.h"
#include "GameType.h"

#define APP_NAME "Metin 2"

enum
{
	POINT_MAX_NUM = 255,
	CHARACTER_NAME_MAX_LEN = 64,
	PLAYER_NAME_MAX_LEN = 12,
};

#ifdef PYTHON_3
	// Python 3.12 module initialization declarations
	PyMODINIT_FUNC PyInit_udp(void);
	PyMODINIT_FUNC PyInit_app(void);
	PyMODINIT_FUNC PyInit_ime(void);
	PyMODINIT_FUNC PyInit_systemSetting(void);
	PyMODINIT_FUNC PyInit_chr(void);
	PyMODINIT_FUNC PyInit_chrmgr(void);
	PyMODINIT_FUNC PyInit_chat(void);
	PyMODINIT_FUNC PyInit_textTail(void);
	PyMODINIT_FUNC PyInit_item(void);
	PyMODINIT_FUNC PyInit_nonplayer(void);
	PyMODINIT_FUNC PyInit_net(void);
	PyMODINIT_FUNC PyInit_player(void);
	PyMODINIT_FUNC PyInit_ServerStateChecker(void);
	PyMODINIT_FUNC PyInit_exchange(void);
	PyMODINIT_FUNC PyInit_miniMap(void);
	PyMODINIT_FUNC PyInit_profiler(void);
	PyMODINIT_FUNC PyInit_event(void);
	PyMODINIT_FUNC PyInit_effect(void);
	PyMODINIT_FUNC PyInit_snd(void);
	PyMODINIT_FUNC PyInit_eventMgr(void);
	PyMODINIT_FUNC PyInit_background(void);
	PyMODINIT_FUNC PyInit_wndMgr(void);
	PyMODINIT_FUNC PyInit_shop(void);
	PyMODINIT_FUNC PyInit_pack(void);
	PyMODINIT_FUNC PyInit_skill(void);
	PyMODINIT_FUNC PyInit_fly(void);
	PyMODINIT_FUNC PyInit_quest(void);
	PyMODINIT_FUNC PyInit_safebox(void);
	PyMODINIT_FUNC PyInit_guild(void);
	PyMODINIT_FUNC PyInit_messenger(void);
#else
	// Python 2.7 module initialization declarations
	void initudp();
	void initapp();
	void initime();
	void initsystem();
	void initchr();
	void initchrmgr();
	void initChat();
	void initTextTail();
	void initime();
	void initItem();
	void initNonPlayer();
	void initnet();
	void initPlayer();
	void initServerStateChecker();
	void initTrade();
	void initMiniMap();
	void initProfiler();
	void initEvent();
	void initeffect();
	void initsnd();
	void initeventmgr();
	void initBackground();
	void initwndMgr();
	void initshop();
	void initpack();
	void initskill();
	void initfly();
	void initquest();
	void initsafebox();
	void initguild();
	void initMessenger();
#endif
