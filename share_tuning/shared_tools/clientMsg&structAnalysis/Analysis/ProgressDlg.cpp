// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Analysis.h"
#include "ProgressDlg.h"
#include "afxdialogex.h"


// CProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
	, m_strText(_T(""))
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctrlProgress);
	DDX_Text(pDX, IDC_EDIT1, m_strText);
	DDX_Control(pDX, IDC_EDIT1, m_ctrEdit);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������


BOOL CProgressDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
