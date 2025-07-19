
// BrokerKWDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "BrokerKW.h"
#include "BrokerKWDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C_DLG_BROKER_KW 대화 상자


UINT _WM_SHELL_RESTART_ = 0;

C_DLG_BROKER_KW::C_DLG_BROKER_KW(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MAIN, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C_DLG_BROKER_KW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL, theApp.khOpenAPI);	// 키움 필수
	DDX_Control(pDX, IDC_CHK_VERSION, m_chk_version);
}

BEGIN_MESSAGE_MAP(C_DLG_BROKER_KW, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_TRAYICON, &C_DLG_BROKER_KW::OnTrayMenu)
	ON_COMMAND(ID_TRAY_CLOSE, &C_DLG_BROKER_KW::OnTrayClose)
	ON_REGISTERED_MESSAGE(_WM_SHELL_RESTART_, &C_DLG_BROKER_KW::OnTrayRestart)

	ON_WM_WINDOWPOSCHANGING()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

void C_DLG_BROKER_KW::save_rect()
{
	CRect rc;
	this->GetWindowRect(&rc);
	if (!this->IsIconic())
	{
		g_pConfig->set_ini(__TEXT("location"), __TEXT("x"), (int)rc.left);
		g_pConfig->set_ini(__TEXT("location"), __TEXT("y"), (int)rc.top);
		g_pConfig->set_ini(__TEXT("location"), __TEXT("w"), (int)rc.Width());
		g_pConfig->set_ini(__TEXT("location"), __TEXT("h"), (int)rc.Height());
	}
}

void C_DLG_BROKER_KW::move_rect()
{
	CRect rc;
	this->GetWindowRect(&rc);

	this->MoveWindow(
		g_pConfig->get_ini(__TEXT("location"), __TEXT("x"), (GetSystemMetrics(SM_CXSCREEN) - rc.Width()) / 2)
		, g_pConfig->get_ini(__TEXT("location"), __TEXT("y"), (GetSystemMetrics(SM_CYSCREEN) - rc.Height()) / 2)
		, g_pConfig->get_ini(__TEXT("location"), __TEXT("w"), rc.Width())
		, g_pConfig->get_ini(__TEXT("location"), __TEXT("h"), rc.Height())
	);
	//GetWindowRect(&rc);
	//DBGPRINT(_T("OnInitDialog() : %d, %d, %d, %d"), rc.left, rc.top, rc.Width(), rc.Height());
}

void C_DLG_BROKER_KW::create_tray_icon()
{
	// 트레이 아이콘 제거
	::NOTIFYICONDATA nid = { sizeof(::NOTIFYICONDATA), this->m_hWnd, 0 };
	Shell_NotifyIcon(NIM_DELETE, &nid);

	// 윈도우 타이틀을 툴팁으로 사용한다.
	CString str;
	GetWindowText(str);
	::wcscpy_s(nid.szTip, str.GetString());

	// 트레이 아이콘 생성
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TRAYICON;
	Shell_NotifyIcon(NIM_ADD, &nid);
}

void C_DLG_BROKER_KW::delete_tray_icon()
{
	NOTIFYICONDATA nid = { 0 };
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = m_hWnd;
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void C_DLG_BROKER_KW::show_window(bool _bShow)
{
	if (!_bShow)
	{
		this->ShowWindow(SW_SHOWMINIMIZED);
		this->PostMessage(WM_SHOWWINDOW, FALSE, SW_OTHERUNZOOM);	// SW_OTHERUNZOOM 의 경우는 윈도우가 최소화 되어 있을 때 윈도우를 활성화 시키는 것이다.
	}
	else
	{
		this->ShowWindow(SW_SHOWNORMAL);
		this->PostMessage(WM_SHOWWINDOW, TRUE, SW_OTHERUNZOOM);	// SW_OTHERUNZOOM 의 경우는 윈도우가 최소화 되어 있을 때 윈도우를 활성화 시키는 것이다.
	}
	bShowWindow = _bShow;
}


LRESULT C_DLG_BROKER_KW::OnTrayMenu(WPARAM _wParam, LPARAM _lParam)
{
	_wParam;
	if (WM_RBUTTONUP == LOWORD(_lParam))
	{
		this->SetForegroundWindow();

		CPoint ptMouse;
		::GetCursorPos(&ptMouse);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_TRAY);

		CMenu* pMenu = menu.GetSubMenu(0);
		pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, ptMouse.x, ptMouse.y, AfxGetMainWnd());
	}
	else if (WM_LBUTTONDBLCLK == LOWORD(_lParam))	// 더블클릭
	{
		if (!bShowWindow)
		{
			// 윈도우를 화면에 표시한다.
			this->show_window(true);
			this->move_rect();
		}
	}
	return(0);
}

void C_DLG_BROKER_KW::OnTrayClose()
{
	//DBGPRINT(L"C_DLG_BROKER_KW::OnTrayClose()");
	this->Destroy(true);
}

LRESULT C_DLG_BROKER_KW::OnTrayRestart(WPARAM _wParam, LPARAM _lParam)
{
	_wParam;
	_lParam;
	//DBGPRINT(L"CMBetBotDlg::OnTrayRestart()");
	this->create_tray_icon();
	return(0);
}

// C_DLG_BROKER_KW 메시지 처리기

BOOL C_DLG_BROKER_KW::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	this->SetIcon(this->m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	this->SetIcon(this->m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
#if defined(_USE_EXCEPTION_MAIN_)
	try
	{
#endif
		_WM_SHELL_RESTART_ = ::RegisterWindowMessage(__TEXT("TaskbarCreated"));
		if (g_pConfig)
		{
			this->bCloseToTray = g_pConfig->get_ini(L"base", L"close_to_tray", true);
		}
		this->create_tray_icon();

		if (!theApp.khOpenAPI.CommConnect())				// 키움 필수
		{	// 로그인을 한다.
			DBGPRINT(L"키움 로그인 팝업 호출 성공");
		}
		else
		{
			DBGPRINT(L"실패: 키움 로그인 팝업");
			AfxMessageBox(__TEXT("로그인창 호출 실패"));
		}

		this->show_window(false);
#if defined(_USE_EXCEPTION_MAIN_)
	}
	catch (...)
	{
		DBGPRINT(L"예외발생: %s(%d)", __FILEW__, __LINE__);
		AfxMessageBox(__TEXT("예외 발생"));
	}
#endif
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void C_DLG_BROKER_KW::OnPaint()
{
	if (this->IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		this->GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR C_DLG_BROKER_KW::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void C_DLG_BROKER_KW::Destroy(bool _bForce)							// 키움 필수
{
	static bool bDestroy = false;
#if defined(_USE_EXCEPTION_MAIN_)
	try
	{
#endif
		if (this->bShowWindow)
		{
			DBGPRINT(L"%s - Save Rect", __FUNCTIONW__);
			save_rect();
		}
		if (!bCloseToTray || !bShowWindow || _bForce)
		{

			if (!bDestroy) { bDestroy = true; }
			else { return; }

			//for (auto& it : umapTimerIDs)
			//{
			//	//if (::KillTimer(m_hWnd, it.first)) { DBGPRINT(L"[타이머] 해제 ID: %d, Interval: %d", it.first, it.second); }
			//	// MFC 함수를 사용해서 타이머를 해제한다.
			//	if (this->KillTimer(it.first)) { DBGPRINT(L"[타이머] 해제 ID: %d, Interval: %d", it.first, it.second); }
			//}
			//umapTimerIDs.clear();

			//DBGPRINT(L"%s - Destroy(first)", __FUNCTIONW__);

			delete_tray_icon();

			//DBGPRINT(L"%s - PostThreadMessage(WM_QUIT)", __FUNCTIONW__);
			AfxGetApp()->PostThreadMessageW(WM_QUIT, 0, 0); // 메인 스레드에 WM_QUIT 메시지를 전송하여 프로그램을 종료합니다.
			//DBGPRINT(L"%s - Destroy(end)", __FUNCTIONW__);
		}
		else
		{
			DBGPRINT(L"%s - 트레이로 이동", __FUNCTIONW__);
			// 트레이로 이동
			this->show_window(false);
		}
#if defined(_USE_EXCEPTION_MAIN_)
	}
	catch (...)
	{
		DBGPRINT(L"예외발생: %s(%d)", __FILEW__, __LINE__);
		AfxMessageBox(__TEXT("예외 발생"));
	}
#endif
}

void C_DLG_BROKER_KW::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
	__super::OnWindowPosChanging(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
		//if (!this->bUseDialog)
	//{
	//	//DBGPRINT(L"%s - SWP_SHOWWINDOW 제거", __FUNCTIONW__);
	//	lpwndpos->flags &= ~SWP_SHOWWINDOW;			// 창이 보이지 않도록 제거
	//}
	//else
	{
		//DBGPRINT(L"%s - SWP_SHOWWINDOW 설정", __FUNCTIONW__);
		lpwndpos->flags |= SWP_SHOWWINDOW;			// 창이 보이도록 설정
	}
	CDialog::OnWindowPosChanging(lpwndpos);
}


void C_DLG_BROKER_KW::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (SC_CLOSE == (nID & 0xFFF0))	// 닫기 버튼을 눌렀을 때
	{
		//DBGPRINT(L"%s - SC_CLOSE", __FUNCTIONW__);
		this->Destroy();
	}
	__super::OnSysCommand(nID, lParam);
}

void C_DLG_BROKER_KW::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	// ESC 키를 눌러도 다이얼로그가 종료되지 않도록 한다.
	//__super::OnCancel();
	//DBGPRINT(L"여긴 호출 되는가?");
}
