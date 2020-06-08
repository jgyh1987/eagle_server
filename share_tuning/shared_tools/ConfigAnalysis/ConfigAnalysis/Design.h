#pragma once
#include "stdafx.h"
#include "IllusionExcelFile.h"
#include "ProgressDlg.h"
class CConfigAnalysisDlg;
struct PropertyBase
{
	CString name;
	CString type;
	CString detail;
	CString typeDetail;
	int count;
	vector<int> vecIndex;

	PropertyBase()
	{
		name = "";
		type = "";
		detail = "";
		typeDetail = "";
		count = 0;
		vecIndex.clear();
	}

	void Clear()
	{
		name = "";
		type = "";
		detail = "";
		typeDetail = "";
		count = 0;
		vecIndex.clear();
	}

	void SetType(CString _type)
	{
		if (_type == "string")
			type = "std::string";
		else if (_type == "int8")
			type = "char";
		else if (_type == "uint8")
			type = "BYTE";
		else if (_type == "uint16")
			type = "uint16_t";
		else if (_type == "uint32")
			type = "uint32_t";
		else if (_type == "int32")
			type = "int32_t";
		else if (_type == "uint64")
			type = "uint64_t";
		else if (_type == "vector")
			type = "std::vector";
		else if (_type == "double")
			type = "double";
		else
			type = "Struct::" + _type;
		typeDetail = type;
	}

	void SetDetail(CString _detail)
	{
		if (type != "std::vector")
			return;

		if (_detail == "string")
			detail = "std::string";
		else if (_detail == "int8")
			detail = "char";
		else if (_detail == "uint8")
			_detail = "BYTE";
		else if (_detail == "uint16")
			detail = "uint16_t";
		else if (_detail == "uint32")
			detail = "uint32_t";
		else if (_detail == "int32")
			detail = "int32_t";
		else if (_detail == "uint64")
			detail = "uint64_t";
		else if (_detail == "double")
			detail = "double";
		else
			detail = "Struct::" + _detail;

		typeDetail = type + "< " + detail + " >";
	}

	void AddVecIndex(int _index)
	{
		++count;
		vecIndex.push_back(_index);
	}

	bool Islegal() {return name != "";}
};

struct ConfigBase
{
	string key;
	int majorCmd;

	ConfigBase()
	{
		key = "";
		majorCmd = 0;
	}
};

class Design
{
private:
	vector<PropertyBase> ClassProperty;
	bool _messageFlag;
	bool _nameFlag;
	int _structEndFlag;
	bool _propertyFlag;
	PropertyBase nowProperty;
	CString name;
	ofstream ofile;				//.h
	ofstream ofilecpp;          //.cpp
	CString strSheetName;
	bool b_keyFlag;
	map< CString, vector<PropertyBase> > m_configUse;
	vector<int> vecIndex;
public:
	bool m_bIsAllExport;
	CProgressDlg *m_pProgress;
public:
	Design();
	virtual ~Design();


	void AnalysisDesign(IllusionExcelFile& excl);
	void DealMsgItem();
	void BeginDesignH();
	void EndDesignH();
	void BeginDesignCpp();
	void EndDesignCpp();

	void GenType(CString _type, CString _value);
	int GetPropertyLength(CString _type, CString _value, CString _detail = "");
	void AnalysisAllConfigExcel(IllusionExcelFile& excl, CListBox& _listBox);
	void AnalysisOneConfigExcel(IllusionExcelFile& excl, CString _name);
	void AnalysisConfigExcel(IllusionExcelFile& excl, CString name, vector<PropertyBase>& useProperty);
	void testFunc();

	void AnalysisOneConfig(IllusionExcelFile& excl, CString _name);
	void LineFeed(CListBox& _listBox,CString strText);
};