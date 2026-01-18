
// Test_SCColorThemeDlg.h: 헤더 파일
//

#pragma once

#include "Common/CDialog/SCThemeDlg/SCThemeDlg.h"
#include "Common/ResizeCtrl.h"
#include "Common/CStatic/SCStatic/SCStatic.h"
#include "Common/CEdit/SCEdit/SCEdit.h"
#include "Common/system/ShellImageList/ShellImageList.h"
#include "Common/CTreeCtrl/SCTreeCtrl/SCTreeCtrl.h"
#include "Common/CListCtrl/CVtListCtrlEx/VtListCtrlEx.h"

// CTestSCColorThemeDlg 대화 상자
class CTestSCColorThemeDlg : public CSCThemeDlg
{
// 생성입니다.
public:
	CTestSCColorThemeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CResizeCtrl		m_resize;
	CShellImageList m_shell_imglist;

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
};
