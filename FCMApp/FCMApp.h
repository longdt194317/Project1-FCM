
// FCMApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFCMAppApp:
// See FCMApp.cpp for the implementation of this class
//

class CFCMAppApp : public CWinApp
{
public:
	CFCMAppApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFCMAppApp theApp;
