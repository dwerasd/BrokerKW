
// BrokerKW.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

#if !defined(WM_TRAYICON)
#define WM_TRAYICON     (WM_USER + 100)
#endif

#include "CKHOpenAPI.h"			// 키움 필수

#define _USE_EXCEPTION_MAIN_

// CBrokerKWApp:
// 이 클래스의 구현에 대해서는 BrokerKW.cpp을(를) 참조하세요.
//

class CBrokerKWApp
	: public CWinApp
{
public:
	CBrokerKWApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	C_KH_OPEN_API khOpenAPI;			// 키움 필수

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CBrokerKWApp theApp;
