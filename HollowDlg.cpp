// HollowDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Hollow.h"
#include "HollowDlg.h"
#include "../common/converter.h"
#include "../common/finder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원

// 구현
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHollowDlg 대화 상자



CHollowDlg::CHollowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHollowDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHollowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHollowDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CHollowDlg 메시지 처리기

BOOL CHollowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	return TRUE;  // 컨트롤에 대한 포커스를 설정하지 않을 경우 TRUE를 반환합니다.
}

void CHollowDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 
// 아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
// 프레임워크에서 이 작업을 자동으로 수행합니다.

void CHollowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다. 
HCURSOR CHollowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHollowDlg::OnBnClickedButton1()
{


	CFileDialog m_IdFile(TRUE,"txt",NULL,NULL ,"EngMasterFile (*.xml)|*.xml|아스키 텍스트 (*.txt)|*.txt||");
	
	if(m_IdFile.DoModal() != IDOK)
		return;

	CString sFillTheBlank;
	sFillTheBlank.Format("%s\n<PAGEEND></PAGEEND>\n%s\n<PAGEEND></PAGEEND>\n%s\n<PAGEEND></PAGEEND>\n%s\n<PAGEEND></PAGEEND>"
		,Blanker(m_IdFile.GetPathName(),3)
		,Blanker(m_IdFile.GetPathName(),0)
		,Blanker(m_IdFile.GetPathName(),1)
		,Blanker(m_IdFile.GetPathName(),2)
		);

	CString SavePath;
	CString sFolderPath;

	sFolderPath = m_IdFile.GetPathName().Left(m_IdFile.GetPathName().GetLength()-m_IdFile.GetFileName().GetLength());



	SavePath.Format("%s%s_[빈칸문제].xml",sFolderPath,m_IdFile.GetFileTitle());

	CConverter cv;
	cv.CVT_CStringToFile(sFillTheBlank,SavePath);
}

//------------------------------------------------------------------------------
// 다섯번째의 단어마다 빈칸을 만들어주는 함수이다.
// SourceFilePath	: 입력 파일의 경로
// nBlankEveryN		: 몇 칸에서 부터 세번째 단어를 비울 것인지 확인한다. (0~2)
//------------------------------------------------------------------------------
CString CHollowDlg::Blanker(CString SourceFilePath, int nBlankEveryN)
{
	int NUM = 0;
	CConverter cv;
	CStringArray tA, wordResult, senResult;
	CString sReturnValue;

	CFinder fd;

	cv.CVT_FileToArray(tA, SourceFilePath);
	for(int i = 0  ; i < tA.GetCount() ; i++)
	{
		CString t;

		t = tA.GetAt(i);
		t.Replace("“","\"");

		CStringArray sA;
//		cv.CVT_SentenceToWordArray(sA, t);
		cv.CVT_ParagraphToWord_T_R_Array(sA, t);

		CString sSenResult;
		for(int j = 0 ; j < sA.GetCount() ; j++)
		{
			CString w;
			w = sA.GetAt(j);



			//2byte문자가 있으면 빼는 부분
			if(fd.Is2ByteWord(w))
			{
				sSenResult += w;
				sSenResult += " ";
			}
			else if((w.Find("<") == -1) && (w.Find("<") == -1) && (w.Find("그림입력") == -1)  && (NUM % 3 == nBlankEveryN))
			{
				CString w1;
				w1 = w.Left(1);

				sSenResult += w1;

				for(int k = 0; k< w.GetLength()-1 ; k++)
				{

					if(fd.IsAlpha(w.Mid(k+1,1)))
						sSenResult += "□";
					else
						sSenResult += w.Mid(k+1,1);
					
				}
				sSenResult += " ";
			}
			else
			{
				sSenResult += w;
				sSenResult += " ";
			}
			NUM++;
		}
		sSenResult = sSenResult.Left(sSenResult.GetLength() - 1); // 맨끝의 빈칸 뗌
		senResult.Add(sSenResult);
	}
	sReturnValue = cv.CVT_ArrayToCString(senResult);

	return sReturnValue;
}
