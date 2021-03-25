#pragma once
//Filename: systemclass.h

#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_


///
// ָ��Ԥ�����ų�������API����СWIN32ͷ�ļ����ӿ����ɹ��̣� //
///
#define WIN32_LEAN_AND_MEAN

//
// ϵͳ //
//
#include <windows.h>

//
// �Զ��� //
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

//����ԭ��
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//ȫ��
static SystemClass* ApplicationHandle = 0;


#endif // _SYSTEMCLASS_H_