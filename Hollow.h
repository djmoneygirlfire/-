// Hollow.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// �� ��ȣ


// CHollowApp:
// �� Ŭ������ ������ ���ؼ��� Hollow.cpp�� �����Ͻʽÿ�.
//

class CHollowApp : public CWinApp
{
public:
	CHollowApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CHollowApp theApp;
