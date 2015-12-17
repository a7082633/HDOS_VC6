// DialogQueryData.cpp : implementation file
//

#include "stdafx.h"
#include "ID_CARD.h"
#include "DialogQueryData.h"
#include "excel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryData dialog


CDialogQueryData::CDialogQueryData(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogQueryData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogQueryData)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogQueryData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogQueryData)
	DDX_Control(pDX, IDC_COMBO_EXPRESSION, m_combo_exp);
	DDX_Control(pDX, IDC_LIST_DATA, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogQueryData, CDialog)
	//{{AFX_MSG_MAP(CDialogQueryData)
	ON_BN_CLICKED(IDC_BTN_SHOWALL, OnBtnShowall)
	ON_BN_CLICKED(IDC_BTN_QUERY, OnBtnQuery)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackup)
	ON_BN_CLICKED(IDC_BTN_OPENBACKUP, OnBtnOpenbackup)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogQueryData message handlers


BOOL CDialogQueryData::OnInitDialog() 
{
	CDialog::OnInitDialog();
	this->CenterWindow();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, "姓名", LVCFMT_CENTER, 60);
	m_list.InsertColumn(1, "性别", LVCFMT_CENTER, 40);
	m_list.InsertColumn(2, "民族", LVCFMT_CENTER, 40);
	m_list.InsertColumn(3, "出生日期", LVCFMT_CENTER, 90);
	m_list.InsertColumn(4, "家庭住址", LVCFMT_CENTER, 220);
	m_list.InsertColumn(5, "身份证号码", LVCFMT_CENTER,130);
	m_list.InsertColumn(6, "签发机关", LVCFMT_CENTER, 170);
	m_list.InsertColumn(7, "有效期起", LVCFMT_CENTER, 90);
	m_list.InsertColumn(8, "有效期止", LVCFMT_CENTER, 90);
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	//m_pRecordset->Open("SELECT * FROM DBID WHERE 姓名='张新新'",m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	while(!m_pRecordset->adoEOF)
	{
		name = m_pRecordset->GetCollect(_variant_t((long)1));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		sex = m_pRecordset->GetCollect(_variant_t((long)2));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		nation = m_pRecordset->GetCollect(_variant_t((long)3));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		born = m_pRecordset->GetCollect(_variant_t((long)4));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		addr = m_pRecordset->GetCollect(_variant_t((long)5));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		cardno = m_pRecordset->GetCollect(_variant_t((long)6));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		issue = m_pRecordset->GetCollect(_variant_t((long)7));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		yxq = m_pRecordset->GetCollect(_variant_t((long)8));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		jiezhi = m_pRecordset->GetCollect(_variant_t((long)9));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset->MoveNext();///移到下一条记录
	}
	isOpenBackup=false;
//	if (m_pRecordset->GetState() == adStateOpen)
//	{
//		m_pRecordset->Close();
//	}
//	if (m_pRecordset)
//	{
//		m_pRecordset.Release();
//		m_pRecordset = NULL;
//	}
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogQueryData::OnBtnShowall() 
{
	if(isOpenBackup)
	{
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///如果已经打开了连接则关闭它
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
		isOpenBackup=false;
	}
	GetDlgItem(IDC_BTN_BACKUP)->EnableWindow(TRUE);//设置按钮可用
	m_list.DeleteAllItems();
	m_pRecordset->MoveFirst();
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	while(!m_pRecordset->adoEOF)
	{
		name = m_pRecordset->GetCollect(_variant_t((long)1));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		sex = m_pRecordset->GetCollect(_variant_t((long)2));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		nation = m_pRecordset->GetCollect(_variant_t((long)3));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		born = m_pRecordset->GetCollect(_variant_t((long)4));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		addr = m_pRecordset->GetCollect(_variant_t((long)5));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		cardno = m_pRecordset->GetCollect(_variant_t((long)6));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		issue = m_pRecordset->GetCollect(_variant_t((long)7));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		yxq = m_pRecordset->GetCollect(_variant_t((long)8));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		jiezhi = m_pRecordset->GetCollect(_variant_t((long)9));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		///在DEBUG方式下的OUTPUT窗口输出记录集中的记录
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset->MoveNext();///移到下一条记录
	}
}

void CDialogQueryData::OnBtnQuery() 
{
	int i=m_combo_exp.GetCurSel();
	if(i<0)
	{
		this->MessageBox("请选择查询条件!");
		return;
	}
	m_list.DeleteAllItems();
	char sql[500]={0};
	CString sExp;
	GetDlgItemText(IDC_EDIT_EXPRESSION,sExp);
	_RecordsetPtr m_pRecordset_q;
	switch(i)
	{
	case 4:
		sprintf(sql,"select * from DBID where 姓名='%s'",sExp.GetBuffer(0));
		break;
	case 3:
		sprintf(sql,"select * from DBID where 性别='%s'",sExp.GetBuffer(0));
		break;
	case 0:
		sprintf(sql,"select * from DBID where 民族='%s'",sExp.GetBuffer(0));
		break;
	case 2:
		sprintf(sql,"select * from DBID where 身份证号码='%s'",sExp.GetBuffer(0));
		break;
	case 1:
		sprintf(sql,"select * from DBID where 签发机关='%s'",sExp.GetBuffer(0));
		break;
	}
	sExp.ReleaseBuffer();
	if(isOpenBackup)
	{
		m_pRecordset_q=m_pConnection_backup->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}else
	{
		m_pRecordset_q=m_pConnection->Execute((_bstr_t)sql,&RecordsAffected,adCmdText);
	}
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	while(!m_pRecordset_q->adoEOF)
	{
		name = m_pRecordset_q->GetCollect(_variant_t((long)1));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		sex = m_pRecordset_q->GetCollect(_variant_t((long)2));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		nation = m_pRecordset_q->GetCollect(_variant_t((long)3));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		born = m_pRecordset_q->GetCollect(_variant_t((long)4));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		addr = m_pRecordset_q->GetCollect(_variant_t((long)5));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		cardno = m_pRecordset_q->GetCollect(_variant_t((long)6));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		issue = m_pRecordset_q->GetCollect(_variant_t((long)7));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		yxq = m_pRecordset_q->GetCollect(_variant_t((long)8));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		jiezhi = m_pRecordset_q->GetCollect(_variant_t((long)9));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset_q->MoveNext();///移到下一条记录
	}
	if (m_pRecordset_q->GetState() == adStateOpen)
	{
		m_pRecordset_q->Close();
	}
	if (m_pRecordset_q)
	{
		m_pRecordset_q.Release();
		m_pRecordset_q = NULL;
	}
}

void CDialogQueryData::OnBtnExport() 
{
	BOOL isOpen = FALSE;		//是否打开(否则为保存)
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径
	CString fileName = L"test.xls";			//默认打开的文件名
	CTime tm; 
	tm=tm.GetCurrentTime();
	fileName=tm.Format("%Y-%m-%d");
	CString filter = L"文件 (*.xls)|*.xls||";	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, NULL, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
		return;
	//写excel
	COleVariant VOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	CString sValue = "";
	_Application objApp;
	_Workbook objBook;
	Workbooks objBooks;
	Worksheets objSheets;
	_Worksheet objSheet;
	Range objRange, usedRange;
	objApp.SetAlertBeforeOverwriting(FALSE);
	objApp.SetDisplayAlerts(FALSE);
	if (!objApp.CreateDispatch("Excel.Application"))
	{
			::AfxMessageBox("确认是否安装了Excel");
			return;
	}
	objBooks = objApp.GetWorkbooks();
	try
	{
		objBook = objBooks.Add(_variant_t(filePath));
	}
	catch (CException* e)
	{
		objBook = objBooks.Add(vtMissing);//找不到就新建一个
	}
	objSheets = objBook.GetWorksheets();
	objSheet = objSheets.GetItem(COleVariant((short)1));
	objRange.AttachDispatch(objSheet.GetCells(), true);
	/////////////////////////////////
	//设置表头
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(1)),COleVariant("姓名"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(2)),COleVariant("性别"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(3)),COleVariant("民族"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(4)),COleVariant("出生日期"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(5)),COleVariant("家庭住址"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(6)),COleVariant("身份证号码"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(7)),COleVariant("签发机关"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(8)),COleVariant("有效期起"));
	objRange.SetItem(COleVariant(long(1)),COleVariant(long(9)),COleVariant("有效期止"));
	int SelectedCount=m_list.GetSelectedCount();
	if(0==SelectedCount)
	{
		for(int i=0;i<m_list.GetItemCount();i++)
		{
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(1)),COleVariant(m_list.GetItemText(i,0)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(2)),COleVariant(m_list.GetItemText(i,1)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(3)),COleVariant(m_list.GetItemText(i,2)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(4)),COleVariant(m_list.GetItemText(i,3)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(5)),COleVariant(m_list.GetItemText(i,4)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(6)),COleVariant(m_list.GetItemText(i,5)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(7)),COleVariant(m_list.GetItemText(i,6)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(8)),COleVariant(m_list.GetItemText(i,7)));
			objRange.SetItem(COleVariant(long(i+1+1)),COleVariant(long(9)),COleVariant(m_list.GetItemText(i,8)));
		}
	}else
	{
		POSITION pos=m_list.GetFirstSelectedItemPosition(); 
		int nId=0,count=0;
		while(pos)
		{
			nId=(int)m_list.GetNextSelectedItem(pos); 
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(1)),COleVariant(m_list.GetItemText(nId,0)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(2)),COleVariant(m_list.GetItemText(nId,1)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(3)),COleVariant(m_list.GetItemText(nId,2)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(4)),COleVariant(m_list.GetItemText(nId,3)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(5)),COleVariant(m_list.GetItemText(nId,4)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(6)),COleVariant(m_list.GetItemText(nId,5)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(7)),COleVariant(m_list.GetItemText(nId,6)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(8)),COleVariant(m_list.GetItemText(nId,7)));
			objRange.SetItem(COleVariant(long(count+1+1)),COleVariant(long(9)),COleVariant(m_list.GetItemText(nId,8)));
			count++;
		}
	}
	objRange.AttachDispatch(objSheet.GetColumns(),true);
	//设置列的列宽  
	Range cols;
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)4),VOptional).pdispVal,TRUE);
	//cols.AttachDispatch(objSheet.GetUsedRange());
	//cols=objSheet.GetRange(COleVariant("A1"),COleVariant("A1"));
	cols.SetColumnWidth(COleVariant((long)15)); //设置列宽
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //左对齐
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)5),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)25)); //设置列宽
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)6),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)30)); //设置列宽
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)7),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)30)); //设置列宽
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)8),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)15)); //设置列宽
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //左对齐
	cols.AttachDispatch(objRange.GetItem(COleVariant((long)9),VOptional).pdispVal,TRUE);
	cols.SetColumnWidth(COleVariant((long)15)); //设置列宽
	cols.SetHorizontalAlignment(_variant_t((long)-4131)); //左对齐
	//cols.SetWrapText((_variant_t)(short)TRUE);
				
	//// 保存文件
	//objBook.Save();
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	//objBook.SetSaved(TRUE);
	objBook.SaveAs(COleVariant(filePath.GetBuffer(0)),_variant_t((long)18),covOptional,covOptional,
						covOptional,covOptional,(long)0,covOptional,covOptional,covOptional,covOptional,covOptional);
	objRange.ReleaseDispatch();
	//// 关闭文件
	objRange.Clear();
	objBook.Close(COleVariant((short)FALSE),VOptional,VOptional);
	objBooks.Close();
	objApp.Quit();	
	filePath.ReleaseBuffer();
	this->MessageBox("导出完成!");
}

void CDialogQueryData::OnBtnBackup() 
{
	BOOL isOpen = FALSE;		//是否打开(否则为保存)
	CString defaultDir = L"E:\\FileTest";	//默认打开的文件路径
	CString fileName = L"test.xls";			//默认打开的文件名
	CTime tm; 
	tm=tm.GetCurrentTime();
	fileName=tm.Format("%Y-%m-%d.mdb");
	CString filter = L"文件 (*.mdb)|*.mdb||";	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, NULL, fileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath = defaultDir + "\\" + fileName;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
		return;
	if(CopyFile("HD_IDDB.mdb",filePath,FALSE)) //覆盖
		AfxMessageBox("数据库备份成功!"); 
	else 
	{
		int i=GetLastError();
		AfxMessageBox("数据库备份失败!");  
	}

}

void CDialogQueryData::OnBtnOpenbackup() 
{
	//先判断是否已经打开了数据库
	if(isOpenBackup)
	{
		//this->MessageBox("关闭!");
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///如果已经打开了连接则关闭它
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
	}
	////////////////
	BOOL isOpen = TRUE;		//是否打开(否则为保存)
	CString filter = L"文件 (*.mdb)|*.mdb||";	//文件过虑的类型
	CFileDialog openFileDlg(isOpen, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT|OFN_NOCHANGEDIR, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	CString filePath;
	if(result == IDOK) 
	{
		filePath = openFileDlg.GetPathName();
		//this->MessageBox(filePath);
	}else
	{
		isOpenBackup=false;
		return;
	}
	////////////连接数据库//////////////
	HRESULT hr;
	try
	{
		hr = m_pConnection_backup.CreateInstance("ADODB.Connection");///创建Connection对象
		if(SUCCEEDED(hr))
		{
			char sOpen[200]={0};
			sprintf(sOpen,"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s",filePath);
			m_pConnection_backup->ConnectionTimeout = 5;
			hr = m_pConnection_backup->Open(sOpen,"","",adModeUnknown);///连接数据库
			//上面一句中连接字串中的Provider是针对ACCESS2000环境的，对于ACCESS97,需要改为:Provider=Microsoft.Jet.OLEDB.3.51;  }
		}
	}
	catch(_com_error e)///捕捉异常
	{
		CString errormessage;
		errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		AfxMessageBox(errormessage);///显示错误信息
		return ;
	} 
	//打开纪录集Log
	//m_pRecordset=m_pConnection->Execute("INSERT INTO DBID(姓名,性别,民族,出生日期,家庭住址,身份证号码,签发机关,有效期起,有效期止) VALUES ('2','2','2','2','2','2','2','2','2')",&RecordsAffected,adCmdText);
	//	r.CreateInstance(_uuidof(Recordset));
	m_pRecordset_backup.CreateInstance("ADODB.Recordset");
	CString s="select * from DBID";
	_bstr_t bs=s.AllocSysString();
	m_pRecordset_backup->Open(bs,m_pConnection_backup.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	//显示数据
	_variant_t name,sex,nation,born,addr,cardno,issue,yxq,jiezhi;
	m_list.DeleteAllItems();
	while(!m_pRecordset_backup->adoEOF)
	{
		name = m_pRecordset_backup->GetCollect(_variant_t((long)1));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		sex = m_pRecordset_backup->GetCollect(_variant_t((long)2));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		nation = m_pRecordset_backup->GetCollect(_variant_t((long)3));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		born = m_pRecordset_backup->GetCollect(_variant_t((long)4));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		addr = m_pRecordset_backup->GetCollect(_variant_t((long)5));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		cardno = m_pRecordset_backup->GetCollect(_variant_t((long)6));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		issue = m_pRecordset_backup->GetCollect(_variant_t((long)7));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		yxq = m_pRecordset_backup->GetCollect(_variant_t((long)8));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		jiezhi = m_pRecordset_backup->GetCollect(_variant_t((long)9));//取得第1列的值,从0开始计数，你也可以直接给出列的名称；
		if(name.vt != VT_NULL && sex.vt != VT_NULL && nation.vt != VT_NULL && 
			born.vt != VT_NULL&& addr.vt != VT_NULL&& jiezhi.vt != VT_NULL&& 
			cardno.vt != VT_NULL&& issue.vt != VT_NULL	&& yxq.vt != VT_NULL)
		{
			int n=m_list.GetItemCount();
			m_list.InsertItem(n,(LPCTSTR)(_bstr_t)name,0);
			m_list.SetItemText(n,1,(LPCTSTR)(_bstr_t)sex);
			m_list.SetItemText(n,2,(LPCTSTR)(_bstr_t)nation);
			m_list.SetItemText(n,3,(LPCTSTR)(_bstr_t)born);
			m_list.SetItemText(n,4,(LPCTSTR)(_bstr_t)addr);
			m_list.SetItemText(n,5,(LPCTSTR)(_bstr_t)cardno);
			m_list.SetItemText(n,6,(LPCTSTR)(_bstr_t)issue);
			m_list.SetItemText(n,7,(LPCTSTR)(_bstr_t)yxq);
			m_list.SetItemText(n,8,(LPCTSTR)(_bstr_t)jiezhi);
		}
		m_pRecordset_backup->MoveNext();///移到下一条记录
	}
	//
	isOpenBackup=true;
	GetDlgItem(IDC_BTN_BACKUP)->EnableWindow(FALSE);
}

void CDialogQueryData::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(isOpenBackup)
	{
		if (m_pRecordset_backup->GetState() == adStateOpen)
		{
			m_pRecordset_backup->Close();
		}
		if(m_pConnection_backup->GetState()==adStateOpen) 
			m_pConnection_backup->Close(); ///如果已经打开了连接则关闭它
		if (m_pConnection_backup)
		{
			m_pConnection_backup.Release();
			m_pConnection_backup = NULL;
		}
	}
	CDialog::OnClose();
}
