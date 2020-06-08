#include "stdafx.h"
#include "ClientMsgH.h"
#include "AnalysisDlg.h"

extern CString saveDir;

ClientMsg::ClientMsg()
{
	Message.clear();
	ClassProperty.clear();
	_messageFlag = false;
	_nameFlag = false;
	_structEndFlag = 0;
	_propertyFlag = false;
	_majorCmdFlag = 0;
	_minorCmdFlag = 0;
	name = "";
	strSheetName = "";
	m_pProgress = NULL;
}
ClientMsgCPP::ClientMsgCPP()
{
}
ClientMsgCS::ClientMsgCS()
{
}

void ClientMsgCPP::BeginClientMsgH()
{
	ofile<<"#ifndef _CLIENT_MSG_H_"<<endl;
	ofile<<"#define _CLIENT_MSG_H_"<<endl;
	ofile<<"#include <string>"<<endl;
	ofile<<"#include <vector>"<<endl;
	ofile<<"#include <list>"<<endl;
	ofile<<"#include <map>"<<endl;
	ofile<<"#include \"CommonType.h\""<<endl;
	ofile<<"#include \"Struct.h\""<<endl;
	ofile<<"#include \"Streamable.h\""<<endl<<endl;
	ofile<<"namespace ClientMsg"<<endl;
	ofile<<"{"<<endl<<endl;
	ofile<<"using namespace Struct;"<<endl<<endl;
	ofile<<"struct __BaseMessage__  : public Streamable"<<endl;
	ofile<<"{"<<endl;
	ofile<<"	virtual int Serialize(WriteStream *) const;"<<endl;
	ofile<<"	virtual int Unserialize(ReadStream *);"<<endl;
	ofile<<"};"<<endl<<endl;
}
void ClientMsgCS::BeginClientCSharpMsg()
{
	ofile<<"using System;"<<endl;
	ofile<<"using System.Collections;"<<endl;
	ofile<<"using System.Collections.Generic;"<<endl<<endl;
}
void ClientMsgCS::EndClientCSharpMsg()
{
	ofile<<"public class NetMsgDefine"<<endl<<"{"<<endl;
	int i = 0;
	int j = 0;
	bool bIsSheetEnd = false;
	for (i = 0; i < CommandMsg.size(); ++i)
	{
		if (!bIsSheetEnd || CommandMsg[i].name.CompareNoCase(CommandMsg[i-1].name) != 0)
		{
			bIsSheetEnd = false;
			for (j = 0; j < Message.size(); ++j)
			{
				if (CommandMsg[i].sheetName == Message[j].name.c_str())
				{
					ofile<<"	public const uint E_"<<CommandMsg[i].sheetName<<"_"<<CommandMsg[i].name<<" = "<<Message[j].majorCmd*1000+CommandMsg[i].minorCmd<<";"<<endl;
					bIsSheetEnd = true;
					break;
				}
			}
		}
		else
		{
			ofile<<"	public const uint E_"<<CommandMsg[i].sheetName<<"_"<<CommandMsg[i].name<<" = "<<Message[j].majorCmd*1000+CommandMsg[i].minorCmd<<";"<<endl;
		}
	}
	ofile<<"}"<<endl;
}
void ClientMsgCPP::EndClientMsgH()
{
	ofile<<"}"<<endl<<endl;
	ofile<<"#endif"<<endl;
}
void ClientMsgCS::AnalysisClientMsg(IllusionExcelFile& excl)
{
	CString url;
	url.Format("%s/ClientMsg.cs",saveDir);
	ofile.open(url);

	BeginClientCSharpMsg();
	if (NULL == m_pProgress)
	{
		m_pProgress  = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG_PROGRESS);
	}
	bool bBeginProgress = true;
	CString strText;
	for (int number = 2; number < 20; ++number)
	{
		strSheetName = excl.GetSheetName(number);
		if (strSheetName == "Message")
		{
			_messageFlag = true;
		}
		bool bLoad = excl.LoadSheet(number);
		int nRow = excl.GetRowCount();
		int nCol = excl.GetColumnCount();

		if (bBeginProgress)
		{
			m_pProgress->m_ctrlProgress.SetRange(0,excl.GetSheetCount());
			m_pProgress->m_ctrlProgress.SetPos(0);
			strText.Format("0 / %d",excl.GetSheetCount());
			m_pProgress->m_ctrEdit.SetWindowText(strText);
			m_pProgress->ShowWindow(SW_SHOW);
			bBeginProgress = false;
		}
		else
		{
			m_pProgress->m_ctrlProgress.SetPos(number);
			strText.Format("%d / %d",number,excl.GetSheetCount());
			m_pProgress->m_ctrEdit.SetWindowText(strText);
		}
		for (int i=1; i<=nRow; i++)
		{
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
						else if (strValue == "majorCmd")
						{
							_majorCmdFlag = 1;

						}
						else if (strValue == "minorCmd")
						{
							_minorCmdFlag = 1;
						}
					}
					else
					{
						if (_nameFlag)
						{
							name = strValue;
							if (strSheetName == "Base")
								ofile<<"public class "<<name<<" : BaseMsg"<<endl<<"{"<<endl;
							else if (strSheetName == "Message")
							{
								MessageBase _msg;
								_msg.name = name;
								Message.push_back(_msg);
								ofile<<"public class "<<name<<" : "<<strSheetName<<endl<<"{"<<endl;
							}					
							else
							{
								CommandBase _commandmsg;
								_commandmsg.sheetName = strSheetName;
								_commandmsg.name = name;
								CommandMsg.push_back(_commandmsg);
								ofile<<"public class "<<name<<" : "<<strSheetName<<endl<<"{"<<endl;
							}
							_nameFlag = false;
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
						else if (_majorCmdFlag == 1)
						{
							ofile<<"	public const uint MAX_CMD = "<<strValue<<";"<<endl;
							Message[Message.size() - 1].majorCmd = atoi(strValue);
							_majorCmdFlag = 2;
						}
						else if (_minorCmdFlag == 1)
						{
							ofile<<"	public const uint MIN_CMD = "<<strValue<<";"<<endl;
							CommandMsg[CommandMsg.size() - 1].minorCmd = atoi(strValue);
							_minorCmdFlag = 2;
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
		if (Message.size() > 1 && strSheetName == Message[Message.size() - 1].name.c_str())
		{
			break;
		}
	}
	EndClientCSharpMsg();
	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
	ofile.close();
}
void ClientMsgCPP::AnalysisClientMsg(IllusionExcelFile& excl)
{
	CString url;
	url.Format("%s/ClientMsg.h",saveDir);
	ofile.open(url); 

	url.Format("%s/ClientMsg.cpp",saveDir);
	ofilecpp.open(url);    

	BeginClientMsgH();
	BeginClientMsgCpp();

	if (NULL == m_pProgress)
	{
		m_pProgress  = new CProgressDlg();
		m_pProgress->Create(IDD_DIALOG_PROGRESS);
	}
	bool bBeginProgress = true;
	CString strText;
	for (int number = 2; number < 20; ++number)
	{
		strSheetName = excl.GetSheetName(number);
		if (strSheetName == "Message")
			_messageFlag = true;

		bool bLoad = excl.LoadSheet(number);
		int nRow = excl.GetRowCount();
		int nCol = excl.GetColumnCount();

		for (int k = 0; k < Message.size(); ++k)
		{
			if (Message[k].name.c_str() == strSheetName)
			{
				nowMessage = Message[k];
			}
		}
		if (bBeginProgress)
		{
			m_pProgress->m_ctrlProgress.SetRange(0,excl.GetSheetCount());
			m_pProgress->m_ctrlProgress.SetPos(0);
			strText.Format("0 / %d",excl.GetSheetCount());
			m_pProgress->m_ctrEdit.SetWindowText(strText);
			m_pProgress->ShowWindow(SW_SHOW);
			bBeginProgress = false;
		}
		else
		{
			m_pProgress->m_ctrlProgress.SetPos(number);
			strText.Format("%d / %d",number,excl.GetSheetCount());
			 m_pProgress->m_ctrEdit.SetWindowText(strText);
		}
		for (int i=1; i<=nRow; ++i)
		{			
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
						else if (strValue == "majorCmd")
						{
							_majorCmdFlag = 1;						
						}
						else if (strValue == "minorCmd")
						{
							_minorCmdFlag = 1;
						}
					}
					else
					{
						if (_nameFlag)
						{
							name = strValue;
							if (strSheetName == "Message")
							{
								MessageBase _msg;
								_msg.name = name;
								Message.push_back(_msg);
							}

							if (strSheetName == "Base")
								ofile<<"struct "<<name<<" : public __BaseMessage__"<<endl<<"{"<<endl;
							else if (strSheetName == "Message")
								ofile<<"struct "<<name<<" : public Message "<<endl<<"{"<<endl;
							else
								ofile<<"struct "<<name<<" : public "<<strSheetName<<endl<<"{"<<endl;
							_nameFlag = false;
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
						else if (_majorCmdFlag == 1)
						{
							ofile<<"	static const uint32_t MAJOR_CMD = "<<strValue<<";"<<endl;
							Message[Message.size() - 1].majorCmd = atoi(strValue);
							_majorCmdFlag = 2;
						}
						else if (_minorCmdFlag == 1)
						{
							ofile<<"	static const uint32_t MINOR_CMD = "<<strValue<<";"<<endl;
							ofile<<"	static const uint32_t CMD = "<<atoi(strValue) + nowMessage.majorCmd* 1000<<";"<<endl<<endl;
							_minorCmdFlag = 2;
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
				ClassProperty.push_back(nowProperty);
			}
		}
		
		DealMsgItem();

		if (Message.size() > 1 && strSheetName == Message[Message.size() - 1].name.c_str())
		{
			break;
		}
	}

	EndClientMsgH();
	EndClientMsgCpp();

	if (NULL != m_pProgress)
	{
		delete m_pProgress;
		m_pProgress = NULL;
	}
	ofile.close();
	ofilecpp.close();                //关闭文件
}
void ClientMsgCS::DealCSharpMsgItem()
{
	if (_majorCmdFlag == 2)
	{
		ofile<<"	public "<<name<<"()"<<endl<<"	{"<<endl;
		ofile<<"		majorCmd = MAX_CMD;"<<endl<<"	}"<<endl;
	}
	else if (_minorCmdFlag == 2)
	{
		ofile<<"	public "<<name<<"() : base()"<<endl<<"	{"<<endl;
		ofile<<"		minorCmd = MIN_CMD;"<<endl;
		for (int l = 0; l < ClassProperty.size(); ++l)
		{
			CString _compare = ClassProperty[l].type;
			if (_compare != "byte" && _compare != "uint" && _compare != "ulong")
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
	_majorCmdFlag = 0;
	_minorCmdFlag = 0;
	_structEndFlag = 0;	
	_propertyFlag = false;
	name = "";
	ClassProperty.clear();
}
void ClientMsgCPP::DealMsgItem()
{
	ofile<<endl<<"	"<<name<<"();"<<endl<<endl;
	ofile<<"	virtual int Serialize(WriteStream *) const;"<<endl;
	ofile<<"	virtual int Unserialize(ReadStream *);"<<endl;
	ofile<<"};"<<endl<<endl;
	
	/************************构造函数************************/
	ofilecpp<<name<<"::"<<name<<"()"<<endl;
	ofilecpp<<"{"<<endl;
	if (_majorCmdFlag == 2)
	{
		ofilecpp<<"	this->majorCmd = MAJOR_CMD;"<<endl;
	}
	else if (_minorCmdFlag == 2)
	{
		ofilecpp<<"	this->minorCmd = MINOR_CMD;"<<endl;
	}

	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE" || _compare == "uint32_t" || _compare == "uint64_t")
			ofilecpp<<"	"<<ClassProperty[l].name<<" = 0;"<<endl;
	}
	ofilecpp<<"}"<<endl<<endl;
	/************************构造函数************************/

	/************************序列化函数************************/
	ofilecpp<<"int "<<name<<"::Serialize(WriteStream * writeStream) const"<<endl;
	ofilecpp<<"{"<<endl;
	ofilecpp<<"	(void)writeStream;"<<endl;
	if (strSheetName == "Base")
		ofilecpp<<"	if (__BaseMessage__::Serialize(writeStream) != 0) return -1;"<<endl;
	else
		ofilecpp<<"	if ("<<strSheetName<<"::Serialize(writeStream) != 0) return -1;"<<endl;
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		ofilecpp<<"	{"<<endl;
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE")
		{ofilecpp<<"		if (!writeStream->Write((char)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "uint32_t")
		{ofilecpp<<"		if (!writeStream->Write((int32_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "uint64_t")
		{ofilecpp<<"		if (!writeStream->Write((int64_t)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "std::string")
		{ofilecpp<<"		if (!writeStream->Write(this->"<<ClassProperty[l].name<<".c_str(), this->"<<ClassProperty[l].name<<".size())) return -1;"<<endl;}		
		else if (_compare == "std::vector")
		{
			ofilecpp<<"		if (!writeStream->Write((int32_t)this->"<<ClassProperty[l].name<<".size())) return -1;"<<endl;
			ofilecpp<<"		for ("<<ClassProperty[l].typeDetail<<"::const_iterator it=this->"<<ClassProperty[l].name<<".begin(); it!=this->"<<ClassProperty[l].name<<".end(); ++it) {"<<endl;
			CString _compareDetail = ClassProperty[l].detail;
			if (_compareDetail == "std::string")
				ofilecpp<<"			if (!writeStream->Write((*it).c_str(), (*it).size())) return -1;"<<endl;
			else if (_compareDetail == "BYTE")
				ofilecpp<<"			if (!writeStream->Write((char)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint32_t")
				ofilecpp<<"			if (!writeStream->Write((int32_t)(*it))) return -1;"<<endl;
			else if (_compareDetail == "uint64_t")
				ofilecpp<<"			if (!writeStream->Write((int64_t)(*it))) return -1;"<<endl;
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
	if (strSheetName == "Base")
		ofilecpp<<"	if (__BaseMessage__::Unserialize(readStream) != 0) return -1;"<<endl;
	else
		ofilecpp<<"	if ("<<strSheetName<<"::Unserialize(readStream) != 0) return -1;"<<endl;
	for (int l = 0; l < ClassProperty.size(); ++l)
	{
		ofilecpp<<"	{"<<endl;
		CString _compare = ClassProperty[l].type;
		if (_compare == "BYTE")
		{ofilecpp<<"		if (!readStream->Read((char&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "uint32_t")
		{ofilecpp<<"		if (!readStream->Read((int32_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "uint64_t")
		{ofilecpp<<"		if (!readStream->Read((int64_t&)this->"<<ClassProperty[l].name<<")) return -1;"<<endl;}
		else if (_compare == "std::string")
		{
			ofilecpp<<"		const char* p;"<<endl;
			ofilecpp<<"		size_t len;"<<endl;
			ofilecpp<<"		if (!readStream->ReadNoCopy(p, len)) return -1;"<<endl;
			ofilecpp<<"		this->"<<ClassProperty[l].name<<".assign(p, len);"<<endl;
		}
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
			else if (_compare == "uint32_t")
				ofilecpp<<"				if (!readStream->Read((int32_t&)__inner__)) return -1;"<<endl;
			else if (_compare == "uint64_t")
				ofilecpp<<"				if (!readStream->Read((int64_t&)__inner__)) return -1;"<<endl;
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

	_majorCmdFlag = 0;
	_minorCmdFlag = 0;
	_structEndFlag = 0;	
	_propertyFlag = false;
	name = "";
	ClassProperty.clear();
}

void ClientMsgCPP::BeginClientMsgCpp()
{
	ofilecpp<<"#include \"Stream.h\""<<endl;
	ofilecpp<<"#include \"ClientMsg.h\""<<endl<<endl;
	ofilecpp<<"namespace ClientMsg"<<endl;
	ofilecpp<<"{"<<endl<<endl;
	ofilecpp<<"using namespace Struct;"<<endl<<endl;
	ofilecpp<<"int __BaseMessage__::Serialize(WriteStream *) const"<<endl;
	ofilecpp<<"{"<<endl;
	ofilecpp<<"	return 0;"<<endl;
	ofilecpp<<"}"<<endl<<endl;
	ofilecpp<<"int __BaseMessage__::Unserialize(ReadStream *)"<<endl;
	ofilecpp<<"{"<<endl;
	ofilecpp<<"	return 0;"<<endl;
	ofilecpp<<"}"<<endl<<endl;
}

void ClientMsgCPP::EndClientMsgCpp()
{
	ofilecpp<<"};"<<endl<<endl;
}