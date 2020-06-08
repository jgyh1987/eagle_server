
// DlgProxy.cpp : 实现文件
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
	
	// 为使应用程序在自动化对象处于活动状态时一直保持 
	//	运行，构造函数调用 AfxOleLockApp。
	AfxOleLockApp();

	// 通过应用程序的主窗口指针
	//  来访问对话框。设置代理的内部指针
	//  指向对话框，并设置对话框的后向指针指向
	//  该代理。
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
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CAnalysisDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IAnalysis 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {273DFD09-CC31-4768-8DD6-E61A48FA9916}
static const IID IID_IAnalysis =
{ 0x273DFD09, 0xCC31, 0x4768, { 0x8D, 0xD6, 0xE6, 0x1A, 0x48, 0xFA, 0x99, 0x16 } };

BEGIN_INTERFACE_MAP(CAnalysisDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CAnalysisDlgAutoProxy, IID_IAnalysis, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {6219EA9B-E899-4A4A-9F89-C70C6FCBDCBB}
IMPLEMENT_OLECREATE2(CAnalysisDlgAutoProxy, "Analysis.Application", 0x6219ea9b, 0xe899, 0x4a4a, 0x9f, 0x89, 0xc7, 0xc, 0x6f, 0xcb, 0xdc, 0xbb)


// CAnalysisDlgAutoProxy 消息处理程序
