#pragma once
//Filename: systemclass.h

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///
// 指定预处理（排除不常用API，减小WIN32头文件，加快生成过程） //
///
#define WIN32_LEAN_AND_MEAN

//
// 系统 //
//
#include <windows.h>

//
// 自定义 //
//
#include "inputclass.h"
#include "graphicsclass.h"

class SystemClass {
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;

};

//函数原型
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//全局
static SystemClass* ApplicationHandle = 0;


#endif // _SYSTEMCLASS_H_