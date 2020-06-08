#pragma once
#include "afxcmn.h"
#include "resource.h"

// CProgressBarDlg 对话框

class CProgressBarDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgressBarDlg)

public:
	virtual ~CProgressBarDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROGRESSBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CProgressBarDlg(CWnd* pParent = NULL);   // 标准构造函数
	DECLARE_MESSAGE_MAP()
public:
	void InitializationProgress(int iRange);
	void StepProgress(int iStep);
	static CProgressBarDlg* Instance();
	void CloseProgressDlg();

private:
	static CProgressBarDlg* m_pProgress;
	int m_iRange;
	int m_iStep;
	CProgressCtrl m_ctrlProgress;
};
