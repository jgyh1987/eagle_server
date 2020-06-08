#include "stdafx.h"
#include "Design.h"

extern CString fileDir;
extern CString saveDir;

void Design::AnalysisOneConfig(libxl::Book* book, CString _name)
{
	CString fileName;
	fileName.Format("%s/design.xls", fileDir);
	if(!book->load(fileName))
	{
		AfxMessageBox("加载文件初始化失败!");
		return;
	}

	libxl::Sheet* sheet = book->getSheet(2);
	int nRow = sheet->lastRow();
	int nCol = sheet->lastCol();

	bool _skipFlag = false;
	bool _complete = false;
	CString strValue;
	double iNum = 0;
	for (int i = 0; i< nRow; ++i)
	{
		if (_skipFlag)
		{
			switch (sheet->cellType(i, 1))
			{
			case libxl::CELLTYPE_NUMBER:
				iNum = sheet->readNum(i, 1);
				iNum = Round(iNum);
				strValue.Format("%s", valueToString(iNum).c_str());
				break;
			case libxl::CELLTYPE_STRING:
				strValue = sheet->readStr(i, 1);
				break;
			default:
				strValue = "";
				break;
			}
			if (strValue == "")
				_skipFlag = false;
			continue;
		}

		for (int j = 0; j< nCol; ++j)
		{
			switch (sheet->cellType(i, j))
			{
			case libxl::CELLTYPE_NUMBER:
				iNum = sheet->readNum(i, j);
				iNum = Round(iNum);
				strValue.Format("%s", valueToString(iNum).c_str());
				break;
			case libxl::CELLTYPE_STRING:
				strValue = sheet->readStr(i, j);
				break;
			default:
				strValue = "";
				break;
			}
			if (strValue != "")
			{
				if (j == 0)
				{
					if (strValue == "name")
					{
						_nameFlag = true;
					}
					else if (strValue == "property")
					{
						_propertyFlag = true;
						nowProperty.Clear();
					}
					else if (strValue == "pk")
					{
						_complete = true;
						break;
					}
				}
				else
				{
					if (_nameFlag)
					{
						if (strValue == _name)
						{
							name = strValue;
						}
						else
						{
							_skipFlag = true;
						}
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
							ClassProperty.push_back(nowProperty);
							break;
						}
					}
				}				
			}	
		}

		if (_complete)
		{
			_propertyFlag = false;
			m_configUse.insert(map<CString, vector<PropertyBase> >::value_type(name, ClassProperty));
			ClassProperty.clear();
			name = "";
		}
	}
}