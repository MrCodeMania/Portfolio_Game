
// Bhzzang.h : Bhzzang ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CBhzzangApp:
// �� Ŭ������ ������ ���ؼ��� Bhzzang.cpp�� �����Ͻʽÿ�.
//

class CBhzzangApp : public CWinApp
{
public:
	CBhzzangApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBhzzangApp theApp;
