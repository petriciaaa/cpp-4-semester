
// MFCMyFirstApplication.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCMyFirstApplicationApp:
// Сведения о реализации этого класса: MFCMyFirstApplication.cpp
//

class CMFCMyFirstApplicationApp : public CWinApp
{
public:
	CMFCMyFirstApplicationApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCMyFirstApplicationApp theApp;
