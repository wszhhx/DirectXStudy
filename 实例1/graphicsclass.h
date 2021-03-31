#pragma once

#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include"d3dclass.h"

///
//ȫ�ֱ���//
///
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

//������ͼ����ص��඼���װ��GraphicsClass��
class GraphicsClass {
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();

private:
	bool Render();
private:
	D3DClass* m_D3D;
};

#endif</windows.h> // !1