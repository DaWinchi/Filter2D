
// Filter.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CFilterApp:
// Сведения о реализации этого класса: Filter.cpp
//

class CFilterApp : public CWinApp
{
public:
	CFilterApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CFilterApp theApp;
