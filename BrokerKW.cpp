
// BrokerKW.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "BrokerKW.h"
#include "BrokerKWDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

dk::C_CONFIG* g_pConfig = nullptr;
dk::C_LOG* g_pLog = nullptr;

// CBrokerKWApp

BEGIN_MESSAGE_MAP(CBrokerKWApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// CBrokerKWApp 생성

CBrokerKWApp::CBrokerKWApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
#if defined(_USE_EXCEPTION_MAIN_)
	try
	{
#endif
		if (!g_pConfig) { g_pConfig = new dk::C_CONFIG(); }
		if (!g_pLog) { g_pLog = new dk::C_LOG(); }
		if (g_pLog)
		{
			g_pLog->Init(__TEXT("log-BrokerKW"));
			g_pLog->Write(__TEXT("로그 기록을 시작합니다(BrokerKW)"));
		}
		this->khOpenAPI.init();			// 키움 필수
#if defined(_USE_EXCEPTION_MAIN_)
	}
	catch (...)
	{
		if (g_pLog) { g_pLog->Write(L"CBrokerKWApp 생성 중 알 수 없는 예외 발생"); }
		else { ::OutputDebugStringW(L"CBrokerKWApp 생성 중 알 수 없는 예외 발생"); }
	}
#endif
}


// 유일한 CBrokerKWApp 개체입니다.

CBrokerKWApp theApp;


// CBrokerKWApp 초기화

BOOL CBrokerKWApp::InitInstance()
{
	// 애플리케이션 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// MFC 컨트롤의 테마를 사용하기 위해 "Windows 원형" 비주얼 관리자 활성화
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));

	C_DLG_BROKER_KW dlgMain;
	m_pMainWnd = &dlgMain;
	const INT_PTR nResponse = dlgMain.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}
	// 생성한 것들을 삭제합니다. - 키움 필수
#if defined(_USE_EXCEPTION_MAIN_)
	try
	{
#endif
		DBGPRINT(L"프로그램을 종료합니다");
		dk::TerminateProcess(L"opstarter.exe");
		// 설정과 로그를 삭제합니다.
		if (g_pConfig != nullptr)
		{
			delete g_pConfig;
			g_pConfig = nullptr;
		}
		if (g_pLog != nullptr)
		{
			g_pLog->Write(L"CBrokerKWApp::InitInstance() - 로그 기록을 종료합니다(BrokerKW)");
			delete g_pLog;
			g_pLog = nullptr;
		}
#if defined(_USE_EXCEPTION_MAIN_)
	}
	catch (...)
	{
		if (g_pLog) { g_pLog->Write(L"CBrokerKWApp::InitInstance() - 알 수 없는 예외 발생"); }
		else { ::OutputDebugStringW(L"CBrokerKWApp::InitInstance() - 알 수 없는 예외 발생"); }
	}
#endif
	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}
#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고 응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}
