
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CConfigAnalysisDlg;


// CConfigAnalysisDlgAutoProxy ����Ŀ��

class CConfigAnalysisDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CConfigAnalysisDlgAutoProxy)

	CConfigAnalysisDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CConfigAnalysisDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CConfigAnalysisDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CConfigAnalysisDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

