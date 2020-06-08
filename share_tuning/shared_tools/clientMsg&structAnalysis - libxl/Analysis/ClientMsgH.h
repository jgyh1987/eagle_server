#pragma once

#include "stdafx.h"
#include "StructH.h"
#include "ProgressBarDlg.h"

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
	CProgressBarDlg *m_pProgress;
public:
	ClientMsg();
	virtual ~ClientMsg() {};

	virtual void AnalysisClientMsg(libxl::Book* book) = 0;
	std::string valueToString(double value);
	double Round(double value);
};

class ClientMsgCPP : public ClientMsg
{
public:
	ClientMsgCPP();
	~ClientMsgCPP() {};

	virtual void AnalysisClientMsg(libxl::Book* book);
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

	virtual void AnalysisClientMsg(libxl::Book* book);
	void BeginClientCSharpMsg();
	void EndClientCSharpMsg();
	void DealCSharpMsgItem();
};



enum LANGUAGE
{
	LANGUAGE_CPP = 1,
	LANGUAGE_CS = 2,
};

