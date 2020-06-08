
// AnalysisDlg.h : 头文件
//

#pragma once

class CAnalysisDlgAutoProxy;

#include "Resource.h"

// CAnalysisDlg 对话框
class CAnalysisDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAnalysisDlg);
	friend class CAnalysisDlgAutoProxy;

// 构造
public:
	CAnalysisDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CAnalysisDlg();

// 对话框数据
	enum { IDD = IDD_ANALYSIS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	bool b_doing;


// 实现
protected:
	CAnalysisDlgAutoProxy* m_pAutoProxy;
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
