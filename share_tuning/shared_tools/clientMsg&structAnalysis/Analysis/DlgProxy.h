
// DlgProxy.h: ͷ�ļ�
//

#pragma once

class CAnalysisDlg;


// CAnalysisDlgAutoProxy ����Ŀ��

class CAnalysisDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CAnalysisDlgAutoProxy)

	CAnalysisDlgAutoProxy();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��

// ����
public:
	CAnalysisDlg* m_pDialog;

// ����
public:

// ��д
	public:
	virtual void OnFinalRelease();

// ʵ��
protected:
	virtual ~CAnalysisDlgAutoProxy();

	// ���ɵ���Ϣӳ�亯��

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CAnalysisDlgAutoProxy)

	// ���ɵ� OLE ����ӳ�亯��

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

