
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

UINT ThreadAction(LPVOID pParam)
{
	CGrimTaskDlg* pDlg = (CGrimTaskDlg*)pParam;
	if (pDlg == NULL) {
		return 0;
	}

	CString strX2, strY2;
	pDlg->GetDlgItem(IDC_EDIT_X2)->GetWindowText(strX2);
	pDlg->GetDlgItem(IDC_EDIT_Y2)->GetWindowText(strY2);

	int nX1 = pDlg->getGrimCV()->getCoordinate().m_nX1;
	int nY1 = pDlg->getGrimCV()->getCoordinate().m_nY1;
	int nX2 = _ttoi(strX2);
	int nY2 = _ttoi(strY2);

	if (nX1 <= 0 || nY1 <= 0 || nX2 <= 0 || nY2 <= 0 ||
		nX1 >= pDlg->getImageWidth() || nY1 >= pDlg->getImageHeight() ||
		nX2 >= pDlg->getImageWidth() || nY2 >= pDlg->getImageHeight()) {

		CString strSize;
		strSize.Format(_T("%d,%d"), pDlg->getImageWidth(), pDlg->getImageHeight());
		AfxMessageBox(_T("원이 그려진 상태가 아니거나 , 범위 값 : ") + strSize + _T("을 벗어난 값이 입력되었습니다."));
		return 0;
	}
	else if (nX1 == nX2 && nY1 == nY2) {
		AfxMessageBox(_T("두 좌표의 값이 같습니다."));
		return 0;
	}

	// draw
	pDlg->getGrimCV()->setCoordinate(nX1, nY1, nX2, nY2);

	int nPitch = pDlg->getImage().GetPitch();
	unsigned char* fm = (unsigned char*)pDlg->getImage().GetBits();

	BOOL bAction = pDlg->getGrimCV()->Action(fm, nPitch, pDlg->getImageWidth(), pDlg->getImageHeight());

	CString strX1, strY1;
	strX1.Format(_T("%d"), pDlg->getGrimCV()->getCoordinate().m_nX1);
	strY1.Format(_T("%d"), pDlg->getGrimCV()->getCoordinate().m_nY1);

	pDlg->GetDlgItem(IDC_EDIT_X1)->SetWindowText(strX1);
	pDlg->GetDlgItem(IDC_EDIT_Y1)->SetWindowText(strY1);

	// save
	if (bAction) {
		TCHAR chPath[256] = { 0, };
		GetModuleFileName(NULL, chPath, 256);

		CString folderPath(chPath);
		folderPath = folderPath.Left(folderPath.ReverseFind('\\')) + _T("/image");

		if (GetFileAttributes(folderPath) == INVALID_FILE_ATTRIBUTES) {
			if (!CreateDirectory(folderPath, NULL)) {
				AfxMessageBox(_T("폴더 생성 실패!"));
				return 0;
			}
		}

		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);

		CString strFileName;
		strFileName.Format(folderPath + _T("/image_%04d%02d%02d_%02d%02d%02d_%03d.bmp"),
			sysTime.wYear,
			sysTime.wMonth,
			sysTime.wDay,
			sysTime.wHour,
			sysTime.wMinute,
			sysTime.wSecond,
			sysTime.wMilliseconds);

		pDlg->getImage().Save(strFileName);
	}

	// 이미지 갱신 요청
	pDlg->Invalidate(FALSE);

	return 0;
}

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
	ON_BN_CLICKED(IDC_BTN_DRAW, &CGrimTaskDlg::OnBnClickedBtnDraw)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ACTION, &CGrimTaskDlg::OnBnClickedBtnAction)
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
	rect.right = DLG_WIDTH;
	rect.bottom = DLG_HEIGHT;
	MoveWindow(&rect);

	// Font
	m_fontTitle.CreatePointFont(300, _T("Arial"));
	GetDlgItem(IDC_STATIC_TITLE)->SetFont(&m_fontTitle);

	m_fontNormal.CreatePointFont(150, _T("Arial"));
	GetDlgItem(IDC_STATIC_START)->SetFont(&m_fontNormal);
	GetDlgItem(IDC_STATIC_END)->SetFont(&m_fontNormal);

	// image
	m_nImageWidth= rect.right * IMAGE_WIDTH_RATE;
	m_nImageHeight = rect.bottom * IMAGE_HEIGHT_RATE;
	int nBpp = 8;

	m_image.Create(m_nImageWidth, m_nImageHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			fm[j * nPitch + i] = 128;
		}
	}

	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);

	m_grimCV = new C_GrimCV;

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
	CRect rect;
	GetClientRect(&rect);

	
	CPaintDC dc(this); // 클라이언트 영역 그리기용 DC

	// m_image를 그리기
	int nImageX = rect.Width() / 8;
	int nImageY = rect.Height() / 4.5;

	if (!m_image.IsNull()) {
		m_image.Draw(dc, nImageX, nImageY);
	}

	CDialogEx::OnPaint();
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

	int nStartY = cy / 10; // Start와 End의 Y 위치를 가운데로 조정
	GetDlgItem(IDC_STATIC_START)->MoveWindow(nStartX - nMargin, nStartY, nLabelWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_X1)->	  MoveWindow(nStartX + nMargin * 12, nStartY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_X1)->	  MoveWindow(nStartX + nMargin * 12 + nLabelWidth / 3.5, nStartY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_Y1)->	  MoveWindow(nStartX + nMargin * 15 + nLabelWidth / 2 + nInputWidth, nStartY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_Y1)->	  MoveWindow(nStartX + nMargin * 30 + nLabelWidth, nStartY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_BTN_DRAW)->	  MoveWindow(nEndX, nStartY - 5, nButtonWidth, nButtonHeight);

	// End
	int nEndY = nStartY + 50; // Start와 End의 간격 조정
	GetDlgItem(IDC_STATIC_END)->MoveWindow(nStartX - nMargin, nEndY, nLabelWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_X2)->	MoveWindow(nStartX + nMargin * 12, nEndY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_X2)->	MoveWindow(nStartX + nMargin * 12 + nLabelWidth / 3.5, nEndY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_STATIC_Y2)->	MoveWindow(nStartX + nMargin * 15 + nLabelWidth / 2 + nInputWidth, nEndY, nLabelWidth / 2, nLabelHeight);
	GetDlgItem(IDC_EDIT_Y2)->	MoveWindow(nStartX + nMargin * 30 + nLabelWidth, nEndY, nInputWidth, nLabelHeight);
	GetDlgItem(IDC_BTN_ACTION)->MoveWindow(nEndX, nEndY, nButtonWidth, nButtonHeight);

	// Bottom Line
	GetDlgItem(IDC_BTN_LOAD_IMG)->MoveWindow(cx / 2 - nButtonWidth - nMargin, cy - nButtonHeight - nMargin, nButtonWidth, nButtonHeight);
	GetDlgItem(IDC_BTN_CLOSE)->MoveWindow(cx / 2 + nMargin, cy - nButtonHeight - nMargin, nButtonWidth, nButtonHeight);

	// Image
	if (!m_image.IsNull()) {
		m_image.Destroy();

		m_nImageWidth = cx * IMAGE_WIDTH_RATE;
		m_nImageHeight = cy * IMAGE_HEIGHT_RATE;
		int nBpp = 8;

		m_image.Create(m_nImageWidth, m_nImageHeight, nBpp);
		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}

		int nPitch = m_image.GetPitch();
		unsigned char* fm = (unsigned char*)m_image.GetBits();

		for (int j = 0; j < m_nImageHeight; j++) {
			for (int i = 0; i < m_nImageWidth; i++) {
				fm[j * nPitch + i] = COLOR_GRAY;
			}
		}

		Invalidate(TRUE);
	}
}

C_GrimCV* CGrimTaskDlg::getGrimCV()
{
	return m_grimCV;
}

int CGrimTaskDlg::getImageWidth()
{
	return m_nImageWidth;
}

int CGrimTaskDlg::getImageHeight()
{
	return m_nImageHeight;
}

CImage& CGrimTaskDlg::getImage()
{
	return m_image;
}

void CGrimTaskDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strX1;
	CString strY1;

	int nX1 = 0;
	int nY1 = 0;

	GetDlgItem(IDC_EDIT_X1)->GetWindowText(strX1);
	GetDlgItem(IDC_EDIT_Y1)->GetWindowText(strY1);

	nX1 = _ttoi(strX1);
	nY1 = _ttoi(strY1);

	if (nX1 <= 0 || nY1 <= 0 || nX1 >= m_nImageWidth || nY1 >= m_nImageHeight ) {
		CString strSize;
		strSize.Format(_T("%d,%d"), m_nImageWidth, m_nImageHeight);

		AfxMessageBox(_T("값이 0이하이거나 범위 값 : ") + strSize + _T("을 벗어난 값이 입력되었습니다."));
		return;
	}

	// draw
	m_grimCV->setCoordinate(nX1, nY1, 0, 0);

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	for (int j = 0; j < m_nImageHeight; j++) {
		for (int i = 0; i < m_nImageWidth; i++) {
			fm[j * nPitch + i] = COLOR_GRAY;
		}
	}

	BOOL bDraw = m_grimCV->DrawCircle(fm, nPitch, m_nImageWidth, m_nImageHeight);

	if (!bDraw) {
		AfxMessageBox(_T("Failed to Draw Circle"));
		return;
	}

	
	Invalidate(FALSE);
}


void CGrimTaskDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_grimCV;

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CGrimTaskDlg::OnBnClickedBtnAction()
{
	AfxBeginThread(ThreadAction, this);
}