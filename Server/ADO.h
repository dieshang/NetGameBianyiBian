#pragma once

#include <comdef.h>
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF"),rename("BOF","adoBOF")
#include <atlstr.h>
class CADO  
{
public:
	_RecordsetPtr  m_pRecordset;
public:
	CADO();
	virtual ~CADO();
	BOOL openDB(CString m_strPathName, CString m_strName, CString m_strPassword, CString m_strProvider);
	void close();
	_RecordsetPtr search(const CString m_strSql);
	BOOL dbDelete(const CString m_strSql);
	BOOL update(const CString m_strSql);
	BOOL insert(const CString m_strSql);
private:
	void initConnection();
	void initRecordSet();
	void initCommand();
	BOOL CommandIsValid();
	BOOL RecordSetIsValid();
	BOOL ConnectionIsValid();
private:
	_CommandPtr m_pCommand;
	_ConnectionPtr  m_pConnection;
};