
// DlgProxy.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigAnalysis.h"
#include "DlgProxy.h"
#include "ConfigAnalysisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConfigAnalysisDlgAutoProxy

IMPLEMENT_DYNCREATE(CConfigAnalysisDlgAutoProxy, CCmdTarget)

CConfigAnalysisDlgAutoProxy::CConfigAnalysisDlgAutoProxy()
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
		ASSERT_KINDOF(CConfigAnalysisDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CConfigAnalysisDlg)))
		{
			m_pDialog = reinterpret_cast<CConfigAnalysisDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CConfigAnalysisDlgAutoProxy::~CConfigAnalysisDlgAutoProxy()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	//  除了做其他事情外，这还将销毁主对话框
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CConfigAnalysisDlgAutoProxy::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CConfigAnalysisDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConfigAnalysisDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// 注意: 我们添加了对 IID_IConfigAnalysis 的支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {599B5B7F-0CD6-485C-B0F3-09F9C07BB47A}
static const IID IID_IConfigAnalysis =
{ 0x599B5B7F, 0xCD6, 0x485C, { 0xB0, 0xF3, 0x9, 0xF9, 0xC0, 0x7B, 0xB4, 0x7A } };

BEGIN_INTERFACE_MAP(CConfigAnalysisDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CConfigAnalysisDlgAutoProxy, IID_IConfigAnalysis, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 宏在此项目的 StdAfx.h 中定义
// {F9E85656-F94A-4D9C-B0A6-7C9ABE833C87}
IMPLEMENT_OLECREATE2(CConfigAnalysisDlgAutoProxy, "ConfigAnalysis.Application", 0xf9e85656, 0xf94a, 0x4d9c, 0xb0, 0xa6, 0x7c, 0x9a, 0xbe, 0x83, 0x3c, 0x87)


// CConfigAnalysisDlgAutoProxy 消息处理程序
