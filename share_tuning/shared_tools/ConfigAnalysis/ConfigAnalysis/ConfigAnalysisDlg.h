
// ConfigAnalysisDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

class CConfigAnalysisDlgAutoProxy;


// CConfigAnalysisDlg 对话框
class CConfigAnalysisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConfigAnalysisDlg);
	friend class CConfigAnalysisDlgAutoProxy;

// 构造
public:
	CConfigAnalysisDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CConfigAnalysisDlg();

// 对话框数据
	enum { IDD = IDD_CONFIGANALYSIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	bool b_doing;
	CConfigAnalysisDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成的消息映射函数
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
