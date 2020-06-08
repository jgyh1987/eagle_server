
// AnalysisDlg.h : ͷ�ļ�
//

#pragma once

class CAnalysisDlgAutoProxy;

#include "Resource.h"

// CAnalysisDlg �Ի���
class CAnalysisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalysisDlg);
	friend class CAnalysisDlgAutoProxy;

// ����
public:
	CAnalysisDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CAnalysisDlg();

// �Ի�������
	enum { IDD = IDD_ANALYSIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	bool b_doing;


// ʵ��
protected:
	CAnalysisDlgAutoProxy* m_pAutoProxy;
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
	void SavePath();
	void ReadPath(bool bIsChangeRadio);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
