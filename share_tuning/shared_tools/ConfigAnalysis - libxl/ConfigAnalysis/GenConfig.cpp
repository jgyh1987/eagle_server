#include "stdafx.h"
#include "Design.h"

bool is_str_utf8(const char* str)
{
	unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
	unsigned char chr = *str;
	bool bAllAscii = true;
	for (unsigned int i = 0; str[i] != '\0'; ++i) {
		chr = *(str + i);
		//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
		if (nBytes == 0 && (chr & 0x80) != 0) {
			bAllAscii = false;
		}
		if (nBytes == 0) {
			//如果不是ASCII码,应该是多字节符,计算字节数
			if (chr >= 0x80) {
				if (chr >= 0xFC && chr <= 0xFD) {
					nBytes = 6;
				}
				else if (chr >= 0xF8) {
					nBytes = 5;
				}
				else if (chr >= 0xF0) {
					nBytes = 4;
				}
				else if (chr >= 0xE0) {
					nBytes = 3;
				}
				else if (chr >= 0xC0) {
					nBytes = 2;
				}
				else {
					return false;
				}
				nBytes--;
			}
		}
		else {
			//多字节符的非首字节,应为 10xxxxxx
			if ((chr & 0xC0) != 0x80) {
				return false;
			}
			//减到为零为止
			nBytes--;
		}
	}
	//违返UTF8编码规则
	if (nBytes != 0) {
		return false;
	}
	if (bAllAscii) { //如果全部都是ASCII, 也是UTF8
		return true;
	}
	return true;
}

bool is_str_gbk(const char* str)
{
	unsigned int nBytes = 0;//GBK可用1-2个字节编码,中文两个 ,英文一个
	unsigned char chr = *str;
	bool bAllAscii = true; //如果全部都是ASCII,
	for (unsigned int i = 0; str[i] != '\0'; ++i) {
		chr = *(str + i);
		if ((chr & 0x80) != 0 && nBytes == 0) {// 判断是否ASCII编码,如果不是,说明有可能是GBK
			bAllAscii = false;
		}
		if (nBytes == 0) {
			if (chr >= 0x80) {
				if (chr >= 0x81 && chr <= 0xFE) {
					nBytes = +2;
				}
				else {
					return false;
				}
				nBytes--;
			}
		}
		else {
			if (chr < 0x40 || chr>0xFE) {
				return false;
			}
			nBytes--;
		}//else end
	}
	if (nBytes != 0) {   //违返规则
		return false;
	}
	if (bAllAscii) { //如果全部都是ASCII, 也是GBK
		return true;
	}
	return true;
}

string GBKToUTF8(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n + 1];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n + 1];
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

string GBKToUTF8_1(const std::string& strGBK)
{
	string strOutUTF8 = "";
	WCHAR * str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new WCHAR[n + 1];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n + 1];
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	strOutUTF8 = str2;
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
}

int Gb2312ToUnicode(wchar_t* pOut, char *gbBuffer)
{
	return ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, gbBuffer, 2, pOut, 1);
}

string UTF8ToGBK(const std::string& strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	//strUTF8 = szGBK;
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}


extern CString fileDir;
extern CString saveDir;
extern CString saveConfigDir;
extern CString saveAloneExportDir;
void Design::GenType(CString _type, CString _value)
{
	if (_type == "std::string")
	{
		//if (is_str_utf8(_value))
		{
			//_value.Replace(" ", "");
			int _size = strlen(_value);

			ofile.write((const char*)&_size, sizeof(int));
			ofile.write(_value, _size);
		}
		//else
		//{
		//	_value.Replace(" ", "");
		//	int _size = strlen(_value);

		//	if (is_str_gbk(_value))
		//	{
		//		int a = 1;
		//	}

		//	for (auto i = 0; i < _size; ++i)
		//	{
		//		UINT32 a = (UINT8)_value[i];

		//		a = 10;
		//	}

		//	wchar_t temp1[5] = {0};
		//	char temp2[3] = {0};
		//	temp2[0] = _value.GetBuffer()[0];
		//	temp2[1] = _value.GetBuffer()[1];
		//	if (ERROR_NO_UNICODE_TRANSLATION == Gb2312ToUnicode(temp1, temp2))
		//	{
		//		int a = 1;
		//	}

		//	auto _temp = GBKToUTF8_1(_value.GetBuffer());

		//	_size = _temp.size();

		//	ofile.write((const char*)&_size, sizeof(int));

		//	ofile.write(_temp.c_str(), _size);

		//}
	}
	else if (_type == "char")
	{
		int _size = sizeof(signed char);
		char _temp = atoi(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "BYTE")
	{
		int _size = sizeof(signed char);
		char _temp = atoi(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "uint16_t")
	{
		int _size = sizeof(unsigned short);
		short _temp = atoi(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "int32_t")
	{
		int _size = sizeof(unsigned long);
		int _temp = atoi(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "uint32_t")
	{
		int _size = sizeof(unsigned long);
		int _temp = atoi(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "uint64_t")
	{
		int _size = sizeof(unsigned long long);
		long long _temp = _atoi64(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "double")
	{
		int _size = sizeof(double);
		double _temp = atof(_value);
		ofile.write((const char*)&_temp, _size);
	}
	else if (_type == "std::vector")
	{

	}
	else
		AfxMessageBox("type:" + _type + "  value:" + _value + " is error!");
}

int Design::GetPropertyLength(CString _type, CString _value, CString _detail)
{
	int length = 0;
	if (_type == "std::string")
	{
		auto temp = GBKToUTF8(_value.GetBuffer());

		if (is_str_utf8(_value))
		{
			int a = 10;
		}

		if (is_str_gbk(_value))
		{
			int a = 10;
		}

		//if (is_str_utf8(_value))
		{
			//_value.Replace(" ", "");
			length = _value.GetLength();
			length += sizeof(int);
		}
		//else
		//{

		//	_value.Replace(" ", "");
		//	auto temp = GBKToUTF8(_value.GetBuffer());
		//	length = temp.length();
		//	length += sizeof(int);
		//}
	}
	else if (_type == "char")
		length = sizeof(signed char);
	else if (_type == "BYTE")
		length = sizeof(unsigned char);
	else if (_type == "uint16_t")
		length = sizeof(unsigned short);
	else if (_type == "int32_t")
		length = sizeof(unsigned long);
	else if (_type == "uint32_t")
		length = sizeof(unsigned long);
	else if (_type == "uint64_t")
		length = sizeof(unsigned long long);
	else if (_type == "double")
		length = sizeof(double);
	else if (_type == "std::vector")
	{
		length = sizeof(unsigned long);
		length += vecIndex.size() * GetPropertyLength(_detail, "");
	}
	else
		length = 0;
	return length;
}
void Design::LineFeed(CListBox& _listBox,CString strText)
{
	int const iRowSize = 25;
	int const iRowAddSize = 26;
	while (CStringW(strText).GetLength() > iRowSize)
	{
		WCHAR strOne[iRowAddSize] = {};
		wcsncpy(strOne,CStringW(strText),iRowSize);

		_listBox.AddString(CString(strOne));
		strText=CStringW(strText).Right(CStringW(strText).GetLength() - iRowSize); 
	}
	_listBox.AddString(strText);
}
void Design::AnalysisAllConfigExcel(libxl::Book* book, CListBox& _listBox ,CProgressBarDlg* pBar)
{
	int iCount = m_configUse.size();
	int iNext = 0;
	for (map< CString, vector<PropertyBase> >::iterator it = m_configUse.begin(); it != m_configUse.end(); ++it)
	{
		if (!strlen(it->first.GetString()))
			continue;

		CString str = "正在处理" + it->first + "配置";
		_listBox.AddString(str);

		int count = _listBox.GetCount ();
		_listBox.SetCurSel (count - 1);
		pBar->SetTiTleDlg(++iNext,iCount,false);
		try
		{
			AnalysisConfigExcel(book, it->first, it->second, pBar);
		}
		catch (CException* e)
		{
			TCHAR szError[1024];
			e->GetErrorMessage(szError, 1024);
			LineFeed(_listBox,szError);

			count = _listBox.GetCount ();
			_listBox.SetCurSel (count - 1);
		}
	}
}

void Design::AnalysisOneConfigExcel(libxl::Book* book, CString _name ,CProgressBarDlg* pBar)
{	
	map< CString, vector<PropertyBase> >::iterator it = m_configUse.find(_name);
	if (it == m_configUse.end())
	{
		AfxMessageBox("name:" + _name + "can't find excel!");
		return;
	}
	AnalysisConfigExcel(book, _name, it->second, pBar);
}


void Design::AnalysisConfigExcel(libxl::Book* book, CString name, vector<PropertyBase>& useProperty ,CProgressBarDlg* pBar)
{
	CString fileName;
	fileName.Format("%s/%s.xls", fileDir, name);

	if(!book->load(fileName))
	{
		AfxMessageBox("加载文件初始化失败!");
		return;
	}

	CString saveName;
	saveName.Format("%s\\%s.dat", saveConfigDir, name);
	ofile.open(saveName, ios::out|ios::binary);

	libxl::Sheet* sheet = book->getSheet(0);
	int nRow = sheet->lastRow();
	int nCol = sheet->lastCol();

	CString strValue;
	double iNum = 0;
	vector<int> usedIndex;
	usedIndex.resize(useProperty.size(), 0);
	vecIndex.clear();
	m_bBeginProgress = true;
	for (int i = 1; i <= nCol; ++i)
	{
		switch (sheet->cellType(1, i-1))
		{
		case libxl::CELLTYPE_NUMBER:
			iNum = sheet->readNum(1, i-1);
			iNum = ConfigRound(iNum);
			strValue = ConfigvalueToString(iNum).c_str();
			break;
		case libxl::CELLTYPE_STRING:
			strValue = sheet->readStr(1, i-1);
			break;
		default:
			strValue = "";
			break;
		}
		if (strValue == "")
		{
			continue;
		}
		else
		{
			for (int j = 0; j < useProperty.size(); ++j)
			{
				if (useProperty[j].type == "std::vector")
				{
					int _size = useProperty[j].name.GetLength();
					strValue = strValue.Left(_size);
					if (useProperty[j].name == strValue)
					{						
						if (vecIndex.size() == 0)
						{
							usedIndex[j] = i;
						}
						vecIndex.push_back(i);
						break;
					}
				}
				else
				{
					if (useProperty[j].name == strValue)
					{
						usedIndex[j] = i;
						break;
					}
				}
			}
		}		
	}

	bool _endFlag = false;
	for (int i = 4; i <= nRow; ++i)
	{	
		ConfigInitializationBar(nRow-3, i-3, pBar);
		int length = 0;
		for (int k = 0; k < 2; ++k)
		{
			for (int j = 0; j < usedIndex.size(); ++j)
			{
				switch (sheet->cellType(i-1, usedIndex[j]-1))
				{
				case libxl::CELLTYPE_NUMBER:
					iNum = sheet->readNum(i-1, usedIndex[j]-1);
					iNum = ConfigRound(iNum);
					strValue = ConfigvalueToString(iNum).c_str();
					break;
				case libxl::CELLTYPE_STRING:
					strValue = sheet->readStr(i-1, usedIndex[j]-1);
					break;
				default:
					strValue = "";
					break;
				}
				if (strValue == "" && usedIndex[j] == 1)
				{
					_endFlag = true;
					continue;
				}

				if (k == 0)
				{					
					length += GetPropertyLength(useProperty[j].type, strValue, useProperty[j].detail);
				}
				else
				{
					if (useProperty[j].type == "std::vector")
					{
						int _size = sizeof(unsigned long);
						int _temp = vecIndex.size();
						ofile.write((const char*)&_temp, _size);
						for (int k = 0; k < vecIndex.size(); ++k)
						{
							switch (sheet->cellType(i-1, vecIndex[k]-1))
							{
							case libxl::CELLTYPE_NUMBER:
								iNum = sheet->readNum(i-1, vecIndex[k]-1);
								iNum = ConfigRound(iNum);
								strValue = ConfigvalueToString(iNum).c_str();
								break;
							case libxl::CELLTYPE_STRING:
								strValue = sheet->readStr(i-1, vecIndex[k]-1);
								break;
							default:
								strValue = "";
								break;
							}
							GenType(useProperty[j].detail, strValue);
						}
					}
					else
					{
						GenType(useProperty[j].type, strValue);
					}
				}
			}

			if (_endFlag)
			{
				break;
			}

			if (k == 0)
			{
				ofile.write((char*)&length, sizeof(unsigned long));
			}
		}	
		if (_endFlag)
		{
			break;
		}
	}

	ofile.close();
}

void Design::ConfigInitializationBar(int iRow, int i, CProgressBarDlg* pBar)
{
	if (m_bIsAllExport)
	{
		if (m_bBeginProgress)
		{
			pBar->InitializationProgress(iRow);
			m_bBeginProgress = false;
		}
		else
		{
			pBar->StepProgress(i);
		}
	}
}

void Design::testFunc()
{
	ifstream ifile("c://MapConfig.dat", ios::in|ios::binary);

	int _size = sizeof(unsigned long);
	unsigned long a = 0;
	ifile.read((char*)&a, _size);
	ifile.seekg (_size, ios::cur); 

}

std::string Design::ConfigvalueToString(double value)
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
double Design::ConfigRound(double value)
{
	return (value>=0.0) ? floor(value+0.5) : ceil(value-0.5);
}
