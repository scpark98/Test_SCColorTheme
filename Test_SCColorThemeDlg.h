
// Test_SCColorThemeDlg.h: 헤더 파일
//

#pragma once

#include "Common/CDialog/SCThemeDlg/SCThemeDlg.h"
#include "Common/ResizeCtrl.h"
#include "Common/CComboBox/SCComboBox/SCComboBox.h"
#include "Common/CStatic/SCStatic/SCStatic.h"
#include "Common/CStatic/PathCtrl/PathCtrl.h"
#include "Common/CEdit/SCEdit/SCEdit.h"
#include "Common/CEdit/CSCStaticEdit/SCStaticEdit.h"
#include "Common/system/ShellImageList/ShellImageList.h"
#include "Common/CTreeCtrl/SCTreeCtrl/SCTreeCtrl.h"
#include "Common/CListCtrl/CVtListCtrlEx/VtListCtrlEx.h"
#include "Common/CButton/GdiButton/GdiButton.h"
#include "Common/CListBox/SCListBox/SCListBox.h"
#include "Common/messagebox/CSCMessageBox/SCMessageBox.h"
#include "Common/CSliderCtrl/SCSliderCtrl/SCSliderCtrl.h"
#include "Common/CMenu/CSCMenuBar/SCMenu.h"
#include "Common/ControlSplitter.h"

// CTestSCColorThemeDlg 대화 상자
class CTestSCColorThemeDlg : public CSCThemeDlg
{
// 생성입니다.
public:
	CTestSCColorThemeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CResizeCtrl			m_resize;
	CShellImageList		m_shell_imglist;
	CSCMessageBox		m_msgbox;

	LRESULT				on_message_CSCSystemButtons(WPARAM wParam, LPARAM lParam);
	LRESULT				on_message_CPathCtrl(WPARAM wParam, LPARAM lParam);
	LRESULT				on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam);
	LRESULT				on_message_CSCMenu(WPARAM wParam, LPARAM lParam);
	LRESULT				on_message_CSCTreeCtrl(WPARAM wParam, LPARAM lParam);
	LRESULT				on_message_CVtListCtrlEx(WPARAM wParam, LPARAM lParam);
	afx_msg void		OnTvnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);

	CSCMenu				m_menu;
	CSCMenu				m_menu_color_theme;

	//모든 자식 컨트롤 + msgbox 에 현재 m_theme 을 전파. invalidate=true 면 즉시 redraw (런타임 테마 변경 시).
	void				apply_color_theme(bool invalidate);

	enum TIMER_ID
	{
		timer_test = 1,
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_SCCOLORTHEME_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CSCTreeCtrl m_tree;
	CVtListCtrlEx m_list;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	CSCComboBox m_combo_theme;
	afx_msg void OnCbnSelchangeComboTheme();
	CSCStatic m_static_color_theme;
	CSCEdit m_edit;
	CSCStatic m_static_edit;
	CGdiButton m_btn_ok;
	CGdiButton m_btn_cancel;
	CSCStatic m_static_listbox;
	CSCListBox m_listbox;
	CSCStatic m_static_staticedit;
	CSCStaticEdit m_static_scstaticedit;
	CSCStatic m_static_pathctrl;
	CPathCtrl m_path;
	afx_msg void OnBnClickedButtonListboxAdd();
	afx_msg void OnBnClickedButtonListboxDelete();
	CSCComboBox m_combo_font;
	afx_msg void OnCbnSelchangeComboFont();
	CSCSliderCtrl m_slider_fontsize;
	CSCStatic m_static_fontname;
	CSCStatic m_static_fontsize;
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	CGdiButton m_button_listbox_add;
	CGdiButton m_button_listbox_delete;
	CControlSplitter m_splitter;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
