
// Test_SCColorThemeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_SCColorTheme.h"
#include "Test_SCColorThemeDlg.h"
#include "afxdialogex.h"

#include "Common/RandomText.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//동적 생성하는 폰트 시연 콤보 ID (resource.h 의 IDC_ 최대값 1012 위, command 범위 32771 아래).
#define IDC_COMBO_FONT_FACE			1101
#define IDC_COMBO_FONT_SIZE			1102

//폰트·크기를 바꿔가며 quality 자동판정을 확인하는 콤보 항목 — 콤보 인덱스로 그대로 참조.
//굴림/궁서/돋움/Tahoma/Verdana = 작은 크기에 비트맵 내장(또렷), Segoe UI/맑은 고딕 = 순수 벡터(전 크기 AA).
static const TCHAR* g_font_faces[] = { _T("Segoe UI"), _T("맑은 고딕"), _T("굴림"), _T("궁서"), _T("돋움"), _T("Tahoma"), _T("Verdana") };
static const int g_font_sizes[] = { 9, 10, 11, 12, 13, 14, 16, 18, 20, 24, 28 };


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestSCColorThemeDlg 대화 상자



CTestSCColorThemeDlg::CTestSCColorThemeDlg(CWnd* pParent /*=nullptr*/)
	: CSCThemeDlg(IDD_TEST_SCCOLORTHEME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSCColorThemeDlg::DoDataExchange(CDataExchange* pDX)
{
	CSCThemeDlg::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_tree);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_COMBO_THEME, m_combo_theme);
	DDX_Control(pDX, IDC_STATIC_COLOR_THEME, m_static_color_theme);
	DDX_Control(pDX, IDC_EDIT, m_edit);
	DDX_Control(pDX, IDC_STATIC_EDIT, m_static_edit);
	//표준 PUSHBUTTON 인 IDOK / IDCANCEL 을 CGdiButton 으로 subclass — PreSubclassWindow 에서 BS_OWNERDRAW 자동 적용.
	DDX_Control(pDX, IDOK, m_btn_ok);
	DDX_Control(pDX, IDCANCEL, m_btn_cancel);
	DDX_Control(pDX, IDC_STATIC_LISTBOX, m_static_listbox);
	DDX_Control(pDX, IDC_LISTBOX, m_listbox);
	DDX_Control(pDX, IDC_STATIC_SCSTATICEDIT, m_static_staticedit);
	DDX_Control(pDX, IDC_STATIC_CSCSTATIC_EDIT, m_static_scstaticedit);
	DDX_Control(pDX, IDC_STATIC_PATHCTRL, m_static_pathctrl);
	DDX_Control(pDX, IDC_PATH, m_path);
}

BEGIN_MESSAGE_MAP(CTestSCColorThemeDlg, CSCThemeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGED()
	ON_CBN_SELCHANGE(IDC_COMBO_THEME, &CTestSCColorThemeDlg::OnCbnSelchangeComboTheme)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT_FACE, &CTestSCColorThemeDlg::OnCbnSelchangeComboFontFace)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT_SIZE, &CTestSCColorThemeDlg::OnCbnSelchangeComboFontSize)
	ON_REGISTERED_MESSAGE(Message_CSCSystemButtons, &CTestSCColorThemeDlg::on_message_CSCSystemButtons)
	ON_REGISTERED_MESSAGE(Message_CPathCtrl, &CTestSCColorThemeDlg::on_message_CPathCtrl)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_ADD, &CTestSCColorThemeDlg::OnBnClickedButtonListboxAdd)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_DELETE, &CTestSCColorThemeDlg::OnBnClickedButtonListboxDelete)
END_MESSAGE_MAP()


// CTestSCColorThemeDlg 메시지 처리기

BOOL CTestSCColorThemeDlg::OnInitDialog()
{
	CSCThemeDlg::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetWindowText(_T("Test_SCColorTheme"));

	set_color_theme(CSCColorTheme::color_theme_gray);
	//m_theme.set_theme_level(0.4f);

	set_system_buttons(this, SC_PIN, SC_MINIMIZE, SC_MAXIMIZE, SC_CLOSE);

	set_titlebar_font_size(9);
	set_titlebar_icon(IDR_MAINFRAME, 16, 16);

	m_resize.Create(this);
	m_resize.Add(IDOK, 100, 100, 0, 0);
	m_resize.Add(IDCANCEL, 100, 100, 0, 0);
	m_resize.Add(IDC_STATIC_PATHCTRL, 0, 100, 0, 0);
	m_resize.Add(IDC_PATH, 0, 100, 100, 0);
	m_resize.Add(IDC_TREE, 0, 0, 0, 100);
	m_resize.Add(IDC_LIST, 0, 0, 100, 100);

	m_tree.set_as_shell_treectrl(&m_shell_imglist);
	m_list.set_as_shell_listctrl(&m_shell_imglist);
	m_path.set_shell_imagelist(&m_shell_imglist, true);
	//m_path.set_path(_T("D:\\"));

	m_combo_theme.set_line_height(12);
	std::deque<CString> dq_color_theme;
	CSCColorTheme::get_color_theme_list(dq_color_theme);
	for (auto theme_name : dq_color_theme)
		m_combo_theme.AddString(theme_name);

	int color_theme = theApp.GetProfileInt(_T("setting"), _T("color theme"), CSCColorTheme::color_theme_default);
	m_combo_theme.SetCurSel(color_theme);

	//부모(CSCThemeDlg) 의 m_theme 객체를 인덱스 기반으로 먼저 채운 다음, 객체 자체를 자식들에 전파.
	//인덱스만 넘기면 자식이 default 만 재계산하여 부모가 커스터마이즈한 색 (titlebar 등) 이 누락된다.
	set_color_theme(color_theme);

	m_static_color_theme.set_color_theme(m_theme);
	m_static_edit.set_color_theme(m_theme);
	m_static_staticedit.set_color_theme(m_theme);
	m_static_listbox.set_color_theme(m_theme);
	m_static_pathctrl.set_color_theme(m_theme);

	m_combo_theme.set_color_theme(m_theme);
	m_edit.set_color_theme(m_theme);
	m_edit.set_line_align(DT_VCENTER);
	m_static_scstaticedit.set_color_theme(m_theme);
	//m_listbox.set_color_theme(m_theme);
	//m_listbox.set_font_size(10);
	//m_listbox.set_show_selection_always(false);
	m_tree.set_color_theme(m_theme);
	m_list.set_color_theme(m_theme);
	m_btn_ok.set_color_theme(m_theme);
	m_btn_cancel.set_color_theme(m_theme);
	m_path.set_color_theme(m_theme);

	//--- CSCListBox 폰트 quality 자동판정 시연 콤보 (동적 생성) — listbox 아래 [폰트][크기] ---
	//폰트가 그 크기에 비트맵을 가지면 DEFAULT_QUALITY(또렷), 없으면 ANTIALIASED_QUALITY(부드럽게)가 자동 적용.
	//폰트(굴림=비트맵 / Segoe UI=벡터)와 크기를 바꿔가며 전환 경계를 직접 확인.
	CRect rc_list;
	m_listbox.GetWindowRect(rc_list);
	ScreenToClient(rc_list);

	const int gap = 6;
	const int combo_drop_h = 200;	//Create 시 window height = dropdown 펼침 상한
	int half = (rc_list.Width() - gap) / 2;
	int combo_top = rc_list.bottom + gap;

	CRect rc_face(rc_list.left, combo_top, rc_list.left + half, combo_top + combo_drop_h);
	CRect rc_size(rc_face.right + gap, combo_top, rc_list.right, combo_top + combo_drop_h);

	const DWORD combo_style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS;
	m_combo_font_face.Create(combo_style, rc_face, this, IDC_COMBO_FONT_FACE);
	m_combo_font_size.Create(combo_style, rc_size, this, IDC_COMBO_FONT_SIZE);

	m_combo_font_face.set_line_height(12);
	m_combo_font_size.set_line_height(12);

	for (const TCHAR* face : g_font_faces)
		m_combo_font_face.AddString(face);
	for (int pt : g_font_sizes)
	{
		CString s;
		s.Format(_T("크기: %dpt"), pt);
		m_combo_font_size.AddString(s);
	}

	m_combo_font_face.SetCurSel(0);	//Segoe UI (다이얼로그 상속 폰트와 동일)
	m_combo_font_size.SetCurSel(1);	//10pt (listbox 초기 크기와 동일)

	m_combo_font_face.set_color_theme(m_theme);
	m_combo_font_size.set_color_theme(m_theme);

	m_msgbox.create(this, _T("Test_SCColorTheme"), 0, false);
	m_msgbox.set_color_theme(m_theme);
	m_msgbox.set_message(_T("<cr=royalblue>테스트 <b><cr=red>메시지 박스</cr></b> 길이에 따라 <b>자동 조정</b>되며\n멀티라인 가능\n<cr=blue>기본 <b><cb=lightpink>HTML 태그</b></cb> 지원"),
		MB_ICONINFORMATION);

	m_edit.set_text(_T("This is a SCEdit control 플레이그라운드."));

	for (int i = 0; i < 15; i++)
	{
		m_listbox.insert(i, i2S(i) + _T(":") + RandomText::GetSlogan());
	}
	m_listbox.insert(-1, _T("한글 테스트 텍스트"));

	RestoreWindowPosition(&theApp, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestSCColorThemeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CSCThemeDlg::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestSCColorThemeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSCThemeDlg::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestSCColorThemeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestSCColorThemeDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CSCThemeDlg::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}

void CTestSCColorThemeDlg::OnCbnSelchangeComboTheme()
{
	int index = m_combo_theme.GetCurSel();
	if (index < 0 || index >= m_combo_theme.GetCount())
		return;

	theApp.WriteProfileInt(_T("setting"), _T("color theme"), index);

	//부모(CSCThemeDlg) 의 m_theme 객체를 인덱스 기반으로 먼저 채운 다음, 객체 자체를 자식들에 전파.
	set_color_theme(index, true);


	m_sys_buttons.set_color_theme(m_theme, true);
	m_static_color_theme.set_color_theme(m_theme, true);
	m_combo_theme.set_color_theme(m_theme, true);

	m_static_edit.set_color_theme(m_theme, true);
	m_edit.set_color_theme(m_theme, true);

	m_static_staticedit.set_color_theme(m_theme, true);
	m_static_scstaticedit.set_color_theme(m_theme, true);

	m_static_listbox.set_color_theme(m_theme, true);
	m_listbox.set_color_theme(m_theme, true);
	m_combo_font_face.set_color_theme(m_theme, true);
	m_combo_font_size.set_color_theme(m_theme, true);

	m_tree.set_color_theme(m_theme, true);
	m_list.set_color_theme(m_theme, true);
	m_btn_ok.set_color_theme(m_theme, true);
	m_btn_cancel.set_color_theme(m_theme, true);

	m_static_pathctrl.set_color_theme(m_theme, true);
	m_path.set_color_theme(m_theme, true);

	m_msgbox.set_color_theme(m_theme, true);
}

void CTestSCColorThemeDlg::OnCbnSelchangeComboFontFace()
{
	int i = m_combo_font_face.GetCurSel();
	if (i < 0)
		i = 0;

	//set_font_name 이 ReconstructFont 를 호출 → 새 폰트의 비트맵 보유 여부로 AA 모드를 자동 재판정.
	m_listbox.set_font_name(g_font_faces[i]);
}

void CTestSCColorThemeDlg::OnCbnSelchangeComboFontSize()
{
	int i = m_combo_font_size.GetCurSel();
	if (i < 0)
		i = 0;

	//set_font_size 가 ReconstructFont 를 호출 → 새 크기에서 비트맵 보유 여부로 AA 모드를 자동 재판정.
	m_listbox.set_font_size(g_font_sizes[i]);
}

LRESULT CTestSCColorThemeDlg::on_message_CSCSystemButtons(WPARAM wParam, LPARAM lParam)
{
	CSCSystemButtonsMessage* msg = (CSCSystemButtonsMessage*)wParam;

	switch (msg->cmd)
	{
		case SC_PIN:
			SetWindowPos(is_top_most(m_hWnd) ? &wndNoTopMost : &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			theApp.WriteProfileInt(_T("setting"), _T("always on top"), is_top_most(m_hWnd));
			break;
		case SC_MINIMIZE:
			ShowWindow(SW_MINIMIZE);
			break;
		case SC_RESTORE:
		case SC_MAXIMIZE:
			ShowWindow(IsZoomed() ? SW_RESTORE : SW_MAXIMIZE);
			break;
		case SC_CLOSE:
			EndDialog(0);
			break;
	}

	return 0;
}

LRESULT CTestSCColorThemeDlg::on_message_CPathCtrl(WPARAM wParam, LPARAM lParam)
{
	CPathCtrlMessage* pMsg = (CPathCtrlMessage*)wParam;

	//m_path2도 동일한 처리가 필요하지만 이 예제에서는 m_path만 처리한다.
	if (pMsg->pThis == &m_path)
	{
		if (pMsg->message == CPathCtrl::message_pathctrl_path_changed)
		{
			TRACE(_T("message_pathctrl_path_changed from m_path_local. path = %s\n"), pMsg->cur_path);
			bool* res = (bool*)lParam;

			//내 PC, 바탕 화면 등과 같은 경로일 경우는 PathFileExists()로 검사가 안되므로 다른 방법으로 유효한 패스인지 검사해야 한다.
			if (PathFileExists(pMsg->cur_path))
			{
				//res에 true를 넘겨주면 경로가 유효하다는 의미가 되고 그래야만 CPathCtrl에서 경로를 변경하여 표시한다.
				//유효한 경로인지 판별을 main에서 하는 이유는 remote일 경우도 있으므로.
				if (res)
					*res = true;
			}
			else
			{
				AfxMessageBox(_T("입력된 경로를 찾을 수 없습니다."));
				if (res)
					*res = false;
			}
		}
	}

	return 0;
}

void CTestSCColorThemeDlg::OnBnClickedButtonListboxAdd()
{
	int index = m_listbox.add(_T("new item"));
	m_listbox.SetSel(index);
	m_listbox.edit(index);
}

void CTestSCColorThemeDlg::OnBnClickedButtonListboxDelete()
{
	m_listbox.delete_items();
}
