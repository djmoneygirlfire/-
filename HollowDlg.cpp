// HollowDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Hollow.h"
#include "HollowDlg.h"
#include "../common/converter.h"
#include "../common/finder.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

// ����
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


// CHollowDlg ��ȭ ����



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


// CHollowDlg �޽��� ó����

BOOL CHollowDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHollowDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CHollowDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHollowDlg::OnBnClickedButton1()
{


	CFileDialog m_IdFile(TRUE,"txt",NULL,NULL ,"EngMasterFile (*.xml)|*.xml|�ƽ�Ű �ؽ�Ʈ (*.txt)|*.txt||");
	
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



	SavePath.Format("%s%s_[��ĭ����].xml",sFolderPath,m_IdFile.GetFileTitle());

	CConverter cv;
	cv.CVT_CStringToFile(sFillTheBlank,SavePath);
}

//------------------------------------------------------------------------------
// �ټ���°�� �ܾ�� ��ĭ�� ������ִ� �Լ��̴�.
// SourceFilePath	: �Է� ������ ���
// nBlankEveryN		: �� ĭ���� ���� ����° �ܾ ��� ������ Ȯ���Ѵ�. (0~2)
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
		t.Replace("��","\"");

		CStringArray sA;
//		cv.CVT_SentenceToWordArray(sA, t);
		cv.CVT_ParagraphToWord_T_R_Array(sA, t);

		CString sSenResult;
		for(int j = 0 ; j < sA.GetCount() ; j++)
		{
			CString w;
			w = sA.GetAt(j);



			//2byte���ڰ� ������ ���� �κ�
			if(fd.Is2ByteWord(w))
			{
				sSenResult += w;
				sSenResult += " ";
			}
			else if((w.Find("<") == -1) && (w.Find("<") == -1) && (w.Find("�׸��Է�") == -1)  && (NUM % 3 == nBlankEveryN))
			{
				CString w1;
				w1 = w.Left(1);

				sSenResult += w1;

				for(int k = 0; k< w.GetLength()-1 ; k++)
				{

					if(fd.IsAlpha(w.Mid(k+1,1)))
						sSenResult += "��";
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
		sSenResult = sSenResult.Left(sSenResult.GetLength() - 1); // �ǳ��� ��ĭ ��
		senResult.Add(sSenResult);
	}
	sReturnValue = cv.CVT_ArrayToCString(senResult);

	return sReturnValue;
}
