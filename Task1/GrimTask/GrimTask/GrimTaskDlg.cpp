﻿
// GrimTaskDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GrimTask.h"
#include "GrimTaskDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CGrimTaskDlg 대화 상자



CGrimTaskDlg::CGrimTaskDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRIMTASK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGrimTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGrimTaskDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGrimTaskDlg 메시지 처리기

BOOL CGrimTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	// Set size of the dlg
	CRect rect;
	GetClientRect(&rect);
	rect.right = 1280;
	rect.bottom = 1024;
	MoveWindow(&rect);

	// Title 폰트 생성 (초기화)
	m_TitleFont.CreatePointFont(300, _T("Arial"));
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&m_TitleFont);

	m_NormalFont.CreatePointFont(150, _T("Arial"));
	GetDlgItem(IDC_STATIC_START)->SetFont(&m_NormalFont);
	GetDlgItem(IDC_STATIC_END)->SetFont(&m_NormalFont);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGrimTaskDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGrimTaskDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGrimTaskDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGrimTaskDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!IsWindow(GetDlgItem(IDC_STATIC_TITLE)->GetSafeHwnd())) {
		// 컨트롤이 초기화되지 않았다면 종료
		return;
	}

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// resource.h

	int nMargin = 10; // 공통 여백
	int nButtonWidth = cx / 6; // 버튼 너비
	int nButtonHeight = cy / 20; // 버튼 높이 (조금 더 작게 조정)
	int nInputWidth = cx / 8; // 입력창 너비
	int nLabelHeight = cy / 25; // 입력창 높이 (조금 더 작게 조정)
	int nLabelWidth = cx / 15; // 레이블 너비


	// Title
	GetDlgItem(IDC_STATIC_TITLE)->MoveWindow((cx - 200) / 2, nMargin, 500, 100); // 제목 크기와 위치 조정

	// Start
	int nStartX = cx / 6;
	int nEndX = nStartX + nMargin * 70;

	int nStartY = cy  / 10; // Start와 End의 Y 위치를 가운데로 조정
	GetDlgItem(IDC_STATIC_START)->MoveWindow(nStartX - nMargin, nStartY, nLabelWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_X1)->	  MoveWindow(nStartX + nMargin * 12, nStartY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_X1)->	  MoveWindow(nStartX + nMargin * 12 + nLabelWidth / 3.5, nStartY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_Y1)->	  MoveWindow(nStartX + nMargin * 15 + nLabelWidth / 2 + nInputWidth, nStartY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_Y1)->	  MoveWindow(nStartX + nMargin * 30 + nLabelWidth, nStartY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_BTN_DRAW)->	  MoveWindow(nEndX, nStartY - 5, nButtonWidth, nButtonHeight);

	// End
	int nEndY = nStartY + 50; // Start와 End의 간격 조정
	GetDlgItem(IDC_STATIC_END)->MoveWindow(nStartX - nMargin, nEndY, nLabelWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_X2)-> MoveWindow(nStartX + nMargin * 12, nEndY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_X2)->	MoveWindow(nStartX + nMargin * 12 + nLabelWidth / 3.5, nEndY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_Y2)->	MoveWindow(nStartX + nMargin * 15 + nLabelWidth / 2 + nInputWidth, nEndY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_Y2)->	MoveWindow(nStartX + nMargin * 30 + nLabelWidth, nEndY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_BTN_ACTION)->MoveWindow(nEndX, nEndY, nButtonWidth, nButtonHeight);

	// Bottom Line
	GetDlgItem(IDC_BTN_LOAD_IMG)->MoveWindow(cx / 2 - nButtonWidth - nMargin, cy - nButtonHeight - nMargin, nButtonWidth, nButtonHeight);
	GetDlgItem(IDC_BTN_CLOSE)->MoveWindow(cx / 2 + nMargin, cy - nButtonHeight - nMargin, nButtonWidth, nButtonHeight);
}
