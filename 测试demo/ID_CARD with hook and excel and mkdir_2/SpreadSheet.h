/////////////////////////////////////////////////////////////////////////
// 类名：CSpreadSheet
// 功能：读、写Excel文件或指定分隔符分隔的文本文件类
// 附注：导入、导出指定数据的Excel文件或分隔符文本文件
// 修改：徐景周(jingzhou_xu@163.com)
// 组织：Future Studio
// 日期：2003.1.8
////////////////////////////////////////////////////////////////////////
#ifndef CSPREADSHEET_H
#define CSPREADSHEET_H

#include <odbcinst.h>
#include <afxdb.h>

class CSpreadSheet
{
public:
	CSpreadSheet(CString File, CString SheetOrSeparator, bool Backup = false);			// 为进行读写操作，进行的预处理工作
	~CSpreadSheet();																	// 清理工作
	bool AddHeaders(CStringArray &FieldNames, bool replace = false);					// 添加首行列头
	bool DeleteSheet();																	// 删除分隔符文本文件内容
	bool DeleteSheet(CString SheetName);												// 删除指定表格全部内容，但表格自身不被删除
	bool AddRow(CStringArray &RowValues, long row = 0, bool replace = false);			// 播放或替换一行
	bool AddCell(CString CellValue, CString column, long row = 0, bool Auto = true);	// 使用行号或字母列号替换或添加一单元格
	bool AddCell(CString CellValue, short column, long row = 0);						// 使用行、列号替换或添加一单元格
	bool ReplaceRows(CStringArray &NewRowValues, CStringArray &OldRowValues);			// 在Excel表格中替换行
	bool ReadRow(CStringArray &RowValues, long row = 0);								// 读取一行
	bool ReadColumn(CStringArray &ColumnValues, CString column, bool Auto = true);		// 使用行号、字母列号读取一列
	bool ReadColumn(CStringArray &ColumnValues, short column);							// 使用列号读取一列
	bool ReadCell (CString &CellValue, CString column, long row = 0, bool Auto = true); // 使用行号、字母列号读取单元格
	bool ReadCell (CString &CellValue, short column, long row = 0);						// 使用列号读取单元格
	void BeginTransaction();															// 开始事务
	bool Commit();																		// 保存改变状态
	bool RollBack();																	// 回滚改变状态
	bool Convert(CString SheetOrSeparator);
																						// 获取首行列头名
	inline void GetFieldNames (CStringArray &FieldNames) {FieldNames.RemoveAll(); FieldNames.Copy(m_aFieldNames);} 
	inline long GetTotalRows() {return m_dTotalRows;}									// 获取总行数
	inline short GetTotalColumns() {return m_dTotalColumns;}							// 获取总列数
	inline long GetCurrentRow() {return m_dCurrentRow;}									// 获取当前选中行
	inline bool GetBackupStatus() {return m_bBackup;}									// 获取备份状态. True表示备份, False不进行备份
	inline bool GetTransactionStatus() {return m_bTransaction;}							// 获取事务状态. True表示开始, False表示没有开始或开始时产生错误
	inline CString GetLastError() {return m_sLastError;}								// 获取最后错误信息

private:
	bool Open();																		// 为进行读写打开处理
	void GetExcelDriver();																// 获取Excel-ODBC驱动程序
	short CalculateColumnNumber(CString column, bool Auto);								// 转换Excel字母列号为对应数字列号

	bool	m_bAppend;			// 新建表格还是使用原表格内部标志
	bool	m_bBackup;			// 备份状态内部标志
	bool	m_bExcel;			// 是Excel表格文件还是分隔符文本文件内部标志
	bool	m_bTransaction;		// 事务状态内部标志

	long	m_dCurrentRow;		// 当前行号索引, 起始为1
	long	m_dTotalRows;		// 总行数
	short	m_dTotalColumns;	// Excel文件时总列数，分隔符文本文件中最大列数

	CString m_sSql;				// 打开Excel进行读写SQL语句
	CString m_sDsn;				// 打开Excel进行读写的DSN名
	CString m_stempSql;			// 临时SQL字符串
	CString m_stempString;		// 临时字符串
	CString m_sSheetName;		// Excel表格名
	CString m_sExcelDriver;		// Excel驱动程序名
	CString m_sFile;			// 文件名
	CString m_sSeparator;		// 文本文件分隔符
	CString m_sLastError;		// 错误信息

	CStringArray m_atempArray;	// 临时数组
	CStringArray m_aFieldNames; // 字段数组
	CStringArray m_aRows;		// 行存储

	CDatabase	*m_Database;	// 数据库变量
	CRecordset	*m_rSheet;		// 记录集变量
};

// 为读写进行打开处理(File -- 文件名，SheetOrSeparator -- Excel表名或文本分隔符，Backup -- 是否创建备份表)
CSpreadSheet::CSpreadSheet(CString File, CString SheetOrSeparator, bool Backup /* = false */) :
m_Database(NULL), m_rSheet(NULL), m_sFile(File),
m_dTotalRows(0), m_dTotalColumns(0), m_dCurrentRow(1),
m_bAppend(false), m_bBackup(Backup), m_bTransaction(false)
{
	// 检测文件是Excel表格还是分隔符文本文件
	m_stempString		= m_sFile.Right(4);
	m_stempString.MakeLower();
	if (m_stempString == ".xls") // 当是Excel表格文件时
	{
		m_bExcel		= true;
		m_sSheetName	= SheetOrSeparator;
		m_sSeparator	= " ,;.?";
	}
	else						// 当是分隔符文本文件时
	{
		m_bExcel		= false;
		m_sSeparator	= SheetOrSeparator;
	}

	// 当文件是Excel文件时
	if (m_bExcel) 
	{
		m_Database = new CDatabase;
		GetExcelDriver();
		m_sDsn.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s", m_sExcelDriver, m_sFile, m_sFile);

		if (Open())				// 是否已存在Excel文件及表可以打开
		{
			if (m_bBackup)		// Excel中表存在并可以打开的话，是否做原始备份表
			{
				if ((m_bBackup) && (m_bAppend))
				{
					CString tempSheetName	= m_sSheetName;
					m_sSheetName			= m_sSheetName + "备份";
					m_bAppend				= false;

					// 在此创建备份表
					if (!Commit())
					{
						m_bBackup			= false;
					}
					m_bAppend				= true;
					m_sSheetName			= tempSheetName;
					m_dCurrentRow			= 1;
				}
			}
		}
	}
	else // 当文件是指定分隔符分隔的文本文件时
	{
		if (Open())
		{
			if ((m_bBackup) && (m_bAppend))
			{
				m_stempString	= m_sFile;
				m_stempSql.Format("%s.bak", m_sFile);
				m_sFile			= m_stempSql;
				if (!Commit())
				{
					m_bBackup	= false;
				}
				m_sFile			= m_stempString;
			}
		}
	}
}

// 清理工作
CSpreadSheet::~CSpreadSheet()
{
	if (NULL != m_Database)
	{
		m_Database->Close();
		delete m_Database;
	}
}

// 添加首行列头到表格中
bool CSpreadSheet::AddHeaders(CStringArray &FieldNames, bool replace)
{
	if (m_bAppend)		// 原表格后追加
	{
		if (replace)	// 替换首行而不是添加新列
		{
			if (!AddRow(FieldNames, 1, true))
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		if (ReadRow(m_atempArray, 1)) // 添加新列
		{
			if (m_bExcel)
			{
				// 检查首行列头字段是否重复
				for (int i = 0; i < FieldNames.GetSize(); i++)
				{
					for (int j = 0; j < m_atempArray.GetSize(); j++)
					{
						if (FieldNames.GetAt(i) == m_atempArray.GetAt(j))
						{
							m_sLastError.Format("首行列头字段重复:%s\n", FieldNames.GetAt(i));
							return false;
						}
					}
				}	
			}

			m_atempArray.Append(FieldNames);
			if (!AddRow(m_atempArray, 1, true))
			{
				m_sLastError = "添加列头时产生错误\n";
				return false;
			}

			// 更新总列数
			if (m_atempArray.GetSize() > m_dTotalColumns)
			{
				m_dTotalColumns = m_atempArray.GetSize();
			}
			return true;
		}
		return false;				
	}
	else // 新表格
	{
		m_dTotalColumns = FieldNames.GetSize();
		if (!AddRow(FieldNames, 1, true))
		{
			return false;
		}
		else
		{
			m_dTotalRows = 1;
			return true;
		}
	}
}

// 删除分隔符文本文件内容
bool CSpreadSheet::DeleteSheet()
{
	if (m_bExcel)
	{
		if (DeleteSheet(m_sSheetName))
		{
			return true;
		}
		else
		{
			m_sLastError = "删除表格时产生错误\n";
			return false;
		}
	}
	else
	{
		m_aRows.RemoveAll();
		m_aFieldNames.RemoveAll();
		m_dTotalColumns = 0;
		m_dTotalRows = 0;
		if (!m_bTransaction)
		{
			Commit();			
		}
		m_bAppend = false; // 设置新表格标志

		return true;		
	}
}

// 删除指定Excel表格内容，表格自身不被删除
bool CSpreadSheet::DeleteSheet(CString SheetName)
{
	if (m_bExcel)	// 当是Excel表格时
	{
		// 删除表格
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);
		SheetName = "[" + SheetName + "$A1:IV65536]";
		m_stempSql.Format ("DROP TABLE %s", SheetName);
		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			m_Database->Close();
			m_aRows.RemoveAll();
			m_aFieldNames.RemoveAll();
			m_dTotalColumns = 0;
			m_dTotalRows = 0;
		}
		catch(CDBException *pEx)
		{
			m_sLastError = pEx->m_strError;
			m_Database->Close();
			pEx->Delete();

			return false;
		}
		return true;
	}
	else			// 当是分隔符文本文件时
	{
		return DeleteSheet();
	}
}

// 播放或替换一行到表格中，默认为添加一新行 
bool CSpreadSheet::AddRow(CStringArray &RowValues, long row, bool replace)
{
	long tempRow;
	
	if (row == 1)
	{
		if (m_bExcel) 
		{
			// 检查Excel表格首行列头字段是否重复
			for (int i = 0; i < RowValues.GetSize(); i++)
			{
				for (int j = 0; j < RowValues.GetSize(); j++)
				{
					if ((i != j) && (RowValues.GetAt(i) == RowValues.GetAt(j)))
					{
						m_sLastError.Format("首行列头字段重复:%s\n", RowValues.GetAt(i));
						return false;
					}
				}
			}
			
			// 检查首行列头数是否减小
			if (RowValues.GetSize() < m_dTotalColumns)
			{
				m_sLastError = "新列头数不能小于原列头数";
				return false;
			}
			m_dTotalColumns = RowValues.GetSize();
		}

		// 更新首行(列头)
		m_aFieldNames.RemoveAll();
		m_aFieldNames.Copy(RowValues);
	}
	else
	{
		if (m_bExcel)
		{
			if (m_dTotalColumns == 0)
			{
				m_sLastError = "没有列头，首先要加入列头\n";
				return false;
			}
		}
	}

	if (m_bExcel)	// Excel表格文件时
	{
		if (RowValues.GetSize() > m_aFieldNames.GetSize())
		{
			m_sLastError = "列数大于表格中总列数\n";
			return false;
		}
	}
	else			// 分隔符文本文件时
	{
		// 更新最大列数
		if (RowValues.GetSize() > m_dTotalColumns)
		{
			m_dTotalColumns = RowValues.GetSize();
		}
	}

	// 转换行值
	m_stempString.Empty();
	for (int i = 0; i < RowValues.GetSize(); i++)
	{
		if (i != RowValues.GetSize()-1) // 不是最后一列
		{
			m_stempSql.Format("\"%s\"%s", RowValues.GetAt(i), m_sSeparator);
			m_stempString += m_stempSql;
		}
		else							// 最后一列
		{
			m_stempSql.Format("\"%s\"", RowValues.GetAt(i));
			m_stempString += m_stempSql;
		}
	}
	
	if (row)
	{
		if (row <= m_dTotalRows)	// 不用添加新行
		{
			if (replace)			// 替换行
			{
				m_aRows.SetAt(row-1, m_stempString);
			}
			else					// 插入行
			{
				m_aRows.InsertAt(row-1, m_stempString);
				m_dTotalRows++;
			}

			if (!m_bTransaction)
			{
				Commit();
			}
			return true;
		}
		else						// 添加新行
		{
			// 插入空行直到指定行号
			m_dCurrentRow = m_dTotalRows;
			m_stempSql.Empty();
			CString nullString;
			for (int i = 1; i <= m_dTotalColumns; i++)
			{
				if (i != m_dTotalColumns)
				{
					if (m_bExcel)
					{
						nullString.Format("\" \"%s", m_sSeparator);
					}
					else
					{
						nullString.Format("\"\"%s", m_sSeparator);
					}
					m_stempSql += nullString;
				}
				else
				{
					if (m_bExcel)
					{
						m_stempSql += "\" \"";
					}
					else
					{
						m_stempSql += "\"\"";
					}
				}
			}
			for (int j = m_dTotalRows + 1; j < row; j++)
			{
				m_dCurrentRow++;
				m_aRows.Add(m_stempSql);
			}
		}
	}
	else
	{
		tempRow = m_dCurrentRow;
		m_dCurrentRow = m_dTotalRows;
	}

	// 插入一新行
	m_dCurrentRow++;
	m_aRows.Add(m_stempString);
	
	if (row > m_dTotalRows)
	{
		m_dTotalRows	= row;
	}
	else if (!row)
	{
		m_dTotalRows	= m_dCurrentRow;
		m_dCurrentRow	= tempRow;
	}
	if (!m_bTransaction)
	{
		Commit();
	}

	return true;
}

// 使用行号、字母列号替换或添加一单元格到Excel表格中，默认为添加单元格到一新行中，
// 如果你想使用字母列号作为列头名可将Auto置为false
bool CSpreadSheet::AddCell(CString CellValue, CString column, long row, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (AddCell(CellValue, columnIndex, row))
	{
		return true;
	}

	return false;
}

// 使用数字行号、列号替换或添加一个单元格到表格中，默认为添加单元格到一新行
bool CSpreadSheet::AddCell(CString CellValue, short column, long row)
{
	if (0 == column)
	{
		m_sLastError = "列数不能为0\n";
		return false;
	}

	long tempRow;

	if (m_bExcel)	// 当是Excel表格文件时
	{
		if (column > m_aFieldNames.GetSize() + 1)
		{
			m_sLastError = "指定列号大于表格中存在的总列数\n";
			return false;
		}
	}
	else			// 当是分隔符文本文件时
	{
		// 更新最大列数
		if (column > m_dTotalColumns)
		{
			m_dTotalColumns = column;
		}
	}

	if (row)
	{
		if (row <= m_dTotalRows)
		{
			ReadRow(m_atempArray, row);
	
			// 改变指定行
			m_atempArray.SetAtGrow(column-1, CellValue);

			if (row == 1)
			{
				if (m_bExcel) // 检查列头字段是否重复
				{										
					for (int i = 0; i < m_atempArray.GetSize(); i++)
					{
						for (int j = 0; j < m_atempArray.GetSize(); j++)
						{
							if ((i != j) && (m_atempArray.GetAt(i) == m_atempArray.GetAt(j)))
							{
								m_sLastError.Format("首行字段重复(列头):%s\n", m_atempArray.GetAt(i));
								return false;
							}
						}
					}
				}

				// 更新首行(列头)
				m_aFieldNames.RemoveAll();
				m_aFieldNames.Copy(m_atempArray);
			}	

			if (!AddRow(m_atempArray, row, true))
			{
				return false;
			}

			if (!m_bTransaction)
			{
				Commit();
			}
			return true;
		}
		else
		{
			// 插入空行直到指定行号
			m_dCurrentRow = m_dTotalRows;
			m_stempSql.Empty();
			CString nullString;
			for (int i = 1; i <= m_dTotalColumns; i++)
			{
				if (i != m_dTotalColumns)
				{
					if (m_bExcel)
					{
						nullString.Format("\" \"%s", m_sSeparator);
					}
					else
					{
						nullString.Format("\"\"%s", m_sSeparator);
					}
					m_stempSql		+= nullString;
				}
				else
				{
					if (m_bExcel)
					{
						m_stempSql	+= "\" \"";
					}
					else
					{
						m_stempSql	+= "\"\"";
					}
				}
			}
			for (int j = m_dTotalRows + 1; j < row; j++)
			{
				m_dCurrentRow++;
				m_aRows.Add(m_stempSql);
			}
		}
	}
	else
	{
		tempRow = m_dCurrentRow;
		m_dCurrentRow = m_dTotalRows;
	}

	// 插入单元格
	m_dCurrentRow++;
	m_stempString.Empty();
	for (int j = 1; j <= m_dTotalColumns; j++)
	{
		if (j != m_dTotalColumns) // 没有最后一列
		{
			if (j != column)
			{
				if (m_bExcel)
				{
					m_stempSql.Format("\" \"%s", m_sSeparator);
				}
				else
				{
					m_stempSql.Format("\"\"%s", m_sSeparator);
				}
				m_stempString += m_stempSql;
			}
			else
			{
				m_stempSql.Format("\"%s\"%s", CellValue, m_sSeparator);
				m_stempString += m_stempSql;
			}
		}
		else					// 最后一列
		{
			if (j != column)
			{
				if (m_bExcel)
				{
					m_stempString += "\" \"";
				}
				else
				{
					m_stempString += "\"\"";
				}
			}
			else
			{
				m_stempSql.Format("\"%s\"", CellValue);
				m_stempString += m_stempSql;
			}
		}
	}	

	m_aRows.Add(m_stempString);
	
	if (row > m_dTotalRows)
	{
		m_dTotalRows	= row;
	}
	else if (!row)
	{
		m_dTotalRows	= m_dCurrentRow;
		m_dCurrentRow	= tempRow;
	}
	if (!m_bTransaction)
	{
		Commit();
	}
	return true;
}

// 检索和替换Excel表格中行数据
bool CSpreadSheet::ReplaceRows(CStringArray &NewRowValues, CStringArray &OldRowValues)
{
	if (m_bExcel) // 当是Excel表格文件时
	{
		// 打开或创建Excel文件
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);
		m_stempSql.Format("UPDATE [%s] SET ", m_sSheetName);
		for (int i = 0; i < NewRowValues.GetSize(); i++)
		{
			m_stempString.Format("[%s]='%s', ", m_aFieldNames.GetAt(i), NewRowValues.GetAt(i));
			m_stempSql = m_stempSql + m_stempString;
		}
		m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
		m_stempSql = m_stempSql + " WHERE (";
		for (int j = 0; j < OldRowValues.GetSize()-1; j++)
		{
			m_stempString.Format("[%s]='%s' AND ", m_aFieldNames.GetAt(j), OldRowValues.GetAt(j));
			m_stempSql = m_stempSql + m_stempString;
		}
		m_stempSql.Delete(m_stempSql.GetLength()-4, 5);
		m_stempSql += ")";

		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			m_Database->Close();
			Open();
			return true;
		}
		catch(CDBException *pEx)
		{
			m_sLastError = pEx->m_strError;
			m_Database->Close();
			pEx->Delete();
			return false;
		}
	}
	else		// 当是分隔符的文本文件时
	{
		m_sLastError = "这个涵数对分隔符文本文件无效\n";
		return false;
	}
}

// 读取表格中一行，默认为读取下一行
bool CSpreadSheet::ReadRow(CStringArray &RowValues, long row)
{
	// 检查指定行号是否大于表格中总行数
	if (row <= m_aRows.GetSize())
	{
		if (0 != row)
		{
			m_dCurrentRow = row;
		}
		else if (m_dCurrentRow > m_aRows.GetSize())
		{
			return false;
		}

		// 读取指定行
		RowValues.RemoveAll();
		m_stempString = m_aRows.GetAt(m_dCurrentRow-1);
		m_dCurrentRow++;

		// 检索分隔行的分隔符
		int separatorPosition;
		m_stempSql.Format("\"%s\"", m_sSeparator);
		separatorPosition = m_stempString.Find(m_stempSql); // 如果分隔符是字符"?"
		if (separatorPosition != -1)
		{
			// 保存列
			int nCount = 0;
			int stringStartingPosition = 0;
			while (separatorPosition != -1)
			{
				nCount = separatorPosition - stringStartingPosition;
				RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
				stringStartingPosition = separatorPosition + m_stempSql.GetLength();
				separatorPosition = m_stempString.Find(m_stempSql, stringStartingPosition);
			}
			nCount = m_stempString.GetLength() - stringStartingPosition;
			RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));

			// 删除第一列引用符号
			m_stempString = RowValues.GetAt(0);
			m_stempString.Delete(0, 1);
			RowValues.SetAt(0, m_stempString);
			
			// 删除最后列引用符号
			m_stempString = RowValues.GetAt(RowValues.GetSize()-1);
			m_stempString.Delete(m_stempString.GetLength()-1, 1);
			RowValues.SetAt(RowValues.GetSize()-1, m_stempString);

			return true;
		}
		else
		{
			// 保存列
			separatorPosition = m_stempString.Find(m_sSeparator); // 当分隔符是字符"?"
			if (separatorPosition != -1)
			{
				int nCount = 0;
				int stringStartingPosition = 0;
				while (separatorPosition != -1)
				{
					nCount = separatorPosition - stringStartingPosition;
					RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
					stringStartingPosition = separatorPosition + m_sSeparator.GetLength();
					separatorPosition = m_stempString.Find(m_sSeparator, stringStartingPosition);
				}
				nCount = m_stempString.GetLength() - stringStartingPosition;
				RowValues.Add(m_stempString.Mid(stringStartingPosition, nCount));
				return true;
			}
			else	// 表格只有一列时
			{
				// 如果存在在，删除开始和结束时的引用符号
				int quoteBegPos = m_stempString.Find('\"');
				int quoteEndPos = m_stempString.ReverseFind('\"');
				if ((quoteBegPos == 0) && (quoteEndPos == m_stempString.GetLength()-1))
				{
					m_stempString.Delete(0, 1);
					m_stempString.Delete(m_stempString.GetLength()-1, 1);
				}

				RowValues.Add(m_stempString);
			}
		}
	}

	m_sLastError = "指定行大于表格中总行数\n";

	return false;
}

// 使用字母列号从Excel表格中读取一列，如果想将字母列作为列号的话将Auto置为false
bool CSpreadSheet::ReadColumn(CStringArray &ColumnValues, CString column, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (ReadColumn(ColumnValues, columnIndex))
	{
		return true;
	}
	return false;
}

// 使用数字列号从表格中读取一列
bool CSpreadSheet::ReadColumn(CStringArray &ColumnValues, short column)
{
	if (0 == column)
	{
		m_sLastError = "列数不能为0\n";
		return false;
	}

	int tempRow = m_dCurrentRow;
	m_dCurrentRow = 1;
	ColumnValues.RemoveAll();
	for (int i = 1; i <= m_aRows.GetSize(); i++)
	{
		// 读取每一行
		if (ReadRow(m_atempArray, i))
		{
			// 在指定列中获取单元格内容
			if (column <= m_atempArray.GetSize())
			{
				ColumnValues.Add(m_atempArray.GetAt(column-1));
			}
			else
			{
				ColumnValues.Add("");
			}
		}
		else
		{
			m_dCurrentRow = tempRow;
			m_sLastError = "读取行时产生错误\n";
			return false;
		}
	}
	m_dCurrentRow = tempRow;
	return true;
}

// 从Excel表格中使用首行(列头)、字母列号读取单元格内容，默认为在下一行中读取下一个单元格内容
// 如果你想将字母列作为列头名的话可将Auto置为false 
bool CSpreadSheet::ReadCell (CString &CellValue, CString column, long row, bool Auto)
{
	short columnIndex = CalculateColumnNumber(column, Auto);
	if (0 == columnIndex)
	{
		return false;
	}

	if (ReadCell(CellValue, columnIndex, row))
	{
		return true;
	}
	return false;
}

// 在表格文件中使用行、列号读取单元格内容，默认(row无效)为下一行中读取下一个单元格
bool CSpreadSheet::ReadCell (CString &CellValue, short column, long row)
{
	if (0 == column)
	{
		m_sLastError		= "列不能为0\n";
		return false;
	}

	int tempRow				= m_dCurrentRow;
	if (row)
	{
		m_dCurrentRow		= row;
	}
	if (ReadRow(m_atempArray, m_dCurrentRow))
	{
		// 获取指定列中单元格数据
		if (column <= m_atempArray.GetSize())
		{
			CellValue		= m_atempArray.GetAt(column-1);
		}
		else
		{
			CellValue.Empty();
			m_dCurrentRow	= tempRow;
			return false;
		}
		m_dCurrentRow		= tempRow;
		return true;
	}
	m_dCurrentRow			= tempRow;
	m_sLastError			= "读取行时产生错误\n";

	return false;
}

// 事务开始
void CSpreadSheet::BeginTransaction()
{
	m_bTransaction = true;
}

// 提交改变的数据到表格或文本文件中，在此创建Excel中表
bool CSpreadSheet::Commit()
{
	if (m_bExcel) // 当是Excel表格文件时
	{
		// 打开或创建Excel文件
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);

		if (m_bAppend)
		{
			// 如果已经存在表格，则删除它
			m_stempString= "[" + m_sSheetName + "$A1:IV65536]";
			m_stempSql.Format ("DROP TABLE %s", m_stempString);
			try
			{
				m_Database->ExecuteSQL(m_stempSql);
			}
			catch(CDBException *pEx)
			{
				m_sLastError = pEx->m_strError;
				m_Database->Close();
				pEx->Delete();
				return false;
			}
			
			// 创建一个新的表格
			m_stempSql.Format("CREATE TABLE [%s$A1:IV65536] (", m_sSheetName);
			for (int j = 0; j < m_aFieldNames.GetSize(); j++)
			{
				m_stempSql = m_stempSql + "[" + m_aFieldNames.GetAt(j) +"]" + " char(255), ";
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";
		}
		else
		{
			// 创建一个新的表格
			m_stempSql.Format("CREATE TABLE [%s] (", m_sSheetName);
			for (int i = 0; i < m_aFieldNames.GetSize(); i++)
			{
				m_stempSql = m_stempSql + "[" + m_aFieldNames.GetAt(i) +"]" + " char(255), ";
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";
		}

		try
		{
			m_Database->ExecuteSQL(m_stempSql);
			if (!m_bAppend)
			{
				m_dTotalColumns = m_aFieldNames.GetSize();
				m_bAppend		= true;
			}
		}
		catch(CDBException *pEx)
		{
			m_sLastError		= pEx->m_strError;
			m_Database->Close();
			pEx->Delete();

			return false;
		}

		// 保存已改变的数据
		for (int k = 1; k < m_dTotalRows; k++)
		{
			ReadRow(m_atempArray, k+1);

			// 创建插入行SQL语句
			m_stempSql.Format("INSERT INTO [%s$A1:IV%d] (", m_sSheetName, k);
			for (int i = 0; i < m_atempArray.GetSize(); i++)
			{
				m_stempString.Format("[%s], ", m_aFieldNames.GetAt(i));
				m_stempSql = m_stempSql + m_stempString;
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ") VALUES (";
			for (int j = 0; j < m_atempArray.GetSize(); j++)
			{
				m_stempString.Format("'%s', ", m_atempArray.GetAt(j));
				m_stempSql = m_stempSql + m_stempString;
			}
			m_stempSql.Delete(m_stempSql.GetLength()-2, 2);
			m_stempSql += ")";

			// 插入行
			try
			{
				m_Database->ExecuteSQL(m_stempSql);
			}
			catch(CDBException *pEx)
			{
				m_sLastError = pEx->m_strError;
				m_Database->Close();
				pEx->Delete();
				return false;
			}
		}
		m_Database->Close();
		m_bTransaction = false;
		return true;
	}
	else // 当文件是分隔符分隔的文本文件时
	{
		try
		{
			CFile *File = NULL;
			File = new CFile(m_sFile, CFile::modeCreate | CFile::modeWrite  | CFile::shareDenyNone);
			if (File != NULL)
			{
				CArchive *Archive = NULL;
				Archive = new CArchive(File, CArchive::store);
				if (Archive != NULL)
				{
					for (int i = 0; i < m_aRows.GetSize(); i++)
					{
						Archive->WriteString(m_aRows.GetAt(i));
						Archive->WriteString("\r\n");
					}
					delete Archive;
					delete File;
					m_bTransaction = false;
					return true;
				}
				delete File;
			}
		}
		catch(...)
		{
		}
		m_sLastError = "写文件时产生错误\n";
		return false;
	}
}

// 回滚文件改变为改变前状态
bool CSpreadSheet::RollBack()
{
	if (Open())
	{
		m_bTransaction = false;
		return true;
	}

	m_sLastError = "在回滚先前状态时产生错误\n";

	return false;
}

// 转换为指定分隔符的文本或表格文件
bool CSpreadSheet::Convert(CString SheetOrSeparator)
{
	// 文件名
	m_stempString = m_sFile;
	m_stempString.Delete(m_stempString.GetLength()-4, 4);
	if (m_bExcel) // 当文件是Excel文件时
	{
		m_stempString += ".csv";
		CSpreadSheet tempSheet(m_stempString, SheetOrSeparator, false);
		
		// 如果指定文本文件已存在，存不转换直接返回
		if (0 != tempSheet.GetTotalColumns())
		{
			return false;
		}

		tempSheet.BeginTransaction();

		for (int i = 1; i <= m_dTotalRows; i++)
		{
			if (!ReadRow(m_atempArray, i))
			{
				return false;
			}
			if (!tempSheet.AddRow(m_atempArray, i))
			{
				return false;
			}
		}
		if (!tempSheet.Commit())
		{
			return false;
		}
		return true;
	}
	else		// 当文件是分隔符分隔的文本文件时
	{
		m_stempString += ".xls";
		CSpreadSheet tempSheet(m_stempString, SheetOrSeparator, false);

		// 如果指定Excel文件已存在，则直接返回
		if (0 != tempSheet.GetTotalColumns())
		{
			return false;
		}

		GetFieldNames(m_atempArray);

		// 检查首行(列头)字段是否重复
		bool duplicate = false;
		for (int i = 0; i < m_atempArray.GetSize(); i++)
		{
			for (int j = 0; j < m_atempArray.GetSize(); j++)
			{
				if ((i != j) && (m_atempArray.GetAt(i) == m_atempArray.GetAt(j)))
				{
					m_sLastError.Format("首行(列头)字段重复:%s\n", m_atempArray.GetAt(i));
					duplicate = true;
				}
			}
		}

		if (duplicate) // 重复时创建哑元首行(列头)
		{
			m_atempArray.RemoveAll();
			for (int k = 1; k <= m_dTotalColumns; k++)
			{
				m_stempString.Format("%d", k);
				m_atempArray.Add(m_stempString);
			}

			if (!tempSheet.AddHeaders(m_atempArray))
			{
				return false;
			}

			for (int l = 1; l <= m_dTotalRows; l++)
			{
				if (!ReadRow(m_atempArray, l))
				{
					return false;
				}
				if (!tempSheet.AddRow(m_atempArray, l+1))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			if (!tempSheet.AddHeaders(m_atempArray))
			{
				return false;
			}

			for (int l = 2; l <= m_dTotalRows; l++)
			{
				if (!ReadRow(m_atempArray, l))
				{
					return false;
				}
				if (!tempSheet.AddRow(m_atempArray, l))
				{
					return false;
				}
			}
			return true;
		}
	}
}

// 为进行读写打开Excel或分隔符分隔文本文件
bool CSpreadSheet::Open()
{
	if (m_bExcel)	// 当文件是Excel电子表格文件时
	{
		// 打开或创建Excel文件
		m_Database->OpenEx(m_sDsn, CDatabase::noOdbcDialog);

		// 创建记录集并查询表
		m_rSheet = new CRecordset( m_Database );
		m_sSql.Format("SELECT * FROM [%s$A1:IV65536]", m_sSheetName);
		try
		{
			// 查询表
			m_rSheet->Open(CRecordset::forwardOnly, m_sSql, CRecordset::readOnly);
		}
		catch(...)
		{
			// 表不存在
			delete m_rSheet;
			m_rSheet = NULL;
			m_Database->Close();
			return false;
		}

		// 得到列数
		m_dTotalColumns = m_rSheet->m_nResultCols;

		if (m_dTotalColumns != 0)
		{
			m_aRows.RemoveAll();
			m_stempString.Empty();
			m_bAppend = true;
			m_dTotalRows++;					// 总行数
			
			// 获取首行(列头)字段名
			for (int i = 0; i < m_dTotalColumns; i++)
			{
				m_stempSql = m_rSheet->m_rgODBCFieldInfos[i].m_strName;
				m_aFieldNames.Add(m_stempSql);

				// 将所有列合并到一个字符串中
				if (i != m_dTotalColumns-1) // 不是最后一列
				{
					m_stempString = m_stempString + "\"" + m_stempSql + "\"" + m_sSeparator;
				}
				else						// 最后一列
				{	
					m_stempString = m_stempString + "\"" + m_stempSql + "\"";
				}				
			}
			
			// 存储内存中首行(列头)
			m_aRows.Add(m_stempString);

			// 读取并存储内存中其它行
			while (!m_rSheet->IsEOF())
			{
				m_dTotalRows++;							// 总行数

				try
				{
					// 获取一行中所有列
					m_stempString.Empty();
					for (short column = 0; column < m_dTotalColumns; column++)
					{
						m_rSheet->GetFieldValue(column, m_stempSql);

						// 将所有列合并到一个字符串中
						if (column != m_dTotalColumns-1) // 不是最后列时
						{
							m_stempString = m_stempString + "\"" + m_stempSql + "\"" + m_sSeparator;
						}
						else							// 最后一列时
						{	
							m_stempString = m_stempString + "\"" + m_stempSql + "\"";
						}
					}

					// 存储内存中已包含的行
					m_aRows.Add(m_stempString);
					m_rSheet->MoveNext();
				}
				catch (...)
				{
					m_sLastError = "读取行时产生错误\n";
					delete m_rSheet;
					m_rSheet = NULL;
					m_Database->Close();

					return false;
				}
			}		
		}
		
		m_rSheet->Close();
		delete m_rSheet;
		m_rSheet = NULL;
		m_Database->Close();
		m_dCurrentRow = 1;

		return true;
	}
	else			// 当文件是指定分隔符分隔的文本文件时
	{
		try
		{
			CFile *File = NULL;
			File = new CFile(m_sFile, CFile::modeRead | CFile::shareDenyNone);
			if (File != NULL)
			{
				CArchive *Archive = NULL;
				Archive = new CArchive(File, CArchive::load);
				if (Archive != NULL)
				{
					m_aRows.RemoveAll();
					// 读取并存储内存中所有行
					while(Archive->ReadString(m_stempString))
					{
						m_aRows.Add(m_stempString);
					}
					ReadRow(m_aFieldNames, 1); // 得到首行的字段名(列头)
					delete Archive;
					delete File;

					// 得到总行数
					m_dTotalRows = m_aRows.GetSize();

					// 获取最大总列数
					for (int i = 0; i < m_aRows.GetSize(); i++)
					{
						ReadRow(m_atempArray, i);
						if (m_atempArray.GetSize() > m_dTotalColumns)
						{
							m_dTotalColumns = m_atempArray.GetSize();
						}
					}

					if (m_dTotalColumns != 0)
					{
						m_bAppend = true;
					}
					return true;
				}
				delete File;
			}
		}
		catch(...)
		{
		}

		m_sLastError = "打开文件时产生错误\n";

		return false;
	}
}

// 转换Excle中字母列号为对应数字列号
short CSpreadSheet::CalculateColumnNumber(CString column, bool Auto)
{
	if (Auto)
	{	
		column.MakeUpper();

		int firstLetter, secondLetter;
		if (1 == column.GetLength())
		{
			firstLetter = column.GetAt(0);
			return (firstLetter - 65 + 1);									// ASCII码中大写字母A为65
		}
		else if (2 == column.GetLength())
		{
			firstLetter		= column.GetAt(0);
			secondLetter	= column.GetAt(1);
			return ((firstLetter - 65 + 1)*26 + (secondLetter - 65 + 1));	// ASCII码中大写字母A为65
		}
	}

	// 检查是否是有效的字段名，有效直接返回
	for (int i = 0; i < m_aFieldNames.GetSize(); i++)
	{
		if (!column.Compare(m_aFieldNames.GetAt(i)))
		{
			return (i + 1);
		}
	}

	m_sLastError = "无效字段名或字母列号\n";

	return 0;	
}

// 获取Excel-ODBC驱动程序名字
void CSpreadSheet::GetExcelDriver()
{
	char szBuf[2001];
	WORD cbBufMax = 2000;
	WORD cbBufOut;
	char *pszBuf = szBuf;

	// 获取已安装驱动程序的名字 (需要包含头文件"odbcinst.h")
	if(!SQLGetInstalledDrivers(szBuf,cbBufMax,& cbBufOut))
	{
		m_sExcelDriver = "";
	}
	
	// 寻找Excel驱动程序...
	do
	{
		if( NULL != strstr( pszBuf, "Excel" ) )
		{
			// 找到!
			m_sExcelDriver = CString( pszBuf );
			break;
		}
		pszBuf = strchr( pszBuf, '\0' ) + 1;
	}
	while( '\0' != pszBuf[1] );
}

#endif