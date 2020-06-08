#include "stdafx.h"
#include "Design.h"

extern CString fileDir;
extern CString saveDir;

Design::Design()
{
	ClassProperty.clear();
	_messageFlag = false;
	_nameFlag = false;
	_structEndFlag = 0;
	_propertyFlag = false;
	name = "";
	strSheetName = "";
	b_keyFlag = false;
	m_bIsAllExport = false;
	m_bBeginProgress = false;
	vecIndex.clear();
}
Design::~Design()
{
}

void Design::AnalysisDesign(libxl::Book* book,CProgressBarDlg* pBar)
{
	CString fileName;
	fileName.Format("%s/design.xls", fileDir);

	CString url;
	url.Format("%s/Design.h",saveDir);
	ofile.open(url); 

	url.Format("%s/Design.cpp",saveDir);
	ofilecpp.open(url);

	BeginDesignH();
	BeginDesignCpp();

	if(!book->load(fileName))
	{
		AfxMessageBox("加载文件初始化失败!");
		return;
	}

	libxl::Sheet* sheet = book->getSheet(2);
	int nRow = sheet->lastRow();
	int nCol = sheet->lastCol();
	strSheetName = sheet->name();

	CString strText = _T("");

	m_bBeginProgress = true;
	CString strValue;
	double iNum = 0;
	for (int i=0; i< nRow; ++i)
	{	
		InitializationBar(nRow-1, i, pBar);
		for (int j=0; j< nCol; ++j)
		{
			switch (sheet->cellType(i, j))
			{
			case libxl::CELLTYPE_NUMBER:
				iNum = sheet->readNum(i, j);
				iNum = Round(iNum);
				strValue = valueToString(iNum).c_str();
				break;
			case libxl::CELLTYPE_STRING:
				strValue = sheet->readStr(i, j);
				break;
			default:
				strValue = "";
				break;
			}
			if (strValue == "")
			{
				if (j == 1)
				{
					if (_structEndFlag == 1)
						_structEndFlag = 2;
					break;
				}					
			}
			else
			{
				if (j == 0)
				{
					if (strValue == "name")
					{
						_nameFlag = true;
						_structEndFlag = 1;
					}
					else if (strValue == "property")
					{
						_propertyFlag = true;
						nowProperty.Clear();
					}
					else if (strValue == "pk")
					{
						b_keyFlag = true;
					}
				}
				else
				{
					if (_nameFlag)
					{
						name = strValue;
						ofile<<"struct "<<name<<" : public Streamable"<<endl;
						ofile<<"{"<<endl;
						_nameFlag = false;
						break;
					}
					else if (_propertyFlag)
					{
						if (j == 1)
							nowProperty.name = strValue;
						else if (j == 2)
							nowProperty.SetType(strValue);
						else if (j == 3)
							nowProperty.SetDetail(strValue);
						else if (j == 6 && strValue == "c")
						{
							ofile<<"	"<<nowProperty.typeDetail<<" "<<nowProperty.name<<";"<<endl;
							ClassProperty.push_back(nowProperty);
							break;
						}
					}
					else if (b_keyFlag)
					{
						_structEndFlag = 2;
						break;
					}
				}				
			}	
		}

		if (_structEndFlag == 2)
		{
			DealMsgItem();
		}
	}
	DealMsgItem();

	EndDesignH();
	EndDesignCpp();

	ofile.close();
	ofilecpp.close();                //关闭文件
}

void Design::InitializationBar(int iRow, int i, CProgressBarDlg* pBar)
{
	if (!m_bIsAllExport)
	{
		if (m_bBeginProgress)
		{
			pBar->InitializationProgress(iRow);
			m_bBeginProgress = false;
			return;
		}
		else
		{
			pBar->StepProgress(i);
			return;
		}
	}
	if (m_bIsAllExport && m_bBeginProgress)
	{
		pBar->InitializationProgress(iRow);
		pBar->SetTiTleDlg(0,0,true);
		m_bBeginProgress = false;
	}
	else
	{
		pBar->StepProgress(i);
	}
}

void Design::DealMsgItem()
{
	ofile<<endl<<"	"<<name<<"();"<<endl<<endl;
	ofile<<"	virtual int Serialize(WriteStream *) const;"<<endl;
	ofile<<"	virtual int Unserialize(ReadStream *);"<<endl;
	ofile<<"};"<<endl<<endl;

	/************************构造函数************************/
	ofilecpp<<name<<"::"<<name<<"()"<<endl;
	ofilecpp<<"{"<<endl;
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE" || _compare == "uint32_t" || _compare == "uint64_t" || _compare == "double" || _compare == "uint16_t" || _compare == "char" || _compare == "int32_t")
			ofilecpp<<"	"<<ClassProperty[l].name<<" = 0;"<<endl;
	}
	ofilecpp<<"}"<<endl<<endl;
	/************************构造函数************************/

	/************************序列化函数************************/
	ofilecpp<<"int "<<name<<"::Serialize(WriteStream * writeStream) const"<<endl;
	ofilecpp<<"{"<<endl;
	ofilecpp<<"	(void)writeStream;"<<endl;
	
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		ofilecpp<<"	{"<<endl;
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE" || _compare == "char")
			ofilecpp<<"		if (!writeStream->Write((char)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint16_t")
			ofilecpp<<"		if (!writeStream->Write((int16_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint32_t" || _compare == "int32_t")
			ofilecpp<<"		if (!writeStream->Write((int32_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint64_t")
			ofilecpp<<"		if (!writeStream->Write((int64_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "std::string")
			ofilecpp<<"		if (!writeStream->Write(this->"<<ClassProperty[l].name<<".c_str(), this->"<<ClassProperty[l].name<<".size())) return -1;"<<endl;
		else if (_compare == "double")
			ofilecpp<<"		if (!writeStream->Write(this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "std::vector")
		{
			ofilecpp<<"		if (!writeStream->Write((int32_t)this->"<<ClassProperty[l].name<<".size())) return -1;"<<endl;
			ofilecpp<<"		for ("<<ClassProperty[l].typeDetail<<"::const_iterator it=this->"<<ClassProperty[l].name<<".begin(); it!=this->"<<ClassProperty[l].name<<".end(); ++it) {"<<endl;
			CString _compareDetail = ClassProperty[l].detail;
			if (_compareDetail == "std::string")
				ofilecpp<<"			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;"<<endl;
			else if (_compareDetail == "BYTE" || _compareDetail == "char")
				ofilecpp<<"			if (!writeStream->Write((char)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint16_t")
				ofilecpp<<"			if (!writeStream->Write((int16_t)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint32_t" || _compareDetail == "int32_t")
				ofilecpp<<"			if (!writeStream->Write((int32_t)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint64_t")
				ofilecpp<<"			if (!writeStream->Write((int64_t)(*it))) return -1;"<<endl;
			else if (_compareDetail == "double")
				ofilecpp<<"			if (!writeStream->Write(*it)) return -1;"<<endl;
			else
				ofilecpp<<"			if ((*it).Serialize(writeStream) != 0) return -1;"<<endl;
			ofilecpp<<"		}"<<endl;
		}
		else
		{ofilecpp<<"		if (this->"<<ClassProperty[l].name<<".Serialize(writeStream) != 0) return -1;"<<endl;}

		ofilecpp<<"	}"<<endl;
	}
	ofilecpp<<endl<<"	return 0;"<<endl;
	ofilecpp<<"}"<<endl<<endl;
	/************************序列化函数************************/

	/************************反序列化函数************************/
	ofilecpp<<"int "<<name<<"::Unserialize(ReadStream * readStream)"<<endl;
	ofilecpp<<"{"<<endl;
	ofilecpp<<"	(void)readStream;"<<endl;
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		ofilecpp<<"	{"<<endl;
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE" || _compare == "char")
			ofilecpp<<"		if (!readStream->Read((char&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint16_t")
			ofilecpp<<"		if (!readStream->Read((int16_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint32_t" || _compare == "int32_t")
			ofilecpp<<"		if (!readStream->Read((int32_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint64_t")
			ofilecpp<<"		if (!readStream->Read((int64_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "std::string")
		{
			ofilecpp<<"		const char* p;"<<endl;
			ofilecpp<<"		size_t len;"<<endl;
			ofilecpp<<"		if (!readStream->ReadNoCopy(p, len)) return -1;"<<endl;
			ofilecpp<<"		this->"<<ClassProperty[l].name<<".assign(p, len);"<<endl;
		}
		else if (_compare == "double")
			ofilecpp<<"		if (!readStream->Read(this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "std::vector")
		{
			ofilecpp<<"		int32_t __len__;"<<endl;
			ofilecpp<<"		if (!readStream->Read(__len__)) return -1;"<<endl;
			ofilecpp<<"		this->"<<ClassProperty[l].name<<".reserve(__len__);"<<endl;
			ofilecpp<<"		for (int32_t i=0; i<__len__; ++i) {"<<endl;
			_compare = ClassProperty[l].detail;
			ofilecpp<<"			"<<_compare<<" __inner__;"<<endl;
			ofilecpp<<"			{"<<endl;
			if (_compare == "BYTE" || _compare == "char")
				ofilecpp<<"				if (!readStream->Read((char&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint16_t")
				ofilecpp<<"				if (!readStream->Read((int16_t&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint32_t" || _compare == "int32_t")
				ofilecpp<<"				if (!readStream->Read((int32_t&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint64_t")
				ofilecpp<<"				if (!readStream->Read((int64_t&)__inner__)) return -1;"<<endl;
			else if (_compare == "double")
				ofilecpp<<"				if (!readStream->Read(__inner__)) return -1;"<<endl;
			else if (_compare == "std::string")
			{
				ofilecpp<<"				const char* p;"<<endl;
				ofilecpp<<"				size_t len;"<<endl;
				ofilecpp<<"				if (!readStream->ReadNoCopy(p, len)) return -1;"<<endl;
				ofilecpp<<"				__inner__.assign(p, len);"<<endl;
			}
			else
				ofilecpp<<"		if (__inner__.Unserialize(readStream) != 0) return -1;	"<<endl;

			ofilecpp<<"			}"<<endl;
			ofilecpp<<"			this->"<<ClassProperty[l].name<<".push_back(__inner__);"<<endl;
			ofilecpp<<"		}"<<endl;
		}
		else
		{ofilecpp<<"		if (this->"<<ClassProperty[l].name<<".Unserialize(readStream) != 0) return -1;	"<<endl;}

		ofilecpp<<"	}"<<endl;
	}
	ofilecpp<<endl<<"	return 0;"<<endl;
	ofilecpp<<"}"<<endl<<endl;
	/************************反序列化函数************************/

	_structEndFlag = 0;	
	_propertyFlag = false;
	m_configUse.insert(map<CString, vector<PropertyBase> >::value_type(name, ClassProperty));
	name = "";
	ClassProperty.clear();
}

void Design::BeginDesignH()
{
	ofile<<"#ifndef _DESIGN_H_"<<endl;
	ofile<<"#define _DESIGN_H_"<<endl<<endl;
	ofile<<"#include <string>"<<endl;
	ofile<<"#include <vector>"<<endl;
	ofile<<"#include <list>"<<endl;
	ofile<<"#include <map>"<<endl;
	ofile<<"#include \"Streamable.h\""<<endl;
	ofile<<"#include \"CommonType.h\""<<endl;
	ofile<<"#include \"Struct.h\""<<endl<<endl;
	ofile<<"namespace design"<<endl;
	ofile<<"{"<<endl<<endl;
	ofile<<"using namespace Struct;"<<endl<<endl;
}

void Design::EndDesignH()
{
	ofile<<"}"<<endl<<endl;
	ofile<<"#endif"<<endl;
}

void Design::BeginDesignCpp()
{
	ofilecpp<<"#include \"Stream.h\""<<endl;
	ofilecpp<<"#include \"Design.h\""<<endl<<endl;
	ofilecpp<<"namespace design"<<endl;
	ofilecpp<<"{"<<endl<<endl;
	ofilecpp<<"using namespace Struct;"<<endl<<endl;
}

void Design::EndDesignCpp()
{
	ofilecpp<<"}"<<endl<<endl;
}

std::string Design::valueToString(double value)
{
	char buffer[32];
	sprintf_s(buffer, sizeof(buffer), "%#.16g", value);
	char* ch = buffer + strlen(buffer) - 1;
	while(ch >= buffer){
		switch(*ch){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			--ch;
			continue;
		case '.':
			*(ch) = '\0';
			return buffer;
		default:
			return buffer;
		}
	}
	return buffer;
}

// 将一个double类型小数点后面的数四舍五入 
double Design::Round(double value)
{
	return (value>=0.0) ? floor(value+0.5) : ceil(value-0.5);
}