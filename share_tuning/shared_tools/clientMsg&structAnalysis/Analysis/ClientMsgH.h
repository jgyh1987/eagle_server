#pragma once

#include "stdafx.h"
#include "IllusionExcelFile.h"
#include "StructH.h"
#include "ProgressDlg.h"
class ClientMsg
{
protected:
	std::vector<MessageBase> Message;
	std::vector<PropertyBase> ClassProperty;
	std::vector<CommandBase> CommandMsg;
	bool _messageFlag;
	bool _nameFlag;
	int _structEndFlag;
	bool _propertyFlag;
	int _majorCmdFlag;
	int _minorCmdFlag;
	PropertyBase nowProperty;
	CString name;
	MessageBase nowMessage;
	ofstream ofile;				//.h
	ofstream ofilecpp;          //.cpp
	CString strSheetName;
	CProgressDlg *m_pProgress;
public:
	ClientMsg();
	virtual ~ClientMsg() {};

	virtual void AnalysisClientMsg(IllusionExcelFile& excl) = 0;
};

class ClientMsgCPP : public ClientMsg
{
public:
	ClientMsgCPP();
	~ClientMsgCPP() {};

	virtual void AnalysisClientMsg(IllusionExcelFile& excl);
	void BeginClientMsgH();
	void EndClientMsgH();
	void BeginClientMsgCpp();
	void EndClientMsgCpp();
	void DealMsgItem();
};

class ClientMsgCS : public ClientMsg
{
public:
	ClientMsgCS();
	virtual ~ClientMsgCS() {};

	virtual void AnalysisClientMsg(IllusionExcelFile& excl);
	void BeginClientCSharpMsg();
	void EndClientCSharpMsg();
	void DealCSharpMsgItem();
};

enum LANGUAGE
{
	LANGUAGE_CPP = 1,
	LANGUAGE_CS = 2,
};

