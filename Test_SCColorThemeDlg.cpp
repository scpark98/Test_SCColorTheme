
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
	DDX_Control(pDX, IDC_PATH, m_path);
	DDX_Control(pDX, IDC_COMBO_FONT, m_combo_font);
	DDX_Control(pDX, IDC_SLIDER_FONT_SIZE, m_slider_fontsize);
	DDX_Control(pDX, IDC_STATIC_FONT_NAME, m_static_fontname);
	DDX_Control(pDX, IDC_STATIC_FONT_SIZE, m_static_fontsize);
	DDX_Control(pDX, IDC_BUTTON_LISTBOX_ADD, m_button_listbox_add);
	DDX_Control(pDX, IDC_BUTTON_LISTBOX_DELETE, m_button_listbox_delete);
	DDX_Control(pDX, IDC_SPLITTER, m_splitter);
	DDX_Control(pDX, IDC_RADIO_ALIGN_TOP, m_radio_top);
	DDX_Control(pDX, IDC_RADIO_ALIGN_VCENTER, m_radio_vcenter);
	DDX_Control(pDX, IDC_RADIO_ALIGN_BOTTOM, m_radio_bottom);
	DDX_Control(pDX, IDC_CHECK_DISABLE, m_check_disable);
	DDX_Control(pDX, IDC_LIST2, m_list2);
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
	ON_REGISTERED_MESSAGE(Message_CSCListCtrl, &CTestSCColorThemeDlg::on_message_CSCListCtrl)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, &CTestSCColorThemeDlg::OnTvnSelchangedTree)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_ADD, &CTestSCColorThemeDlg::OnBnClickedButtonListboxAdd)
	ON_BN_CLICKED(IDC_BUTTON_LISTBOX_DELETE, &CTestSCColorThemeDlg::OnBnClickedButtonListboxDelete)
	ON_WM_CONTEXTMENU()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTestSCColorThemeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO_ALIGN_BOTTOM, &CTestSCColorThemeDlg::OnBnClickedRadioAlignBottom)
	ON_BN_CLICKED(IDC_RADIO_ALIGN_TOP, &CTestSCColorThemeDlg::OnBnClickedRadioAlignTop)
	ON_BN_CLICKED(IDC_RADIO_ALIGN_VCENTER, &CTestSCColorThemeDlg::OnBnClickedRadioAlignVCenter)
	ON_BN_CLICKED(IDC_CHECK_DISABLE, &CTestSCColorThemeDlg::OnBnClickedCheckDisable)
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
	m_resize.Add(IDC_PATH, 0, 0, 100, 0);
	m_resize.Add(IDC_TREE, 0, 0, 0, 100);
	m_resize.Add(IDC_LIST, 0, 0, 100, 100);
	m_resize.Add(IDC_SPLITTER, 0, 0, 0, 100);
	m_resize.Add(IDC_LIST2, 0, 0, 0, 100);

	m_check_disable.set_auto_color(false);
	m_radio_top.set_auto_color(false);
	m_radio_vcenter.set_auto_color(false);
	m_radio_bottom.set_auto_color(false);

	m_splitter.set_type(CControlSplitter::CS_VERT);
	m_splitter.AddToTopOrLeftCtrls(IDC_TREE);
	m_splitter.AddToBottomOrRightCtrls(IDC_LIST);

	m_tree.set_as_shell_treectrl(&theApp.m_shell_imagelist);
	m_tree.set_use_drag_and_drop(true);
	m_tree.add_drag_images(IDB_DRAG_SINGLE_FILE, IDB_DRAG_MULTI_FILES);

	m_list.set_as_shell_listctrl(&theApp.m_shell_imagelist);
	m_path.set_shell_imagelist(&theApp.m_shell_imagelist, true);
	m_list.set_header_height(28);
	m_list.set_line_height(26);
	//20260709 by claude. 탐색기 파일목록 폰트 = 시스템 IconTitleFont(SPI_GETICONTITLELOGFONT). 한국어 Windows 에선 '맑은 고딕' 9pt 다.
	//(앞서 Segoe UI 로 하드코딩했다가 탐색기와 달라 보였음 — Segoe UI 는 이 목록의 폰트가 아니다.) 시스템 폰트를 그대로 상속해 로케일 무관 일치.
	LOGFONT lf_icon = { 0 };
	if (SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(lf_icon), &lf_icon, 0))
		m_list.set_log_font(lf_icon);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_CHECKBOXES);
	m_list.set_use_drag_and_drop(true);
	m_list.add_drag_images(IDB_DRAG_SINGLE_FILE, IDB_DRAG_MULTI_FILES);


	m_tree.set_path(_T("D:\\Temp"));

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

	m_splitter.set_back_color(m_theme.cr_back);
	m_combo_font.set_as_font_combo();
	m_combo_font.set_line_height(16);
	m_combo_font.set_color_theme(m_theme);

	m_slider_fontsize.set_style(CSCSliderCtrl::style_thumb_round);
	m_slider_fontsize.set_range(8, 108);
	m_slider_fontsize.set_tic_freq(20);
	//m_slider_fontsize.set_auto_snap(true);	//드래그 시 가장 가까운 틱으로 스냅 동작 확인
	//m_slider_fontsize.set_tic_only();		//드래그 시 가장 가까운 틱으로만 이동

	m_edit.set_line_align(DT_VCENTER);
	//m_listbox.set_font_size(10);
	//m_listbox.set_show_selection_always(false);

	//CSCListBox 폰트 quality 자동판정 시연 — IDC_COMBO_FONT(폰트) + IDC_SLIDER_FONT_SIZE(크기).
	//폰트가 그 크기에 비트맵을 가지면 DEFAULT_QUALITY(또렷), 없으면 ANTIALIASED_QUALITY(부드럽게)가 자동 적용.
	//폰트(굴림=비트맵 / Segoe UI=벡터)와 크기를 바꿔가며 전환 경계를 직접 확인.
	//20260826 by claude. 마지막으로 고른 폰트·크기를 복원한다. 기본값은 다이얼로그 상속 폰트(Segoe UI) + listbox 초기 크기(10).
	CString font_name = theApp.GetProfileString(_T("setting"), _T("font name"), _T("Segoe UI"));
	int font_size = theApp.GetProfileInt(_T("setting"), _T("font size"), 10);

	//SelectString 과 달리 set_cur_sel 은 font combo 의 m_lf 까지 동기화한다 (CBN_SELCHANGE 가 안 오므로).
	int font_index = m_combo_font.FindStringExact(-1, font_name);
	if (font_index >= 0)
		m_combo_font.set_cur_sel(font_index);

	m_slider_fontsize.set_pos(font_size);

	m_msgbox.create(this, _T("Test_SCColorTheme"), 0, false);

	//모든 자식 컨트롤 + msgbox 에 테마 전파 (msgbox 는 create 이후라야 하므로 여기서 호출).
	apply_color_theme(false);
	m_msgbox.set_message(_T("<cr=royalblue>테스트 <b><cr=red>메시지 박스.</cr></b> 텍스트 길이에 따라 <b>자동 조정</b>되며\n멀티라인 가능\n<cr=blue>기본 <b><cb=lightpink>HTML 태그</b></cb> 지원"),
		MB_ABORTRETRYIGNORE | MB_ICONINFORMATION);

	m_edit.set_text(_T("This is a SCEdit control 플레이그라운드."));

	for (int i = 0; i < 15; i++)
	{
		m_listbox.insert(i, i2S(i) + _T(":") + RandomText::GetSlogan());
	}
	m_listbox.insert(-1, _T("한글 테스트 텍스트"));
	m_listbox.set_use_edit();

	init_list2();

	//20260807 by claude. 툴팁 인스턴스·Create·relay 는 CSCThemeDlg 가 소유하므로 여기서는 내용만 등록한다.
	//Disable 체크로 이 컨트롤들을 disable 시켜도 툴팁이 그대로 뜨는지가 확인 포인트.
	m_tooltip.AddTool(&m_edit, _T("<b>CSCEdit</b><br>native CEdit 파생. disable 시 테두리가 사라진다."));
	m_tooltip.AddTool(&m_static_scstaticedit, _T("<b>CSCStaticEdit</b><br><cr=royalblue>CStatic</cr> 기반 자체 그리기 edit."));
	m_tooltip.AddTool(&m_combo_theme, _T("<b>CSCComboBox</b><br>color theme 을 바꾼다.<br><cr=gray>툴팁 색도 함께 바뀐다.</cr>"));

	//<indent> 는 문단 전체를, <hang> 은 wrap 으로 이어진 줄만 민다. 일부러 max_width 를 넘겨 wrap 을 만든다.
	m_tooltip.AddTool(&m_path,
		_T("<la=bottom><b>CPathCtrl</b> <sz=8><cr=gray>(탐색기 주소표시줄)</cr></sz>")
		_T("<br><indent=10><hang=14>경로가 길어 한 줄에 들어가지 않으면 자동으로 줄이 바뀌고, ")
		_T("이어지는 줄만 hang 만큼 더 들여쓴다. indent 는 문단 전체를 미는 값이다.<br>&lt;br&gt;에 의해 다음 라인으로 줄바꿈되면 왼쪽에 들여쓰기가 없다."));
	m_tooltip.AddTool(&m_tree, _T("<b>CSCTreeCtrl</b><br>커스텀 스크롤바 · disable 시 입력 무시."));
	m_tooltip.AddTool(&m_list, _T("<b>CSCListCtrl</b><br>shell list 모드."));
	m_tooltip.AddTool(&m_check_disable, _T("모든 컨트롤들을 <cr=crimson><b>disable</cr></b> 시킨다.<br>disable 상태에서도 이 툴팁들이 표시된다."));

	//20260828 by claude. 아래 툴팁들은 컨트롤 설명이면서 동시에 CSCParagraph 태그의 표본이다.
	//어떤 태그가 툴팁에서 실제로 어떻게 그려지는지 한 화면에서 비교할 수 있도록 컨트롤마다 서로 다른 태그를 배분했다.
	//색은 태그 안에서만 지정한다 — 컨트롤 자체에는 여전히 set_color_theme(m_theme) 한 줄뿐이다.
	//제목 줄에 <la=bottom> 을 붙이는 이유 : 라인의 기본 세로 정렬은 DT_TOP 이라 크기가 다른 run 을 한 줄에
	//섞으면 작은 글자가 윗변에 붙어 떠 보인다. 아랫변을 맞춰야 글자들이 같은 기준선에 놓인 것처럼 읽힌다.

	//<al> 가운데 정렬 + <grad> 글자 그라디언트. 그라디언트 시작색은 테마의 cr_text 라 테마를 따라간다.
	m_tooltip.AddTool(&m_static_color_theme,
		_T("<al=center><sz=12><b><grad=violet>CSCStatic</grad></b></sz>")
		_T("<br><al=center>태그 텍스트를 그리는 라벨")
		_T("<br><ls=0.5><al=center><sz=8><cr=gray>al=center · grad=색</cr></sz>"));

	//<st>/<cs> 외곽선, <ts> 그림자 목록 (앞 항목이 글자에 더 가깝게 그려진다).
	m_tooltip.AddTool(&m_static_edit,
		_T("<la=bottom><b>CSCStatic</b> <sz=8><cr=gray>(CSCEdit 라벨)</cr></sz>")
		_T("<br><ls=0.8><st=3><cs=black><cr=gold>외곽선 st=3 · cs=black</cr></cs></st>")
		_T("<br><ts=0,2,4,black;0,0,10,deepskyblue>그림자 두 겹 ts=x,y,blur,색</ts>"));

	//<sup>/<sub> 위·아래 첨자.
	m_tooltip.AddTool(&m_static_staticedit,
		_T("<b>CSCStatic</b><br>위 첨자 x<sup>2</sup> · 아래 첨자 H<sub>2</sub>O")
		_T("<br><ls=1.4><sz=8><cr=gray>sup · sub</cr></sz>"));

	//<box> run 을 여백만큼 부풀린 라운드 배경.
	m_tooltip.AddTool(&m_static_listbox,
		_T("<la=bottom><b>CSCStatic</b> <box=royalblue,10,6><cr=white>label</cr></box>")
		_T("<br><ls=0.8>오른쪽 리스트박스를 가리키는 라벨"));

	m_tooltip.AddTool(&m_listbox,
		_T("<b>CSCListBox</b>")
		_T("<br><ls=0.8><b>F2</b> 로 <box=seagreen,10,5><cr=white>편집</cr></box>, <b>Delete</b> 로 삭제.")
		_T("<br><ls=1.4><sz=8><cr=gray>box=색,반지름,여백</cr></sz>"));

	m_tooltip.AddTool(&m_btn_ok, _T("<la=bottom><b>CGdiButton</b> <sz=8><cr=gray>(확인)</cr></sz>"));

	//<glow> 는 <ts=0,0,sigma,색,sigma> 의 축약이라 offset 이 0 이고 사방으로 퍼진다.
	//sigma 는 글자 크기에 맞춰야 한다 — spread 가 sigma 와 같아서, 9pt 글자에 12 를 주면
	//글리프가 서로 붙어 덩어리가 되고 발광이 아니라 얼룩으로 보인다.
	m_tooltip.AddTool(&m_btn_cancel,
		_T("<la=bottom><b>CGdiButton</b> <sz=8><cr=gray>(취소)</cr></sz>")
		_T("<br><ls=0.8><glow=orangered,4><b>glow</b></glow> 로 글자 주위를 <glow=gold>발광</glow>시킨다."));

	//<box> 는 단어를 감싼다 — 여백이 글자 박스(라인 높이) 기준이라 한 글자 run 은 세로로 길쭉해진다.
	m_tooltip.AddTool(&m_button_listbox_add,
		_T("<box=seagreen,9,5><cr=white><b>추가</b></cr></box> 항목을 넣고 바로 편집 상태가 된다."));

	//<cr=#AARRGGBB> — 8자리는 alpha 가 앞에 온다(RRGGBBAA 아님).
	m_tooltip.AddTool(&m_button_listbox_delete,
		_T("<box=crimson,9,5><cr=white><b>삭제</b></cr></box> 선택한 항목을 지운다.")
		_T("<br><ls=1.4><sz=8><cr=gray>#AARRGGBB 도 쓴다 → <cr=#80CC3333>반투명 글자</cr></cr></sz>"));

	//<tab> 은 다음 run 의 라인 내 시작 x 를 고정한다 — 툴팁 안에 표를 만들 수 있다.
	m_tooltip.AddTool(&m_combo_font,
		_T("<la=bottom><b>CSCComboBox</b> <sz=8><cr=gray>(font)</cr></sz>")
		_T("<br><ls=0.8><u>태그<tab=96>기능</u>")
		_T("<br>tab<tab=96>다음 run 의 시작 x 고정")
		_T("<br>f<tab=96>구간 글꼴")
		_T("<br>sz<tab=96>구간 글자 크기"));

	//<sp> 자간(음수 = 좁힘).
	m_tooltip.AddTool(&m_slider_fontsize,
		_T("<b>CSCSliderCtrl</b>")
		_T("<br><ls=0.8>글자 크기를 8<sub>pt</sub> 부터 108<sup>pt</sup> 까지 바꾼다.")
		_T("<br><sp=4>넓은 자간 sp=4</sp> · <sp=-1>좁은 sp=-1</sp>"));

	//<f> run 마다 다른 글꼴.
	m_tooltip.AddTool(&m_static_fontname,
		_T("<b>CSCStatic</b>")
		_T("<br><ls=0.8><f=Consolas>Consolas</f> · <f=Georgia><i>Georgia</i></f> · <f=Impact>Impact</f>")
		_T("<br><ls=1.4><sz=8><cr=gray>f=글꼴 — run 단위로 글꼴이 바뀐다</cr></sz>"));

	//<la> 는 크기가 다른 run 이 섞인 라인의 세로 기준선을 고른다.
	m_tooltip.AddTool(&m_static_fontsize,
		_T("<b>CSCStatic</b>")
		_T("<br><ls=0.8><la=bottom><sz=8>8</sz> <sz=12>12</sz> <sz=16>16</sz> <sz=20>20</sz>")
		_T("<br><ls=1.4><sz=8><cr=gray>la=bottom — 아랫변을 맞춘다</cr></sz>"));

	//<ruby> 는 바로 다음 run 하나 위에 0.5 배 주석을 얹는다. <cru> 로 루비 색만 따로 준다.
	//세 라디오는 CSCEdit 과 CSCStaticEdit 두 컨트롤의 set_line_align 을 함께 바꾼다.
	m_tooltip.AddTool(&m_radio_top,
		_T("<la=bottom><b>CGdiButton</b> <sz=8><cr=gray>(radio)</cr></sz>")
		_T("<br><ls=0.8><ruby=うえ>上</ruby> CSCEdit·CSCStaticEdit 글자를 <b>위</b>로."));

	m_tooltip.AddTool(&m_radio_vcenter,
		_T("<la=bottom><b>CGdiButton</b> <sz=8><cr=gray>(radio)</cr></sz>")
		_T("<br><ls=0.8><cru=orange><ruby=なか>中</ruby></cru> CSCEdit·CSCStaticEdit 글자를 <b>가운데</b>로.")
		_T("<br><ls=1.4><sz=8><cr=gray>cru=루비 색</cr></sz>"));

	m_tooltip.AddTool(&m_radio_bottom,
		_T("<la=bottom><b>CGdiButton</b> <sz=8><cr=gray>(radio)</cr></sz>")
		_T("<br><ls=0.8><ruby=した>下</ruby> CSCEdit·CSCStaticEdit 글자를 <b>아래</b>로."));

	//<nowrap> 구간은 word-wrap 이 쪼개지 않는다.
	m_tooltip.AddTool(&m_splitter,
		_T("<b>CControlSplitter</b>")
		_T("<br><ls=0.8>드래그하면 트리와 리스트의 폭이 나뉜다.")
		_T("<br><nowrap>이 문장은 nowrap 이라 쪼개지지 않는다</nowrap>"));

	m_tooltip.AddTool(&m_list2,
		_T("<la=bottom><b>CSCListCtrl</b> <sz=8><cr=gray>(report)</cr></sz>")
		_T("<br><ls=0.8><u>컬럼<tab=64>폭<tab=104>내용</u>")
		_T("<br>No<tab=64>50<tab=104>순번")
		_T("<br>Name<tab=64>150<tab=104>이름")
		_T("<br>Slogan<tab=64>200<tab=104>표어")
		_T("<br>Score<tab=64>100<tab=104><cr=seagreen>점수</cr>")
		_T("<br>Memo<tab=64>200<tab=104>비고")
		_T("<br><ls=1.4><sz=8><cr=gray>체크박스 · 전체 행 선택</cr></sz>"));

	//20260826 by claude. 콤보·슬라이더에 값만 넣어서는 컨트롤들에 반영되지 않는다 — 프로그램적 변경은 알림이 오지 않는다.
	//msgbox 까지 만들어진 이 시점에서 사용자가 직접 고른 것과 같은 경로로 한 번 적용한다.
	OnCbnSelchangeComboFont();
	apply_font_size(font_size);

	RestoreWindowPosition(&theApp, this);

	SetTimer(timer_test, 100, NULL);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

//shelllist가 아닌 일반 ListCtrl
void CTestSCColorThemeDlg::init_list2()
{
	//m_list2.set_use_virtual_list(false);

	m_list2.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);// | LVS_EX_GRIDLINES);
	//m_list2.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_AUTOCHECKSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB);
	//m_list2.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FLATSB);

	m_list2.set_headings(_T("No,50;Name,150;Slogan,200;Score,100;Memo,200"));
	//m_list2.set_color_theme(CVtListCtrlEx::color_theme_dark_gray);
	//m_list2.set_line_height(theApp.GetProfileInt(_T("list name"), _T("line height"), 80));

	m_list2.set_font_size(theApp.GetProfileInt(_T("list"), _T("font size"), 9));
	m_list2.set_font_name(theApp.GetProfileString(_T("list"), _T("font name"), _T("맑은 고딕")));

	m_list2.restore_column_width(&theApp, _T("list name"));
	m_list2.set_header_height(24);
	m_list2.set_line_height(24);
	//m_list2.get_header_ctrl()->set_font_bold();
	//m_list2.get_header_ctrl()->use_header_separator(false);

	//m_list2.draw_top_line(true);// , Gdiplus::Color::Red);
	//m_list2.draw_bottom_line(true);// , Gdiplus::Color::Blue);

	//shell listctrl은 아니지만 파일 아이콘이 제대로 표시되는지 확인하기 위해 아래와 같이 세팅함.
	m_list2.set_use_own_imagelist(true);
	m_list2.set_shell_imagelist(&theApp.m_shell_imagelist);


	//m_list2.set_column_text_align(0, HDF_CENTER);
	//m_list2.set_column_text_align(0, HDF_CENTER);
	m_list2.set_column_text_align(1, HDF_CENTER);
	m_list2.set_column_text_align(2, HDF_RIGHT);
	/*
	m_list2.set_header_text_align(0, HDF_CENTER);
	m_list2.set_header_text_align(1, HDF_CENTER);
	m_list2.set_header_text_align(2, HDF_CENTER);
	m_list2.set_header_text_align(3, HDF_LEFT);
	*/
	//m_list2.set_column_data_type(col_score, CVtListCtrlEx::column_data_type_percentage_grid);
	m_list2.set_column_data_type(col_score, CSCListCtrl::column_data_type_progress);
	m_list2.show_progress_text();
	//m_list2.set_back_alternate_color(true, Gdiplus::Color(242, 242, 242));
	//m_list2.set_progress_color(Gdiplus::Color(255, 187, 255));
	//m_list2.set_progress_text_color(Gdiplus::Color::Black);
	m_list2.allow_edit();


	m_list2.set_use_drag_and_drop(true);
	m_list2.add_drag_images(IDB_DRAG_SINGLE_FILE, IDB_DRAG_MULTI_FILES);
	//20260705 by claude. 소스=로컬 리스트. 드래그 중 대상 드라이브에 따라 "+ …로 복사" 문구 표시.
	//m_list2.set_drag_hint_provider([this](CWnd* pDropWnd, CPoint pt) { return compute_drag_hint(&m_list_local, pDropWnd, pt); });


	//RandomText를 이용한 테스트 데이터 추가
	srand(time(NULL));

	//debug mode에서
	//10,000개 추가 시 invalidate = false, SetRedraw(FALSE) 할 경우 약 6초, true로 할 경우는 약 26초 소요

	long t0 = clock();
	bool make_invalidate = false;
	//m_list2.SetRedraw(FALSE);

	for (int i = 0; i < 15; i++)
	{
		int index = m_list2.add_item(i2S(i) + RandomText::extension(true), -1, false, make_invalidate);
		m_list2.set_text(index, col_name, RandomText::GetName(), make_invalidate);
		//m_list2.set_text_color(index, 0, RGB(index, index, index));//random19937(RGB(0,0,0), RGB(255,255,255)));
		m_list2.set_text(index, col_slogan, RandomText::GetSlogan(), make_invalidate);
		//m_list2.set_text_color(index, index, RGB(indexi, 0, 0));//random19937(RGB(0,0,0), RGB(255,255,255)));
		m_list2.set_text(index, col_score, i2S(random19937(0, 100)), make_invalidate);
		//m_list2.set_text_color(index, 2, RGB(0, 0, 255-index));//random19937(RGB(0,0,0), RGB(255,255,255)));
		m_list2.set_text(index, col_memo, RandomText::GetName(), make_invalidate);
	}

	//m_list2.SetRedraw(TRUE);
	//SetWindowText(i2S(clock() - t0));

	//수동 테스트 데이터 추가
	m_list2.add_item(_T("0.txt"));
	m_list2.add_item(_T("1.mp4"));
	m_list2.add_item(_T("2.html"));
	m_list2.add_item(_T("3.exe"));
	m_list2.add_item(_T("4.dat"));
	m_list2.add_item(_T("5.ini"));

	m_list2.SetCheck(0, true);

	m_list2.set_text(0, col_score, _T("50"));
	m_list2.set_text(1, col_score, _T("fail"));

	for (int i = 0; i < m_list2.size(); i++)
		m_list2.SetItemData(i, i);

	m_list2.set_text_color(0, col_no, Gdiplus::Color::Red);
	m_list2.set_back_color(0, col_no, Gdiplus::Color::RoyalBlue);
	m_list2.set_text_color(1, col_name, Gdiplus::Color::Pink);
	m_list2.set_back_color(1, col_score, Gdiplus::Color::Red);

	//m_list2.set_item_color(2, 0, Gdiplus::Color::Red, Gdiplus::Color::Blue);
	//m_list2.set_text_color(3, 0, Gdiplus::Color::Red);
	//m_list2.set_back_color(3, 1, Gdiplus::Color::Red);
	//m_list2.set_item_color(4, 0, Gdiplus::Color::DeepPink, Gdiplus::Color::DodgerBlue);
	//m_list2.set_text_color(5, 0, Gdiplus::Color::DeepPink);
	//m_list2.set_back_color(5, 1, Gdiplus::Color::DeepPink);
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
	m_splitter.set_back_color(m_theme.cr_back);

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

	m_check_disable.set_color_theme(m_theme, invalidate);
	m_radio_top.set_color_theme(m_theme, invalidate);
	m_radio_vcenter.set_color_theme(m_theme, invalidate);
	m_radio_bottom.set_color_theme(m_theme, invalidate);

	m_tree.set_color_theme(m_theme, invalidate);
	m_list.set_color_theme(m_theme, invalidate);
	m_list2.set_color_theme(m_theme, invalidate);

	m_btn_ok.set_color_theme(m_theme, invalidate);
	m_btn_cancel.set_color_theme(m_theme, invalidate);

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

	theApp.WriteProfileString(_T("setting"), _T("font name"), font_name);

	m_listbox.set_font_name(font_name);
	m_edit.set_font_name(font_name);
	m_static_scstaticedit.set_font_name(font_name);
	//m_msgbox.set_font(font_name);

	//20260709 by claude. 폰트명 변경을 tree/m_list/m_list2 에도 적용(사용자 요청). list 는 invalidate 기본값이 false 라 즉시 재그리기 위해 true 전달(트리는 항상 invalidate).
	m_tree.set_font_name(font_name);
	m_list.set_font_name(font_name, DEFAULT_CHARSET, true);
	m_list2.set_font_name(font_name, DEFAULT_CHARSET, true);
}

LRESULT CTestSCColorThemeDlg::on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam)
{
	CSCSliderCtrlMsg* msg = (CSCSliderCtrlMsg*)wParam;

	//grab / move / release 모두에서 현재 pos(=pt) 를 즉시 반영해 드래그 중에도 폰트 크기가 따라오게 한다.
	int pt = msg->pos;
	apply_font_size(pt);

	//20260826 by claude. 드래그 중(move)에는 저장하지 않는다 — 한 번 드래그에 레지스트리 쓰기가 수십 번 발생한다.
	if (msg->msg == CSCSliderCtrlMsg::msg_thumb_release || msg->msg == CSCSliderCtrlMsg::msg_thumb_track_bottom_slide)
		theApp.WriteProfileInt(_T("setting"), _T("font size"), pt);

	return 0;
}

void CTestSCColorThemeDlg::apply_font_size(int pt)
{
	//set_font_size 가 ReconstructFont 를 호출 → 새 크기에서 비트맵 보유 여부로 AA 모드를 자동 재판정.
	m_listbox.set_font_size(pt);
	m_edit.set_font_size(pt);
	m_static_scstaticedit.set_font_size(pt);
	m_static_fontsize.set_textf(_T("Font size %d"), pt);
	//m_msgbox.set_font(_T(""), pt);

	//20260709 by claude. 폰트 크기 변경을 tree/m_list/m_list2 에도 적용(사용자 요청). list 는 invalidate 기본값 false 라 즉시 재그리기 위해 true 전달.
	m_tree.set_font_size(pt);
	m_list.set_font_size(pt, true);
	m_list2.set_font_size(pt, true);
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
	CPathCtrlMessage* msg = (CPathCtrlMessage*)wParam;

	//m_path2도 동일한 처리가 필요하지만 이 예제에서는 m_path만 처리한다.
	if (msg->pThis == &m_path)
	{
		if (msg->message == CPathCtrl::message_pathctrl_path_changed)
		{
			bool* res = (bool*)lParam;
			CPathCtrl* pPath = (CPathCtrl*)(msg->pThis);
			CString real_path = pPath->get_shell_imagelist()->convert_special_folder_to_real_path((pPath->get_is_local() ? 0 : 1), msg->cur_path);
			TRACE(_T("message_pathctrl_path_changed from m_path_local. path = %s, real_path = %s\n"), msg->cur_path, real_path);

			//내 PC, 바탕 화면 등과 같은 경로일 경우는 PathFileExists()로 검사가 안되므로 다른 방법으로 유효한 패스인지 검사해야 한다.
			//20260708 by claude. 특수폴더(내 PC/바탕 화면/문서)는 실경로가 없어 PathFileExists 가 false → is_special_folder 로 먼저 유효 판정.
			//(이 예외가 빠져 "내 PC" 클릭 시 "경로를 찾을 수 없습니다" 가 재발했다.) 그 외 실경로는 종전대로 convert→PathFileExists 로 검증.
			if (pPath->get_shell_imagelist()->is_special_folder(pPath->get_is_local() ? 0 : 1, msg->cur_path) || PathFileExists(real_path))
			{
				//res에 true를 넘겨주면 경로가 유효하다는 의미가 되고 그래야만 CPathCtrl에서 경로를 변경하여 표시한다.
				//유효한 경로인지 판별을 main에서 하는 이유는 remote일 경우도 있으므로.
				if (res)
					*res = true;

				//tree/list 로 sync — 동일 path 면 각 컨트롤의 set_path 가드가 no-op 으로 cycle 차단.
				m_tree.set_path(msg->cur_path);
				m_list.set_path(msg->cur_path);
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
	else if (msg->message == CSCTreeCtrl::message_drive_volume_changed)
	{
		//트리에서 드라이브 볼륨 변경 → 리스트 동기화(+공유 캐시). 트리 자신은 edit_end 가 이미 노드 텍스트를 갱신했다.
		sync_drive_volume(msg->param0, msg->param1);
	}
	return 0;
}

LRESULT CTestSCColorThemeDlg::on_message_CSCListCtrl(WPARAM wParam, LPARAM lParam)
{
	CSCListCtrlMessage* msg = (CSCListCtrlMessage*)wParam;
	if (msg == NULL)
		return 0;

	if (msg->message == CSCListCtrl::message_path_changed)
	{
		CString* p = (CString*)lParam;
		if (p == NULL)
			return 0;

		m_tree.set_path(*p);
		m_path.set_path(*p);
	}
	else if (msg->message == CSCListCtrl::message_drive_volume_changed)
	{
		//리스트에서 드라이브 볼륨 변경 → 트리 동기화(+공유 캐시). 리스트 자신은 edit_end 가 이미 셀을 갱신했다. param0=root, param1=새 레이블.
		sync_drive_volume(msg->param0, msg->param1);
	}
	return 0;
}

//20260708 by claude. 드라이브 볼륨 레이블 변경을 형제 컨트롤(트리↔리스트)에 반영한다. pathctrl 은 내 PC 뷰에선 바꿀 게 없어 대상 아님.
//표시 라벨은 "볼륨명 (X:)" 형식. (1) 공유 드라이브 캐시 라벨 갱신 → (2) 리스트 refresh(드라이브뷰면 재열거) → (3) 트리 드라이브 노드 텍스트 직접 갱신.
void CTestSCColorThemeDlg::sync_drive_volume(CString drive_root, CString new_label)
{
	if (drive_root.IsEmpty())
		return;
	if (drive_root.Right(1) != _T('\\'))
		drive_root += _T('\\');

	CString disp;
	disp.Format(_T("%s (%c:)"), (LPCTSTR)new_label, drive_root[0]);

	//(1) 공유 드라이브 캐시(CShellImageList 드라이브 리스트) 라벨 갱신 — 리스트는 get_drive_list 로 드라이브뷰를 채우므로 이후 refresh 가 새 라벨을 읽는다.
	std::deque<CDiskDriveInfo>* drives = theApp.m_shell_imagelist.get_drive_list(0);
	if (drives != NULL)
	{
		for (auto& d : *drives)
		{
			CString dp = d.path;
			if (dp.Right(1) != _T('\\'))
				dp += _T('\\');
			if (dp.CompareNoCase(drive_root) == 0)
			{
				_tcscpy_s(d.label, _countof(d.label), (LPCTSTR)disp);
				break;
			}
		}
	}

	//(2) 리스트: 드라이브뷰면 refresh 로 새 라벨 반영(set_path 재진입, refresh=true 기본).
	m_list.set_path(m_list.get_path());

	//(3) 트리: 내 PC 하위 드라이브 노드 텍스트를 직접 갱신(트리는 노드가 영속이라 자동 재열거되지 않는다).
	//20260708 by claude. 노드는 '드라이브 문자 (X:)' 로 찾는다. convert(get_path(노드)) 로 찾으면, 위 (1)에서 캐시 라벨을 이미 새 값으로
	//바꿔놔서 노드의 옛 라벨을 root 로 매핑하는 게 깨져 못 찾는다(트리 미갱신 버그의 원인). 드라이브 문자는 캐시와 무관하니 안전.
	HTREEITEM pc = m_tree.find_item(theApp.m_shell_imagelist.m_volume[0].get_label(CSIDL_DRIVES));
	if (pc != NULL)
	{
		CString letter;
		letter.Format(_T("(%c:)"), drive_root[0]);		//예: "(D:)"
		for (HTREEITEM ch = m_tree.GetChildItem(pc); ch != NULL; ch = m_tree.GetNextSiblingItem(ch))
		{
			if (m_tree.GetItemText(ch).Find(letter) >= 0)
			{
				m_tree.SetItemText(ch, disp);
				break;
			}
		}
	}
}

void CTestSCColorThemeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_test)
	{
		KillTimer(timer_test);
		//m_list.set_path(_T("C:\\Program Files (x86)"));
		//m_list.set_column_width(2, 500, true);
		//CRect rcw;
		//GetWindowRect(&rcw);
		//int x = rcw.left, y = rcw.top, w = rcw.Width();
		//MoveWindow(x, y, w, 460); m_list.Scroll(CSize(0, 100000));
		//MoveWindow(x, y, w, 440); m_list.Scroll(CSize(0, 100000));
		//MoveWindow(x, y, w, 420); m_list.Scroll(CSize(0, 100000));
	}

	CSCThemeDlg::OnTimer(nIDEvent);
}

void CTestSCColorThemeDlg::OnBnClickedOk()
{
	m_msgbox.DoModal(_T("asldf"));
}

void CTestSCColorThemeDlg::OnBnClickedRadioAlignTop()
{
	m_edit.set_line_align(DT_TOP);
	m_static_scstaticedit.set_line_align(DT_TOP);
}

void CTestSCColorThemeDlg::OnBnClickedRadioAlignVCenter()
{
	m_edit.set_line_align(DT_VCENTER);
	m_static_scstaticedit.set_line_align(DT_VCENTER);
}

void CTestSCColorThemeDlg::OnBnClickedRadioAlignBottom()
{
	m_edit.set_line_align(DT_BOTTOM);
	m_static_scstaticedit.set_line_align(DT_BOTTOM);
}

void CTestSCColorThemeDlg::OnBnClickedCheckDisable()
{
	//m_check_disable 자신은 제외 — disable 하면 다시 켤 수 없다.
	BOOL enable = (m_check_disable.GetCheck() == BST_CHECKED) ? FALSE : TRUE;

	//m_sys_buttons.EnableWindow(enable);
	//m_static_color_theme.EnableWindow(enable);
	//m_combo_theme.EnableWindow(enable);

	m_static_edit.EnableWindow(enable);
	m_edit.EnableWindow(enable);

	m_static_staticedit.EnableWindow(enable);
	m_static_scstaticedit.EnableWindow(enable);

	m_static_listbox.EnableWindow(enable);
	m_listbox.EnableWindow(enable);
	m_button_listbox_add.EnableWindow(enable);
	m_button_listbox_delete.EnableWindow(enable);

	m_static_fontname.EnableWindow(enable);
	m_static_fontsize.EnableWindow(enable);
	m_combo_font.EnableWindow(enable);
	m_slider_fontsize.EnableWindow(enable);

	m_radio_top.EnableWindow(enable);
	m_radio_vcenter.EnableWindow(enable);
	m_radio_bottom.EnableWindow(enable);

	m_tree.EnableWindow(enable);
	m_list.EnableWindow(enable);
	m_list2.EnableWindow(enable);

	m_btn_ok.EnableWindow(enable);
	m_btn_cancel.EnableWindow(enable);

	m_path.EnableWindow(enable);

	m_msgbox.EnableWindow(enable);
}
