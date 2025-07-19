
// BrokerKWDlg.h: 헤더 파일
//

#pragma once


// C_DLG_BROKER_KW 대화 상자
class C_DLG_BROKER_KW
	: public CDialogEx
{
private:
	bool bCloseToTray{ false }, bShowWindow{ false };

	void Destroy(bool _bForce = false);

	void save_rect();
	void move_rect();

	void create_tray_icon();
	void delete_tray_icon();

	void show_window(bool _bShow = true);

	afx_msg LRESULT OnTrayMenu(WPARAM _wParam, LPARAM _lParam);

// 구현입니다.
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
	
// 생성입니다.
public:
	C_DLG_BROKER_KW(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTrayClose();
	afx_msg LRESULT OnTrayRestart(WPARAM _wParam, LPARAM _lParam);


	CButton m_chk_version;
};
