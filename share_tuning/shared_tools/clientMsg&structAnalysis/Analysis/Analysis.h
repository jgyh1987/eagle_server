
// Analysis.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAnalysisApp:
// �йش����ʵ�֣������ Analysis.cpp
//

class CAnalysisApp : public CWinApp
{
public:
	CAnalysisApp();

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAnalysisApp theApp;