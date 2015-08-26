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
	// 初始化
	Py_Initialize();
	if (!Py_IsInitialized())
		return ;
	// python文件名
	PyObject * pModule = PyImport_ImportModule("tclient");
	if (!pModule)
		return ;
	// 函数名
	PyObject * pFunc = PyObject_GetAttrString(pModule, "request_info");
	if (!pFunc)
		return ;
	// 调用函数
	PyObject*pResult = PyEval_CallObject(pFunc, NULL);//调用函数
	if (pResult)
	{
		char* pBuffer1 = nullptr;
		char* pBuffer2 = nullptr;
		// 解析结果
		if (PyArg_Parse(pResult, "(ss)", &pBuffer1, &pBuffer2))
		{
			m_account = pBuffer1;
			m_gameurl = pBuffer2;
		}
		Py_DECREF(pResult);
	}
	//结束调用
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



