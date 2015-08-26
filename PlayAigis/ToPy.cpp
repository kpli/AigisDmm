#include "stdafx.h"
#include "ToPy.h"
#include "python.h"


CToPy::CToPy()
	: m_gameurl("")
	, m_account("")
{
}


CToPy::~CToPy()
{
}

CToPy* CToPy::getInstance()
{
	static CToPy ret;
	return &ret;
}

void CToPy::runPython()
{
	reset();
	// ��ʼ��
	Py_Initialize();
	if (!Py_IsInitialized())
		return ;
	// python�ļ���
	PyObject * pModule = PyImport_ImportModule("tclient");
	if (!pModule)
		return ;
	// ������
	PyObject * pFunc = PyObject_GetAttrString(pModule, "request_info");
	if (!pFunc)
		return ;
	// ���ú���
	PyObject*pResult = PyEval_CallObject(pFunc, NULL);//���ú���
	if (pResult)
	{
		char* pBuffer1 = nullptr;
		char* pBuffer2 = nullptr;
		// �������
		if (PyArg_Parse(pResult, "(ss)", &pBuffer1, &pBuffer2))
		{
			m_account = pBuffer1;
			m_gameurl = pBuffer2;
		}
		Py_DECREF(pResult);
	}
	//��������
	Py_Finalize();
}

std::string CToPy::getUrl()
{
	return m_gameurl;
}

std::string CToPy::getMail()
{
	return m_account;
}

void CToPy::reset()
{
	m_gameurl = ("");
	m_account = ("");
}



