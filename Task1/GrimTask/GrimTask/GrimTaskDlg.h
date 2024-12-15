
// GrimTaskDlg.h: 헤더 파일
//

#pragma once

#define IMAGE_WIDTH_RATE	0.7
#define IMAGE_HEIGHT_RATE	0.65
#define DLG_WEIGHT			1280
#define DLG_HEIGHT			1024

// CGrimTaskDlg 대화 상자
class CGrimTaskDlg : public CDialogEx
{
// 생성입니다.
public:
	CGrimTaskDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRIMTASK_DIALOG };
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
	afx_msg void OnSize(UINT nType, int cx, int cy);

private:
	CFont m_fontTitle;
	CFont m_fontNormal;

	CImage m_image;
};
