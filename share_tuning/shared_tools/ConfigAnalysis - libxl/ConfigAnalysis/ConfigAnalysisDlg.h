
// ConfigAnalysisDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "ProgressBarDlg.h"

class CConfigAnalysisDlgAutoProxy;


// CConfigAnalysisDlg �Ի���
class CConfigAnalysisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigAnalysisDlg);
	friend class CConfigAnalysisDlgAutoProxy;

// ����
public:
	CConfigAnalysisDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CConfigAnalysisDlg();

// �Ի�������
	enum { IDD = IDD_CONFIGANALYSIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
// ʵ��
protected:
	bool b_doing;
	CProgressBarDlg* m_pProgressBar;
	CConfigAnalysisDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnLbnSelchangeList1();
	void SavePath();
	void ReadPath();
	CListBox m_listBox;
	afx_msg void OnBnClickedButton6();
};
