#pragma once
#include "stdafx.h"
#include "ProgressBarDlg.h"
#include "libxl.h"
struct MessageBase
{
	string name;
	int majorCmd;

	MessageBase()
	{
		name = "";
		majorCmd = 0;
	}
};
struct CommandBase
{
	CString name;
	CString sheetName;
	int minorCmd;

	CommandBase()
	{
		name = "";
		sheetName = "";
		minorCmd = 0;
	}
};
struct PropertyBase
{
	CString name;
	CString type;
	CString detail;
	CString typeDetail;

	PropertyBase();
	void Clear();
	void SetType(CString _type);
	void SetCSharpType(CString _type);
	void SetDetail(CString _detail);
	void SetCSharpDetail(CString _detail);
};

class StructH{
protected:
	std::vector<MessageBase> Message;
	std::vector<PropertyBase> ClassProperty;
	bool _messageFlag;
	bool _nameFlag;
	int _structEndFlag;
	bool _propertyFlag;
	PropertyBase nowProperty;
	CString name;
	MessageBase nowMessage;
	ofstream ofile;				//.h
	ofstream ofilecpp;          //.cpp
	CString strSheetName;
	std::vector<CString> names;
	std::vector<CString> writes;
	CProgressBarDlg *m_pProgress;
public:
	StructH();
	virtual ~StructH() {};
	virtual void AnalysisStructMsg(libxl::Book* book) = 0;
	std::string StructvalueToString(double value);
	double Round(double value);
};
class StructHCPP : public StructH
{
public:
	StructHCPP() {};
	virtual ~StructHCPP() {};
	virtual void AnalysisStructMsg(libxl::Book* book);
	void DealMsgItem();
	void BeginStructH();
	void EndStructH();
	void BeginStructCpp();
	void EndStructCpp();
};
class StructHCS : public StructH
{
public:
	StructHCS()	{};
	virtual ~StructHCS() {};
	virtual void AnalysisStructMsg(libxl::Book* book);
	void BeginStructCSharpMsg();
	void EndStructCSharpMsg();
	void DealCSharpMsgItem();
};
