#pragma once
#include "afxcmn.h"
#include "resource.h"

// CProgressBarDlg �Ի���

class CProgressBarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgressBarDlg)

public:
	CProgressBarDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgressBarDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
