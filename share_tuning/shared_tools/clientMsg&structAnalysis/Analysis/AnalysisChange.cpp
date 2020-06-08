#include "stdafx.h"
#include "AnalysisChange.h"
#include "ClientMsgH.h"
#include "StructH.h"
#include "IllusionExcelFile.h"
Analysis::Analysis()
{
	m_pClientMsg = NULL;
	m_pStruct =NULL;
	m_type = 0;
}
Analysis::~Analysis()
{
	if(m_pClientMsg)
	{
		delete m_pClientMsg;
		m_pClientMsg = NULL;
	}
	if (m_pStruct)
	{
		delete m_pStruct;
		m_pStruct = NULL;
	}
}

void Analysis::AnalysisClientMsg(IllusionExcelFile& excl)
{
	if (m_pClientMsg)
		m_pClientMsg->AnalysisClientMsg(excl);
}
void Analysis::AnalysisStructMsg(IllusionExcelFile& excl)
{
	if (m_pStruct)
		m_pStruct->AnalysisStructMsg(excl);
}

void Analysis::ChangeLanguage(int type)
{
	switch (type)
	{
	case LANGUAGE_CPP:
		if (LANGUAGE_CPP == m_type)
			break;
		m_type = LANGUAGE_CPP;
		if (m_pClientMsg)
			delete m_pClientMsg;
		if (m_pStruct)
			delete m_pStruct;
		m_pClientMsg = new ClientMsgCPP();
		m_pStruct = new StructHCPP();
		break;
	case LANGUAGE_CS:
		if (LANGUAGE_CS == m_type)
			break;
		m_type = LANGUAGE_CS;
		if (m_pClientMsg)
			delete m_pClientMsg;
		if (m_pStruct)
			delete m_pStruct;
		m_pClientMsg = new ClientMsgCS();
		m_pStruct = new StructHCS();
		break;
	default:
		break;
	}
}
