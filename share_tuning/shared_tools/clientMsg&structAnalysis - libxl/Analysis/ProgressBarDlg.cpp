// ProgressBarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Analysis.h"
#include "ProgressBarDlg.h"
#include "afxdialogex.h"


// CProgressBarDlg 对话框

IMPLEMENT_DYNAMIC(CProgressBarDlg, CDialog)

CProgressBarDlg* CProgressBarDlg::m_pProgress = NULL;

CProgressBarDlg::CProgressBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressBarDlg::IDD, pParent)
{
	m_iRange = 0;
	m_iStep = 0;
}

CProgressBarDlg::~CProgressBarDlg()
{
}

void CProgressBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
}

void CProgressBarDlg::InitializationProgress(int iRange)
{
	CString strText = _T("");
	m_ctrlProgress.SetRange(1,iRange);
	m_iRange = iRange;
	m_ctrlProgress.SetPos(1);
	strText.Format("1 / %d",iRange);
	GetDlgItem(IDC_STATIC_CONTENT)->SetWindowText(strText);
	GetDlgItem(IDC_STATIC_TIP)->SetWindowText(_T("进度："));
}
void CProgressBarDlg::StepProgress(int iStep)
{
	CString strText = _T("");
	m_ctrlProgress.SetPos(iStep);
	strText.Format("%d / %d",iStep,m_iRange);
	GetDlgItem(IDC_STATIC_CONTENT)->SetWindowText(strText);
}
CProgressBarDlg* CProgressBarDlg::Instance()
{
	if (NULL == m_pProgress)
	{
		m_pProgress = new CProgressBarDlg();
		m_pProgress->Create(IDD_DIALOG_PROGRESSBAR);
	}
	return m_pProgress;
}
void CProgressBarDlg::CloseProgressDlg()
{
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
}

BEGIN_MESSAGE_MAP(CProgressBarDlg, CDialog)
END_MESSAGE_MAP()


// CProgressBarDlg 消息处理程序
