#include "graphicsclass.h"

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{

}

GraphicsClass::~GraphicsClass()
{

}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd) 
{
	bool result;

	//创建D3D物体
	m_D3D = new D3DClass;
	if (!m_D3D) {
		return false;
	}
	//初始化D3D
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"无法初始化Direct3D", L"错误", MB_OK);
		return false;
	}
	MessageBox(hwnd, L"Direct3D初始化成功", L"提示", MB_OK);
	return true;
}

void GraphicsClass::Shutdown()
{
	//释放D3D
	if (m_D3D) {
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}
	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	//渲染场景
	result = Render();
	if (!result) {
		return false;
	}
	return true;
}

bool GraphicsClass::Render()
{
	m_D3D->BeginScene(0.5f, 0.5f, 0.5f, 1.0f);
	m_D3D->EndScene();
	return true;
}