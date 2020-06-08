#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"

// CProgressDlg 对话框

class CProgressDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgressDlg)

public:
	virtual ~CProgressDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };
private:
	CProgressDlg(CWnd* pParent = NULL);   // 标准构造函数
	static CProgressDlg* m_pProgress;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_ctrlProgress;
	CEdit m_ctrlEditProgress;
	int m_iRange;
	int m_iStep;

	void InitializationProgress(int iRange);
	void StepProgress(int iStep);
	CProgressDlg* CreateInstance();
	void CloseProgressDlg();
	void SetTiTleDlg(int iNext, int iTotle, bool bIsFirst);
};
