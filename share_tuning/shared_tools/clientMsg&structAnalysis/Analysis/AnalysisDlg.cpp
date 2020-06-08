
// AnalysisDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Analysis.h"
#include "AnalysisDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "IllusionExcelFile.h"
#include "ClientMsgH.h"
#include "StructH.h"
#include "AnalysisChange.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString fileDir = "";
CString saveDir = "";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAnalysisDlg �Ի���




IMPLEMENT_DYNAMIC(CAnalysisDlg, CDialogEx);

CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAnalysisDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
	b_doing = false;
}

CAnalysisDlg::~CAnalysisDlg()
{
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAnalysisDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnalysisDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAnalysisDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnalysisDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_RADIO1, &CAnalysisDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CAnalysisDlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CAnalysisDlg ��Ϣ�������

BOOL CAnalysisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO1);
	radio->SetCheck(TRUE);
	//��ȡ�����ļ� �ļ���ʼ��Ŀ��·��
	ReadPath(false);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CAnalysisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAnalysisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

void CAnalysisDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CAnalysisDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CAnalysisDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CAnalysisDlg::CanExit()
{
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������

	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CAnalysisDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_STATIC)->GetWindowText(fileDir);
	GetDlgItem(IDC_EDIT2)->GetWindowText(saveDir);
	if (fileDir == "")
	{
		AfxMessageBox("��ѡ�������ļ�����Ŀ¼!");  
		return;
	}
	if (saveDir == "")
	{
		AfxMessageBox("��ѡ�񵼳��ļ�����Ŀ¼!");  
		return;
	}
	if (b_doing)
	{
		AfxMessageBox("���ڵ�����,���Ժ�!");
		return;
	}
	//����·���������ļ�
	SavePath();
	IllusionExcelFile excl;
	bool bInit = excl.InitExcel();	
	if (!bInit)
	{
		AfxMessageBox("��ȡ�����ļ���ʼ��ʧ��!");
		return;
	}

	CString fileName;
	fileName.Format("%s/clientMsg.xls", fileDir);
	bool bRet = excl.OpenExcelFile(fileName);
	b_doing = true;

	BOOL bCplusplus =  IsDlgButtonChecked(IDC_RADIO1);
	Analysis analy;
	if (bCplusplus)
	{
		analy.ChangeLanguage(LANGUAGE_CPP);
	}
	else
	{
		analy.ChangeLanguage(LANGUAGE_CS);
	}
	analy.AnalysisClientMsg(excl);
	excl.CloseExcelFile();
	excl.ReleaseExcel();

	b_doing = false;

	int nvalue= AfxMessageBox("�����ɹ�!");
	/*if (nvalue == IDOK)
		OnCancel();*/
}

void CAnalysisDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_STATIC)->GetWindowText(fileDir);
	GetDlgItem(IDC_EDIT2)->GetWindowText(saveDir);
	if (fileDir == "")
	{
		AfxMessageBox("��ѡ�������ļ�����Ŀ¼!");  
		return;
	}
	if (saveDir == "")
	{
		AfxMessageBox("��ѡ�񵼳��ļ�����Ŀ¼!");  
		return;
	}
	if (b_doing)
	{
		AfxMessageBox("���ڵ�����,���Ժ�!");
	}
	//����·���������ļ�
	SavePath();

	IllusionExcelFile excl;
	bool bInit = excl.InitExcel();	
	if (!bInit)
	{
		AfxMessageBox("��ȡ�����ļ���ʼ��ʧ��!");
		return;
	}
	
	CString fileName;
	fileName.Format("%s/struct.xls", fileDir);
	bool bRet = excl.OpenExcelFile(fileName);
	b_doing = true;
	g_analy->AnalysisStructMsg(excl);
	excl.CloseExcelFile();
	excl.ReleaseExcel();

	b_doing = false;

	int nvalue= AfxMessageBox("�����ɹ�!");
	/*if (nvalue == IDOK)
		OnCancel();*/
}

void CAnalysisDlg::OnBnClickedButton1()
{  
	char szBuffer[_MAX_PATH] = {0};  
	BROWSEINFO browseInfo;  
	browseInfo.hwndOwner = this->m_hWnd;  
	browseInfo.pidlRoot = NULL;  
	browseInfo.pszDisplayName = NULL;  
	browseInfo.lpszTitle = "clientMsg��struct����Ŀ¼";  
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;  
	browseInfo.lpfn = NULL;  
	browseInfo.lParam = 0;  
	LPITEMIDLIST lpItemIDList;  
	 
	if((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!=NULL)  
	{  
		if(::SHGetPathFromIDList(lpItemIDList, szBuffer))  
		{  
			fileDir = szBuffer;//�����·��  
			SetDlgItemText(IDC_STATIC, fileDir); 
		}  
		else  
		{  
			AfxMessageBox("Fail to get directory!",MB_ICONSTOP|MB_OK);  
		}  
	} 
}


void CAnalysisDlg::OnBnClickedButton2()
{
	char szBuffer[_MAX_PATH] = {0};  
	BROWSEINFO browseInfo;  
	browseInfo.hwndOwner = this->m_hWnd;  
	browseInfo.pidlRoot = NULL;  
	browseInfo.pszDisplayName = NULL;  
	browseInfo.lpszTitle = "��ѡ����Ҫ�����Ŀ¼";  
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;  
	browseInfo.lpfn = NULL;  
	browseInfo.lParam = 0;  
	LPITEMIDLIST lpItemIDList;  

	if((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!=NULL)  
	{  
		if(::SHGetPathFromIDList(lpItemIDList, szBuffer))  
		{   
			saveDir = szBuffer;//�����·��  
			SetDlgItemText(IDC_EDIT2, saveDir);
		}  
		else  
		{  
			AfxMessageBox("Fail to get directory!",MB_ICONSTOP|MB_OK);  
		}  
	} 
}
//����·���������ļ�
void CAnalysisDlg::SavePath()
{
	CString strPath;
	HMODULE module = GetModuleHandle(0);   
	char buff[MAX_PATH];   
	GetModuleFileName(module, buff, MAX_PATH);    
	//GetCurrentDirectory(_MAX_PATH,buf); //��ȡ��ǰ����·��
	*(strrchr(buff,'\\') + 1) = '\0';
	BOOL bCplusplus =  IsDlgButtonChecked(IDC_RADIO1);
	if (bCplusplus)
	{
		strPath.Format("%sIniPathCPP.ini",buff);
	}
	else
	{
		strPath.Format("%sIniPathCS.ini",buff);
	}
	
	if (!fileDir.IsEmpty())
	{
		WritePrivateProfileString("SourcePath", "Path", fileDir, strPath);
	}
	else
	{
		WritePrivateProfileString("SourcePath", "Path", "", strPath);
	}
	if (!saveDir.IsEmpty())
	{
		WritePrivateProfileString("SavePath", "Path", saveDir, strPath);	
	}
	else
	{
		WritePrivateProfileString("SavePath", "Path", "", strPath);	
	}
}
//��ȡ�����ļ� �ļ���ʼ��Ŀ��·��
void CAnalysisDlg::ReadPath(bool bIsChangeRadio)
{
	HMODULE module = GetModuleHandle(0);   
	char buff[MAX_PATH];   
	GetModuleFileName(module, buff, MAX_PATH);  
	//GetCurrentDirectory(_MAX_PATH,buf);
	*(strrchr(buff,'\\') + 1) = '\0';
	CString strPath = _T("");
	BOOL bCplusplus =  IsDlgButtonChecked(IDC_RADIO1);
	if (bCplusplus)
	{
		strPath.Format(_T("%s\\IniPathCPP.ini"),buff);
	}
	else
	{
		strPath.Format(_T("%s\\IniPathCS.ini"),buff);
	}
	LPTSTR soursePath = new char[_MAX_PATH];
	LPTSTR savePath = new char[_MAX_PATH];
	if (!bIsChangeRadio)
	{
		GetPrivateProfileString("SourcePath", "Path", "", soursePath, _MAX_PATH, strPath);
		GetDlgItem(IDC_STATIC)->SetWindowText(soursePath);
		GetDlgItem(IDC_STATIC)->GetWindowText(fileDir);
	}
	GetPrivateProfileString("SavePath", "Path", "", savePath, _MAX_PATH, strPath);
	GetDlgItem(IDC_EDIT2)->SetWindowText(savePath);	
	GetDlgItem(IDC_EDIT2)->GetWindowText(saveDir);
}


void CAnalysisDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ReadPath(true);
	g_analy->ChangeLanguage(LANGUAGE_CPP);
}


void CAnalysisDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ReadPath(true);
	g_analy->ChangeLanguage(LANGUAGE_CS);
}
