#pragma once

class ClientMsg;
class StructH;
class IllusionExcelFile;
class Analysis
{
public:
	Analysis();
	virtual ~Analysis();

	void AnalysisClientMsg(IllusionExcelFile& excl);
	void AnalysisStructMsg(IllusionExcelFile& excl);
	void ChangeLanguage(int type);
private:
	ClientMsg *m_pClientMsg;
	StructH *m_pStruct;
	int m_type;
};