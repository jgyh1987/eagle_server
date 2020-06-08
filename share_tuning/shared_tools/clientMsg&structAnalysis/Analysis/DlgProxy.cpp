
// DlgProxy.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Analysis.h"
#include "DlgProxy.h"
#include "AnalysisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnalysisDlgAutoProxy

IMPLEMENT_DYNCREATE(CAnalysisDlgAutoProxy, CCmdTarget)

CAnalysisDlgAutoProxy::CAnalysisDlgAutoProxy()
{
	EnableAutomation();
	
	// ΪʹӦ�ó������Զ��������ڻ״̬ʱһֱ���� 
	//	���У����캯������ AfxOleLockApp��
	AfxOleLockApp();

	// ͨ��Ӧ�ó����������ָ��
	//  �����ʶԻ������ô�����ڲ�ָ��
	//  ָ��Ի��򣬲����öԻ���ĺ���ָ��ָ��
	//  �ô���
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CAnalysisDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CAnalysisDlg)))
		{
			m_pDialog = reinterpret_cast<CAnalysisDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CAnalysisDlgAutoProxy::~CAnalysisDlgAutoProxy()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	//  ���������������⣬�⻹���������Ի���
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAnalysisDlgAutoProxy::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IAnalysis ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {273DFD09-CC31-4768-8DD6-E61A48FA9916}
static const IID IID_IAnalysis =
{ 0x273DFD09, 0xCC31, 0x4768, { 0x8D, 0xD6, 0xE6, 0x1A, 0x48, 0xFA, 0x99, 0x16 } };

BEGIN_INTERFACE_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAnalysisDlgAutoProxy, IID_IAnalysis, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 ���ڴ���Ŀ�� StdAfx.h �ж���
// {6219EA9B-E899-4A4A-9F89-C70C6FCBDCBB}
IMPLEMENT_OLECREATE2(CAnalysisDlgAutoProxy, "Analysis.Application", 0x6219ea9b, 0xe899, 0x4a4a, 0x9f, 0x89, 0xc7, 0xc, 0x6f, 0xcb, 0xdc, 0xbb)


// CAnalysisDlgAutoProxy ��Ϣ�������
