#include "stdafx.h"
#include "Design.h"

extern CString fileDir;
extern CString saveDir;

void Design::AnalysisOneConfig(IllusionExcelFile& excl, CString _name)
{
	CString fileName;
	fileName.Format("%s/design.xls", fileDir);
	excl.OpenExcelFile(fileName);

	bool bLoad = excl.LoadSheet(3);
	int nRow = excl.GetRowCount();
	int nCol = excl.GetColumnCount();

	bool _skipFlag = false;
	bool _complete = false;

	for (int i = 1; i<= nRow; ++i)
	{
		if (_skipFlag)
		{
			CString strValue = excl.GetCellString(i, 2);
			if (strValue == "")
				_skipFlag = false;
			continue;
		}

		for (int j = 1; j<= nCol; ++j)
		{
			CString strValue = excl.GetCellString(i, j);
			if (strValue != "")
			{
				if (j == 1)
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
						if (j == 2)
							nowProperty.name = strValue;
						else if (j == 3)
							nowProperty.SetType(strValue);
						else if (j == 4)
							nowProperty.SetDetail(strValue);
						else if (j == 7 && strValue == "c")
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
	excl.CloseExcelFile();
}