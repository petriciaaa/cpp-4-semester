﻿
// MFCCalc.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMFCCalcApp:
// Сведения о реализации этого класса: MFCCalc.cpp
//

class CMFCCalcApp : public CWinApp
{
public:
	CMFCCalcApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCCalcApp theApp;
