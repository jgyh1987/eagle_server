
// AnalysisDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Analysis.h"
#include "AnalysisDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"
#include "ClientMsgH.h"
#include "StructH.h"
#include "AnalysisChange.h"
#include "libxl.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString fileDir = "";
CString saveDir = "";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAnalysisDlg 对话框




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
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
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


// CAnalysisDlg 消息处理程序

BOOL CAnalysisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CButton* radio=(CButton*)GetDlgItem(IDC_RADIO1);
	radio->SetCheck(TRUE);
	OnBnClickedRadio1();
	//读取配置文件 文件起始、目的路经
	ReadPath(false);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAnalysisDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAnalysisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

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
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。

	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}



void CAnalysisDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_STATIC)->GetWindowText(fileDir);
	GetDlgItem(IDC_EDIT2)->GetWindowText(saveDir);
	if (fileDir == "")
	{
		AfxMessageBox("请选择配置文件所在目录!");  
		return;
	}
	if (saveDir == "")
	{
		AfxMessageBox("请选择导出文件保存目录!");  
		return;
	}
	if (b_doing)
	{
		AfxMessageBox("正在导出中,请稍候!");
		return;
	}
	//保存路经到配置文件
	SavePath();

	CString fileName;
	fileName.Format("%s/clientMsg.xls", fileDir);
	libxl::Book* book = xlCreateBook();
	if(!book->load(fileName))
	{
		AfxMessageBox("加载文件初始化失败!");
		return;
	}

	b_doing = true;
	g_analy->AnalysisClientMsg(book);
	book->release();
	b_doing = false;

	AfxMessageBox("导出成功!");

	// int nvalue= AfxMessageBox("导出成功!");
	/*if (nvalue == IDOK)
		OnCancel();*/
}

void CAnalysisDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_STATIC)->GetWindowText(fileDir);
	GetDlgItem(IDC_EDIT2)->GetWindowText(saveDir);
	if (fileDir == "")
	{
		AfxMessageBox("请选择配置文件所在目录!");  
		return;
	}
	if (saveDir == "")
	{
		AfxMessageBox("请选择导出文件保存目录!");  
		return;
	}
	if (b_doing)
	{
		AfxMessageBox("正在导出中,请稍候!");
	}
	//保存路经到配置文件
	SavePath();

	CString fileName;
	fileName.Format("%s/struct.xls", fileDir);
	libxl::Book* book = xlCreateBook();
	if(!book->load(fileName))
	{
		AfxMessageBox("加载文件初始化失败!");
		return;
	}

	b_doing = true;

	g_analy->AnalysisStructMsg(book);
	book->release();

	b_doing = false;

	AfxMessageBox("导出成功!");

	// int nvalue= AfxMessageBox("导出成功!");
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
	browseInfo.lpszTitle = "clientMsg和struct所在目录";  
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;  
	browseInfo.lpfn = NULL;  
	browseInfo.lParam = 0;  
	LPITEMIDLIST lpItemIDList;  
	 
	if((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!=NULL)  
	{  
		if(::SHGetPathFromIDList(lpItemIDList, szBuffer))  
		{  
			fileDir = szBuffer;//保存的路径  
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
	browseInfo.lpszTitle = "请选择需要打包的目录";  
	browseInfo.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;  
	browseInfo.lpfn = NULL;  
	browseInfo.lParam = 0;  
	LPITEMIDLIST lpItemIDList;  

	if((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!=NULL)  
	{  
		if(::SHGetPathFromIDList(lpItemIDList, szBuffer))  
		{   
			saveDir = szBuffer;//保存的路径  
			SetDlgItemText(IDC_EDIT2, saveDir);
		}  
		else  
		{  
			AfxMessageBox("Fail to get directory!",MB_ICONSTOP|MB_OK);  
		}  
	} 
}
//保存路经到配置文件
void CAnalysisDlg::SavePath()
{
	CString strPath;
	HMODULE module = GetModuleHandle(0);   
	char buff[MAX_PATH];   
	GetModuleFileName(module, buff, MAX_PATH);    
	//GetCurrentDirectory(_MAX_PATH,buf); //获取当前工作路径
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
//读取配置文件 文件起始、目的路经
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
	delete[] soursePath;
	delete[] savePath;
}


void CAnalysisDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	ReadPath(true);
	g_analy->ChangeLanguage(LANGUAGE_CPP);
}


void CAnalysisDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	ReadPath(true);
	g_analy->ChangeLanguage(LANGUAGE_CS);
}
