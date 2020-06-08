#pragma once
#include "afxcmn.h"
#include "resource.h"

// CProgressBarDlg 对话框

class CProgressBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressBarDlg)

public:
	CProgressBarDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgressBarDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void InitializationProgress(int iRange);
	void StepProgress(int iStep);
	CProgressBarDlg* Instance();
	void CloseProgressDlg();
	void SetTiTleDlg(int iNext, int iTotle, bool bIsFirst);

private:
	CProgressBarDlg* m_pProgress;
	int m_iRange;
	int m_iStep;
	CProgressCtrl m_ctrlProgress;
};
