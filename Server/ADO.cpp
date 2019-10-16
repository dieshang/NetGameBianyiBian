#include "ADO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CADO::CADO()
{
	::CoInitialize(NULL);
}
CADO::~CADO()
{
	::CoUninitialize();
}
BOOL CADO::ConnectionIsValid()
{
	if (m_pConnection == NULL)
		return FALSE;
	else
		return TRUE;
}
BOOL CADO::RecordSetIsValid()
{
	if (m_pRecordset == NULL)
		return FALSE;
	else
		return TRUE;
}
BOOL CADO::CommandIsValid()
{
	if (m_pCommand == NULL)
		return FALSE;
	else
		return TRUE;
}
void CADO::initConnection()
{
	if (!ConnectionIsValid())
		m_pConnection.CreateInstance( __uuidof(Connection));
}
void CADO::initRecordSet()
{
	if (!RecordSetIsValid())
		m_pRecordset.CreateInstance(__uuidof(Recordset));
}
void CADO::initCommand()
{
	if (!CommandIsValid())
		m_pCommand.CreateInstance(__uuidof(Command));
}
BOOL CADO::openDB(CString m_strPathName, CString m_strName, CString m_strPassword, CString m_strProvider)
{
	initConnection();
	initRecordSet();
	initCommand();
	m_pConnection->Provider = _bstr_t(m_strProvider);
	if(S_OK == m_pConnection->Open(_bstr_t(m_strPathName), _bstr_t(m_strName), _bstr_t(m_strPassword), adModeUnknown))
		return TRUE;
	else 
		return FALSE;
} 
void CADO::close()
{
	if (RecordSetIsValid())
	{
		if( m_pRecordset->State == adStateOpen)
			m_pRecordset->Close();
	}
	if (ConnectionIsValid() || m_pConnection->State == adStateOpen)
	{
		m_pConnection->Close();
	}
}
BOOL CADO::insert(const CString m_strSql)
{
	try
	{
		if (!ConnectionIsValid() || m_pConnection->State == adStateClosed)
		{
			MessageBox(NULL,_T("DB closed"),_T("提示"),NULL);
			//RAConnect(m_ConnectionString);
			return FALSE;
		}

		if(!CommandIsValid())
		{
			initCommand();
		}

		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandType = adCmdText;
		m_pCommand->CommandText = _bstr_t(m_strSql);

		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;

		m_pCommand->Execute(&vNull, &vNull, adCmdText);//m_pConnection->Execute(........)也可以
		//m_pConnection->Execute(_bstr_t(m_strSql), &vNull, adCmdText);
	
		return TRUE;
	}
	catch(_com_error &e)
	{
		MessageBox(NULL,e.Description(),_T("提示"),NULL);
		return FALSE;
	}
}
BOOL CADO::update(const CString m_strSql)
{
	try
	{
		if (!ConnectionIsValid() || m_pConnection->State == adStateClosed)
		{
			MessageBox(NULL,_T("DB closed"),_T("提示"),NULL);
			return FALSE;
		}
		if(!CommandIsValid())
		{
			initCommand();
		}

		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandType = adCmdText;
		m_pCommand->CommandText = _bstr_t(m_strSql);

		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;

		m_pCommand->Execute(&vNull, &vNull, adCmdText);

		return TRUE;
	}
	catch(_com_error &e)
	{
		MessageBox(NULL,e.Description(),_T("提示"),NULL);
		return FALSE;
	}
}
BOOL CADO::dbDelete(const CString m_strSql)
{
	try
	{
		if (!ConnectionIsValid() || m_pConnection->State == adStateClosed)
		{
			
			MessageBox(NULL,_T("DB closed"),_T("提示"),NULL);
			//RAConnect(m_ConnectionString);
			return FALSE;
		}
		if(!CommandIsValid())
		{
			initCommand();
		}

		m_pCommand->ActiveConnection = m_pConnection;
		m_pCommand->CommandType = adCmdText;
		m_pCommand->CommandText = _bstr_t(m_strSql);

		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;

		m_pCommand->Execute(&vNull, &vNull, adCmdText);

		return TRUE;
	}
	catch(_com_error &e)
	{
		MessageBox(NULL,e.Description(),_T("提示"),NULL);
		return FALSE;
	}
}
_RecordsetPtr CADO::search(const CString m_strSql)
{
	try
	{
		if (!ConnectionIsValid() || m_pConnection->State == adStateClosed)
		{
			MessageBox(NULL,_T("DB closed"),_T("提示"),NULL);

			return NULL;
		}
		else
		{ 
			if (RecordSetIsValid())
			{
				if (m_pRecordset->State == adStateOpen)
					m_pRecordset->Close();
			}
			else
			{    
				initRecordSet();
			}

			if(!CommandIsValid())
			{
				initCommand();
			}
			m_pCommand->ActiveConnection = m_pConnection;
			m_pCommand->CommandType = adCmdText;
			m_pCommand->CommandText = _bstr_t(m_strSql);

			_variant_t vNull;
			vNull.vt = VT_ERROR;
			vNull.scode = DISP_E_PARAMNOTFOUND;

			m_pRecordset = m_pCommand->Execute(&vNull, &vNull, adCmdText);
			return  m_pRecordset.Detach();
		}
	}
	catch(_com_error &e)
	{
		MessageBox(NULL,e.Description(),_T("提示"),NULL);
		return NULL;
	}
}