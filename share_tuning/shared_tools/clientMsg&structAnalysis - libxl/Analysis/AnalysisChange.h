#pragma once
#include "libxl.h"
class ClientMsg;
class StructH;
class IllusionExcelFile;
class Analysis
{
public:
	Analysis();
	virtual ~Analysis();

	void AnalysisClientMsg(libxl::Book* book);
	void AnalysisStructMsg(libxl::Book* book);
	void ChangeLanguage(int type);
private:
	ClientMsg *m_pClientMsg;
	StructH *m_pStruct;
	int m_type;
};