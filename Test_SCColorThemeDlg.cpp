
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

//OnContextMenu 의 컬러 테마 동적 submenu 항목 ID 베이스. enum 인덱스에 더해 사용.
//resource.h 의 _APS_NEXT_COMMAND_VALUE (32775) 보다 충분히 위 → 향후 정적 ID 와 충돌 방지.
#define ID_MENU_COLOR_THEME_BASE   33000

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
	DDX_Control(pDX, IDC_COMBO_FONT, m_combo_font);
	DDX_Control(pDX, IDC_SLIDER_FONT_SIZE, m_slider_fontsize);
	DDX_Control(pDX, IDC_STATIC_FONT_NAME, m_static_fontname);
	DDX_Control(pDX, IDC_STATIC_FONT_SIZE, m_static_fontsize);
	DDX_Control(pDX, IDC_BUTTON_LISTBOX_ADD, m_button_listbox_add);
	DDX_Control(pDX, IDC_BUTTON_LISTBOX_DELETE, m_button_listbox_delete);
}

BEGIN_MESSAGE_MAP(CTestSCColorThemeDlg, CSCThemeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_WINDOWPOSCHANGED()
	ON_CBN_SELCHANGE(IDC_COMBO_THEME, &CTestSCColorThemeDlg::OnCbnSelchangeComboTheme)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT, &CTestSCColorThemeDlg::OnCbnSelchangeComboFont)
	ON_REGISTERED_MESSAGE(Message_CSCSystemButtons, &CTestSCColorThemeDlg::on_message_CSCSystemButtons)
	ON_REGISTERED_MESSAGE(Message_CPathCtrl, &CTestSCColorThemeDlg::on_message_CPathCtrl)
	ON_REGISTERED_MESSAGE(Message_CSCSliderCtrl, &CTestSCColorThemeDlg::on_message_CSCSliderCtrl)
	ON_REGISTERED_MESSAGE(Message_CSCMenu, &CTestSCColorThemeDlg::on_message_CSCMenu)
	ON_REGISTERED_MESSAGE(Message_CSCTreeCtrl, &CTestSCColorThemeDlg::on_message_CSCTreeCtrl)
	ON_REGISTERED_MESSAGE(Message_CVtListCtrlEx, &CTestSCColorThemeDlg::on_message_CVtListCtrlEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CTestSCColorThemeDlg::OnTvnSelchangedTree)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_ADD, &CTestSCColorThemeDlg::OnBnClickedButtonListboxAdd)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_DELETE, &CTestSCColorThemeDlg::OnBnClickedButtonListboxDelete)
	ON_WM_CONTEXTMENU()
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

	m_combo_font.set_as_font_combo();
	m_combo_font.set_line_height(16);
	m_combo_font.set_color_theme(m_theme);

	m_slider_fontsize.set_style(CSCSliderCtrl::style_thumb_round);
	m_slider_fontsize.set_range(6, 100);

	m_edit.set_line_align(DT_VCENTER);
	//m_listbox.set_font_size(10);
	//m_listbox.set_show_selection_always(false);

	//CSCListBox 폰트 quality 자동판정 시연 — IDC_COMBO_FONT(폰트) + IDC_SLIDER_FONT_SIZE(크기).
	//폰트가 그 크기에 비트맵을 가지면 DEFAULT_QUALITY(또렷), 없으면 ANTIALIASED_QUALITY(부드럽게)가 자동 적용.
	//폰트(굴림=비트맵 / Segoe UI=벡터)와 크기를 바꿔가며 전환 경계를 직접 확인.
	m_combo_font.SelectString(-1, _T("Segoe UI"));	//다이얼로그 상속 폰트와 동일
	m_slider_fontsize.set_pos(10);					//listbox 초기 크기와 동일

	m_msgbox.create(this, _T("Test_SCColorTheme"), 0, false);

	//모든 자식 컨트롤 + msgbox 에 테마 전파 (msgbox 는 create 이후라야 하므로 여기서 호출).
	apply_color_theme(false);
	m_msgbox.set_message(_T("<cr=royalblue>테스트 <b><cr=red>메시지 박스</cr></b> 길이에 따라 <b>자동 조정</b>되며\n멀티라인 가능\n<cr=blue>기본 <b><cb=lightpink>HTML 태그</b></cb> 지원"),
		MB_ICONINFORMATION);

	m_edit.set_text(_T("This is a SCEdit control 플레이그라운드."));

	for (int i = 0; i < 15; i++)
	{
		m_listbox.insert(i, i2S(i) + _T(":") + RandomText::GetSlogan());
	}
	m_listbox.insert(-1, _T("한글 테스트 텍스트"));
	m_listbox.set_use_edit();

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

	apply_color_theme(true);
}

void CTestSCColorThemeDlg::apply_color_theme(bool invalidate)
{
	m_sys_buttons.set_color_theme(m_theme, invalidate);
	m_static_color_theme.set_color_theme(m_theme, invalidate);
	m_combo_theme.set_color_theme(m_theme, invalidate);

	m_static_edit.set_color_theme(m_theme, invalidate);
	m_edit.set_color_theme(m_theme, invalidate);

	m_static_staticedit.set_color_theme(m_theme, invalidate);
	m_static_scstaticedit.set_color_theme(m_theme, invalidate);

	m_static_listbox.set_color_theme(m_theme, invalidate);
	m_listbox.set_color_theme(m_theme, invalidate);
	m_listbox.set_color_theme(m_theme, invalidate);
	m_button_listbox_add.set_color_theme(m_theme, invalidate);
	m_button_listbox_delete.set_color_theme(m_theme, invalidate);

	m_static_fontname.set_color_theme(m_theme, invalidate);
	m_static_fontsize.set_color_theme(m_theme, invalidate);
	m_combo_font.set_color_theme(m_theme, invalidate);
	m_slider_fontsize.set_color_theme(m_theme, invalidate);

	m_tree.set_color_theme(m_theme, invalidate);
	m_list.set_color_theme(m_theme, invalidate);
	m_btn_ok.set_color_theme(m_theme, invalidate);
	m_btn_cancel.set_color_theme(m_theme, invalidate);

	m_static_pathctrl.set_color_theme(m_theme, invalidate);
	m_path.set_color_theme(m_theme, invalidate);

	m_msgbox.set_color_theme(m_theme, invalidate);
}

void CTestSCColorThemeDlg::OnCbnSelchangeComboFont()
{
	//font combo 는 OnCbnSelchange 에서 m_lf 를 선택 폰트로 갱신하므로 get_font_name() 이 현재 선택을 반환.
	//set_font_name 이 ReconstructFont 를 호출 → 새 폰트의 비트맵 보유 여부로 AA 모드를 자동 재판정.
	CString font_name = m_combo_font.get_font_name();
	if (font_name.IsEmpty())
		return;

	m_listbox.set_font_name(font_name);
	m_edit.set_font_name(font_name);
	m_static_scstaticedit.set_font_name(font_name);
}

LRESULT CTestSCColorThemeDlg::on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam)
{
	CSCSliderCtrlMsg* msg = (CSCSliderCtrlMsg*)wParam;

	//grab / move / release 모두에서 현재 pos(=pt) 를 즉시 반영해 드래그 중에도 폰트 크기가 따라오게 한다.
	//set_font_size 가 ReconstructFont 를 호출 → 새 크기에서 비트맵 보유 여부로 AA 모드를 자동 재판정.
	int pt = msg->pos;
	m_listbox.set_font_size(pt);
	m_edit.set_font_size(pt);
	m_static_scstaticedit.set_font_size(pt);
	m_static_fontsize.set_textf(_T("Font size %d"), pt);
	return 0;
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

				//tree/list 로 sync — 동일 path 면 각 컨트롤의 set_path 가드가 no-op 으로 cycle 차단.
				m_tree.set_path(pMsg->cur_path);
				m_list.set_path(pMsg->cur_path);
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

void CTestSCColorThemeDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	if (m_menu.GetSafeHwnd() == NULL)
		m_menu.create(this);
	if (m_menu_color_theme.GetSafeHwnd() == NULL)
		m_menu_color_theme.create(this);

	//컬러 테마 submenu 동적 구성 — get_color_theme_list 순서대로 추가, 현재 테마에 check.
	m_menu_color_theme.clear();
	std::deque<CString> theme_list;
	CSCColorTheme::get_color_theme_list(theme_list);
	int cur_theme = m_theme.get_color_theme();
	for (int i = 0; i < (int)theme_list.size(); i++)
		m_menu_color_theme.add(ID_MENU_COLOR_THEME_BASE + i, theme_list[i]);
	m_menu_color_theme.check_item(ID_MENU_COLOR_THEME_BASE + cur_theme, true);

	//메인 메뉴 IDR_MENU_CONTEXT 로딩 후 정적 MENUITEM 인 ID_MENU_COLOR_THEME 를 같은 위치에서 submenu 로 교체.
	m_menu.clear();
	m_menu.load(IDR_MENU_CONTEXT, 0);
	m_menu.replace_item_with_submenu(ID_MENU_COLOR_THEME, &m_menu_color_theme);

	//현재 테마를 두 메뉴에 모두 적용.
	m_menu.set_color_theme(m_theme);
	m_menu_color_theme.set_color_theme(m_theme);

	m_menu.popup_menu(point.x, point.y);
}

LRESULT CTestSCColorThemeDlg::on_message_CSCMenu(WPARAM wParam, LPARAM /*lParam*/)
{
	CSCMenuMessage* msg = (CSCMenuMessage*)wParam;
	if (msg == NULL || msg->m_message != CSCMenu::message_scmenu_selchanged)
		return 0;
	if (msg->m_menu_item == NULL)
		return 0;

	int id = msg->m_menu_item->m_id;
	if (id >= ID_MENU_COLOR_THEME_BASE)
	{
		int theme_index = id - ID_MENU_COLOR_THEME_BASE;
		if (theme_index < 0 || theme_index >= m_combo_theme.GetCount())
			return 0;

		//combo 선택을 맞추고 combobox 선택 핸들러 흐름을 그대로 실행.
		m_combo_theme.SetCurSel(theme_index);
		OnCbnSelchangeComboTheme();
	}
	return 0;
}

//tree 의 폴더 selection 변경 — TVN_SELCHANGED 표준 핸들러로 받아 list/path 로 sync.
//(rename 후 path 변경은 별도 message_path_changed → on_message_CSCTreeCtrl 에서 처리.)
void CTestSCColorThemeDlg::OnTvnSelchangedTree(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
	CString path = m_tree.get_path();
	m_list.set_path(path);
	m_path.set_path(path);
	*pResult = 0;
}

LRESULT CTestSCColorThemeDlg::on_message_CSCTreeCtrl(WPARAM wParam, LPARAM /*lParam*/)
{
	CSCTreeCtrlMessage* msg = (CSCTreeCtrlMessage*)wParam;
	if (msg == NULL)
		return 0;

	if (msg->message == CSCTreeCtrl::message_path_changed)
	{
		m_list.set_path(msg->param0);
		m_path.set_path(msg->param0);
	}
	return 0;
}

LRESULT CTestSCColorThemeDlg::on_message_CVtListCtrlEx(WPARAM wParam, LPARAM lParam)
{
	CVtListCtrlExMessage* msg = (CVtListCtrlExMessage*)wParam;
	if (msg == NULL)
		return 0;

	if (msg->message == CVtListCtrlEx::message_path_changed)
	{
		CString* p = (CString*)lParam;
		if (p == NULL)
			return 0;

		m_tree.set_path(*p);
		m_path.set_path(*p);
	}
	return 0;
}
