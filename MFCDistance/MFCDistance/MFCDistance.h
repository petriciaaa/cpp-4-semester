
// MFCDistance.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCDistanceApp:
// Сведения о реализации этого класса: MFCDistance.cpp
//

class CMFCDistanceApp : public CWinApp
{
public:
	CMFCDistanceApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCDistanceApp theApp;
