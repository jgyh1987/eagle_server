
// ConfigAnalysis.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CConfigAnalysisApp:
// �йش����ʵ�֣������ ConfigAnalysis.cpp
//

class CConfigAnalysisApp : public CWinApp
{
public:
	CConfigAnalysisApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CConfigAnalysisApp theApp;