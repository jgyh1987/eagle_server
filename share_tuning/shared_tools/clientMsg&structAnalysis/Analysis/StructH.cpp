#include "stdafx.h"
#include "StructH.h"
#include "AnalysisDlg.h"

extern CString saveDir;

StructH::StructH()
{
	Message.clear();
	ClassProperty.clear();
	_messageFlag = false;
	_nameFlag = false;
	_structEndFlag = 0;
	_propertyFlag = false;
	name = "";
	strSheetName = "";
	names.clear();
	writes.clear();
	m_pProgress = NULL;
}

void StructHCPP::AnalysisStructMsg(IllusionExcelFile& excl)
{
	CString url;
	url.Format("%s/Struct.h",saveDir);
	ofile.open(url); 

	url.Format("%s/Struct.cpp",saveDir);
	ofilecpp.open(url);    

	BeginStructH();
	BeginStructCpp();

	bool bLoad = excl.LoadSheet(2);
	int nRow = excl.GetRowCount();
	int nCol = excl.GetColumnCount();

	if (NULL == m_pProgress)
	{
		m_pProgress  = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG_PROGRESS);
	}
	bool bBeginProgress = true;
	CString strText;
	for (int i=1; i<=nRow; ++i)
	{	
		if (bBeginProgress)
		{
			m_pProgress->m_ctrlProgress.SetRange(0,nRow);
			m_pProgress->m_ctrlProgress.SetPos(0);
			strText.Format("0 / %d",nRow);
			m_pProgress->m_ctrEdit.SetWindowText(strText);
			m_pProgress->ShowWindow(SW_SHOW);
			bBeginProgress = false;
		}
		else
		{
			m_pProgress->m_ctrlProgress.SetPos(i);
			strText.Format("%d / %d",i,nRow);
			m_pProgress->m_ctrEdit.SetWindowText(strText);
		}
		for (int j=1; j<=nCol; ++j)
		{
			CString strValue = excl.GetCellString(i, j);
			if (strValue == "")
			{
				if (j == 2)
				{
					if (_structEndFlag == 1)
						_structEndFlag = 2;
					break;
				}					
			}
			else
			{
				if (j == 1)
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
				}
				else
				{
					if (_nameFlag)
					{
						name = strValue;
						ofile<<"struct "<<name<<" : public Streamable{"<<endl;
						//writes.push_back("struct " + name + " : public Streamable{");
						_nameFlag = false;
						names.push_back(name);
					}
					else if (_propertyFlag)
					{
						if (j == 2)
							nowProperty.name = strValue;
						else if (j == 3)
							nowProperty.SetType(strValue);
						else if (j == 4)
							nowProperty.SetDetail(strValue);
					}
				}				
			}	
		}

		if (_structEndFlag == 2)
		{
			DealMsgItem();
		}			
		else if (_propertyFlag)
		{
			ofile<<"	"<<nowProperty.typeDetail<<" "<<nowProperty.name<<";"<<endl;
			//writes.push_back("	" + nowProperty.typeDetail + " " + nowProperty.name + ";");
			ClassProperty.push_back(nowProperty);
		}
	}
	DealMsgItem();

	/*BeginStructH();
	for (int i = 0 ; i < writes.size(); ++i)
	{
	ofile<<writes[i]<<endl;
	}*/
	EndStructH();
	EndStructCpp();
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
	ofile.close();
	ofilecpp.close();                //关闭文件
}

void StructHCPP::DealMsgItem()
{
	ofile<<endl<<"	"<<name<<"();"<<endl<<endl;
	ofile<<"	virtual int Serialize(WriteStream *) const;"<<endl;
	ofile<<"	virtual int Unserialize(ReadStream *);"<<endl;
	ofile<<"};"<<endl<<endl;
	/*writes.push_back("");
	writes.push_back("	" + name + "();");
	writes.push_back("");
	writes.push_back("	virtual int Serialize(WriteStream *) const;");
	writes.push_back("	virtual int Unserialize(ReadStream *);");
	writes.push_back("};");
	writes.push_back("");*/

	/************************构造函数************************/
	ofilecpp<<name<<"::"<<name<<"()"<<endl;
	ofilecpp<<"{"<<endl;
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE" || _compare == "uint32_t" || _compare == "uint64_t" || _compare == "double" || _compare == "uint16_t")
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
		if (_compare == "BYTE")
			ofilecpp<<"		if (!writeStream->Write((char)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint16_t")
			ofilecpp<<"		if (!writeStream->Write((int16_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint32_t")
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
			else if (_compareDetail == "BYTE")
				ofilecpp<<"			if (!writeStream->Write((char)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint16_t")
				ofilecpp<<"			if (!writeStream->Write((int16_t)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint32_t")
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
		if (_compare == "BYTE")
			ofilecpp<<"		if (!readStream->Read((char&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint16_t")
			ofilecpp<<"		if (!readStream->Read((int16_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;
		else if (_compare == "uint32_t")
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
			if (_compare == "BYTE")
				ofilecpp<<"				if (!readStream->Read((char&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint16_t")
				ofilecpp<<"				if (!readStream->Read((int16_t&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint32_t")
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
	name = "";
	ClassProperty.clear();
}

void StructHCPP::BeginStructH()
{
	ofile<<"#ifndef _STRUCT_H_"<<endl;
	ofile<<"#define _STRUCT_H_"<<endl<<endl;
	ofile<<"#include <string>"<<endl;
	ofile<<"#include <vector>"<<endl;
	ofile<<"#include <list>"<<endl;
	ofile<<"#include <map>"<<endl;
	ofile<<"#include \"Streamable.h\""<<endl;
	ofile<<"#include \"CommonType.h\""<<endl<<endl;
	ofile<<"namespace Struct{"<<endl<<endl;

	/*for (int i = 0; i < names.size(); ++i)
	{
	ofile<<"struct "<<names[i]<<";"<<endl;
	}
	ofile<<endl;*/
}

void StructHCPP::EndStructH()
{
	ofile<<"}"<<endl<<endl;
	ofile<<"#endif"<<endl;
}

void StructHCPP::BeginStructCpp()
{
	ofilecpp<<"#include \"Stream.h\""<<endl;
	ofilecpp<<"#include \"Struct.h\""<<endl<<endl;
	ofilecpp<<"namespace Struct"<<endl;
	ofilecpp<<"{"<<endl<<endl;
}

void StructHCPP::EndStructCpp()
{
	ofilecpp<<"};"<<endl<<endl;
}

void StructHCS::BeginStructCSharpMsg()
{
	ofile<<"using System;"<<endl;
	ofile<<"using System.Collections;"<<endl;
	ofile<<"using System.Collections.Generic;"<<endl<<endl;
}

void StructHCS::AnalysisStructMsg(IllusionExcelFile& excl)
{
	CString url;
	url.Format("%s/Struct.cs",saveDir);
	ofile.open(url);

	BeginStructCSharpMsg();

	bool bLoad = excl.LoadSheet(2);
	int nRow = excl.GetRowCount();
	int nCol = excl.GetColumnCount();
	if (NULL == m_pProgress)
	{
		m_pProgress  = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG_PROGRESS);
	}
	bool bBeginProgress = true;
	CString strText;
	for (int i=1; i<=nRow; i++)
	{
		if (bBeginProgress)
		{
			m_pProgress->m_ctrlProgress.SetRange(0,nRow);
			m_pProgress->m_ctrlProgress.SetPos(0);
			strText.Format("0 / %d",nRow);
			m_pProgress->m_ctrEdit.SetWindowText(strText);
			m_pProgress->ShowWindow(SW_SHOW);
			bBeginProgress = false;
		}
		else
		{
			m_pProgress->m_ctrlProgress.SetPos(i);
			strText.Format("%d / %d",i,nRow);
			m_pProgress->m_ctrEdit.SetWindowText(strText);
		}
		for (int j=1; j<=nCol; j++)
		{
			CString strValue = excl.GetCellString(i,j);
			if (strValue == "")
			{
				if (j == 2)
				{
					if (_structEndFlag == 1)
						_structEndFlag = 2;
					break;
				}					
			}
			else
			{
				if (j == 1)
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
				}
				else
				{
					if (_nameFlag)
					{
						name = strValue;
						ofile<<"public class "<<name<<" : BaseMsg"<<endl<<"{"<<endl;
						_nameFlag = false;
						names.push_back(name);
					}
					else if (_propertyFlag)
					{
						if (j == 2)
							nowProperty.name = strValue;
						else if (j == 3)
							nowProperty.SetCSharpType(strValue);
						else if (j == 4)
							nowProperty.SetCSharpDetail(strValue);
					}
				}				
			}
		}
		if (_structEndFlag == 2)
		{
			DealCSharpMsgItem();
		}			
		else if (_propertyFlag)
		{
			ClassProperty.push_back(nowProperty);
		}
	}
	DealCSharpMsgItem();
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
	ofile.close();
}

void StructHCS::DealCSharpMsgItem()
{
	{
		ofile<<"	public "<<name<<"()"<<endl<<"	{"<<endl;
		for (int l = 0; l < ClassProperty.size(); ++l)
		{
			CString _compare = ClassProperty[l].type;
			if (_compare != "byte" && _compare != "ushort" && _compare != "uint" && _compare != "ulong" && _compare != "double")
			{
				if (_compare == "string")
				{
					ofile<<"		"<<ClassProperty[l].name<<" = string.Empty;"<<endl;
				}
				else if (_compare == "List")
				{
					ofile<<"		"<<ClassProperty[l].name<<" = new "<<ClassProperty[l].typeDetail<<"();"<<endl;
				}
				else
				{
					ofile<<"		"<<ClassProperty[l].name<<" = new "<<ClassProperty[l].type<<"();"<<endl;
				}
			}
		}
		ofile<<"	}"<<endl;
	}
	if (_propertyFlag)
	{
		for (int l = 0; l < ClassProperty.size(); ++l)
		{
			ofile<<"	public "<<ClassProperty[l].typeDetail<<" "<<ClassProperty[l].name<<";"<<endl;
		}
		ofile<<"	public override void Read(CReadStream mCReadStream)"<<endl<<"	{"<<endl;
		ofile<<"		base.Read(mCReadStream);"<<endl;
		int iVectorCount = 1;
		for (int l = 0; l < ClassProperty.size(); ++l)
		{

			if (ClassProperty[l].type == "byte")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadByte();"<<endl;
			}
			else if (ClassProperty[l].type == "ushort")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadUShort();"<<endl;
			}
			else if (ClassProperty[l].type == "uint")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadUInt();"<<endl;
			}
			else if (ClassProperty[l].type == "ulong")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadULong();"<<endl;
			}
			else if (ClassProperty[l].type == "string")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadString();"<<endl;
			}
			else if (ClassProperty[l].type == "double")
			{
				ofile<<"		"<<ClassProperty[l].name<<" = mCReadStream.ReadDouble();"<<endl;
			}
			else if (ClassProperty[l].type == "List")
			{
				ofile<<"		uint nCount"<<iVectorCount<<" = mCReadStream.ReadUInt();"<<endl;
				ofile<<"		for(int i=0;i<nCount"<<iVectorCount<<";i++)"<<endl<<"		{"<<endl;
				if (ClassProperty[l].detail == "byte")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadByte());"<<endl;
				}
				else if (ClassProperty[l].detail == "ushort")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadUShort());"<<endl;
				}
				else if (ClassProperty[l].detail == "uint")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadUInt());"<<endl;
				}
				else if (ClassProperty[l].detail == "ulong")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadULong());"<<endl;
				}
				else if (ClassProperty[l].detail == "double")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadDouble());"<<endl;
				}
				else if (ClassProperty[l].detail == "string")
				{
					ofile<<"			"<<ClassProperty[l].name<<".Add(mCReadStream.ReadString());"<<endl;
				}
				else
				{
					ofile<<"			"<<ClassProperty[l].detail<<" elem"<<iVectorCount<<" = new "<<ClassProperty[l].detail<<"();"<<endl;
					ofile<<"			elem"<<iVectorCount<<".Read(mCReadStream);"<<endl;
					ofile<<"			"<<ClassProperty[l].name<<".Add(elem"<<iVectorCount<<");"<<endl;
				}
				ofile<<"		}"<<endl;
				++iVectorCount;
			}
			else
			{
				ofile<<"		"<<ClassProperty[l].name<<".Read(mCReadStream);"<<endl;
			}
		}
		ofile<<"	}"<<endl;

		ofile<<"	public override void Write(CWriteStream mCWriteStream)"<<endl<<"	{"<<endl;
		ofile<<"		base.Write(mCWriteStream);"<<endl;
		int iVectorCountSecond = 1;
		for (int l = 0; l < ClassProperty.size(); ++l)
		{
			if (ClassProperty[l].type == "byte")
			{
				ofile<<"		"<<"mCWriteStream.WriteByte("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "ushort")
			{
				ofile<<"		"<<"mCWriteStream.WriteUShort("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "uint")
			{
				ofile<<"		"<<"mCWriteStream.WriteUInt("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "ulong")
			{
				ofile<<"		"<<"mCWriteStream.WriteULong("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "double")
			{
				ofile<<"		"<<"mCWriteStream.WriteDouble("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "string")
			{
				ofile<<"		"<<"mCWriteStream.WriteString("<<ClassProperty[l].name<<");"<<endl;
			}
			else if (ClassProperty[l].type == "List")
			{
				ofile<<"		uint nCount"<<iVectorCountSecond<<" = (uint)"<<ClassProperty[l].name<<".Count;"<<endl;
				ofile<<"		mCWriteStream.WriteUInt(nCount"<<iVectorCountSecond<<");"<<endl;
				ofile<<"		for(int i=0;i<nCount"<<iVectorCountSecond<<";i++)"<<endl<<"		{"<<endl;
				if (ClassProperty[l].detail == "byte")
				{
					ofile<<"			mCWriteStream.WriteByte("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else if (ClassProperty[l].detail == "ushort")
				{
					ofile<<"			mCWriteStream.WriteUShort("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else if (ClassProperty[l].detail == "uint")
				{
					ofile<<"			mCWriteStream.WriteUInt("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else if (ClassProperty[l].detail == "ulong")
				{
					ofile<<"			mCWriteStream.WriteULong("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else if (ClassProperty[l].detail == "double")
				{
					ofile<<"			mCWriteStream.WriteDouble("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else if (ClassProperty[l].detail == "string")
				{
					ofile<<"			mCWriteStream.WriteString("<<ClassProperty[l].name<<"[i]);"<<endl;
				}
				else
				{
					ofile<<"			"<<ClassProperty[l].name<<"[i].Write(mCWriteStream);"<<endl;
				}
				ofile<<"		}"<<endl;
				++iVectorCountSecond;
			}
			else
			{
				ofile<<"		"<<ClassProperty[l].name<<".Write(mCWriteStream);"<<endl;
			}
		}
		ofile<<"	}"<<endl;
	}
	ofile<<"}"<<endl<<endl;
	_structEndFlag = 0;	
	_propertyFlag = false;
	name = "";
	ClassProperty.clear();
}
void StructHCS::EndStructCSharpMsg()
{
	ofile<<endl;
}

PropertyBase::PropertyBase()
{
	name = "";
	type = "";
	detail = "";
	typeDetail = "";
}

void PropertyBase::Clear()
{
	name = "";
	type = "";
	detail = "";
	typeDetail = "";
}

void PropertyBase::SetType(CString _type)
{
	if (_type == "string")
		type = "std::string";
	else if (_type == "uint8")
		type = "BYTE";
	else if (_type == "uint16")
		type = "uint16_t";
	else if (_type == "uint32")
		type = "uint32_t";
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

void PropertyBase::SetCSharpType(CString _type)
{
	if (_type == "uint8")
		type = "byte";
	else if (_type == "uint16")
		type = "ushort";
	else if (_type == "uint32")
		type = "uint";
	else if (_type == "uint64")
		type = "ulong";
	else if (_type == "string")
		type = "string";
	else if (_type == "double")
		type = "double";
	else if (_type =="vector")
		type = "List";
	else
		type = _type;
	typeDetail = type;
}
void PropertyBase::SetDetail(CString _detail)
{
	if (_detail == "string")
		detail = "std::string";
	else if (_detail == "uint8")
		detail = "BYTE";
	else if (_detail == "uint16")
		detail = "uint16_t";
	else if (_detail == "uint32")
		detail = "uint32_t";
	else if (_detail == "uint64")
		detail = "uint64_t";
	else if (_detail == "double")
		detail = "double";
	else
		detail = "Struct::" + _detail;

	typeDetail = type + "< " + detail + " >";
}
void PropertyBase::SetCSharpDetail(CString _detail)
{
	if (_detail == "uint8")
		detail = "byte";
	else if (_detail == "uint16")
		detail = "ushort";
	else if (_detail == "uint32")
		detail = "uint";
	else if (_detail == "uint64")
		detail = "ulong";
	else if (_detail == "string")
		detail = "string";
	else if (_detail == "double")
		detail = "double";
	else
		detail = _detail;
	typeDetail = type + "<" + detail + ">";
}
