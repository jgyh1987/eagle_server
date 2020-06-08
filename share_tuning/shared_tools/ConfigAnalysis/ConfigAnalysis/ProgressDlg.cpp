// ProgressDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigAnalysis.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg 对话框

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	int m_iRange = 0;
	int m_iStep = 0;
	m_pProgress = NULL;
}

CProgressDlg::~CProgressDlg()
{
	if (NULL == m_pProgress)
	{
		m_pProgress = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG1);
	}
}
CProgressDlg* CProgressDlg::m_pProgress = NULL;

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Control(pDX, IDC_EDIT1, m_ctrlEditProgress);
}
void CProgressDlg::InitializationProgress(int iRange)
{
	CString strText = _T("");
	m_ctrlProgress.SetRange(0,iRange);
	m_iRange = iRange;
	m_ctrlProgress.SetPos(0);
	strText.Format("0 / %d",iRange);
	m_ctrlEditProgress.SetWindowText(strText);
//	m_pProgress->ShowWindow(SW_SHOW);
}
void CProgressDlg::StepProgress(int iStep)
{
	CString strText = _T("");
	m_ctrlProgress.SetPos(iStep);
	strText.Format("%d / %d",iStep,m_iRange);
	m_ctrlEditProgress.SetWindowText(strText);
}
CProgressDlg* CProgressDlg::CreateInstance()
{
	if (NULL == m_pProgress)
	{
		m_pProgress = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG1);
	}
	return m_pProgress;
}
void CProgressDlg::CloseProgressDlg()
{
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
}
void CProgressDlg::SetTiTleDlg(int iNext, int iTotle, bool bIsFirst)
{
	CString strText = _T("");
	CString strOne = _T("第一阶段");
	CString strTwo = _T("第二阶段");
	if (bIsFirst)
	{
		strText.Format(_T("%s"),strOne);
	}
	else
	{
		strText.Format(_T("%s: %d / %d"),strTwo,iNext,iTotle);
	}
	GetDlgItem(IDC_STATIC_TITLE)->SetWindowText(strText);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
END_MESSAGE_MAP()


// CProgressDlg 消息处理程序
