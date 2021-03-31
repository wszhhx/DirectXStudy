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

	//����D3D����
	m_D3D = new D3DClass;
	if (!m_D3D) {
		return false;
	}
	//��ʼ��D3D
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN,
		SCREEN_DEPTH, SCREEN_NEAR);
	if (!result) {
		MessageBox(hwnd, L"�޷���ʼ��Direct3D", L"����", MB_OK);
		return false;
	}
	MessageBox(hwnd, L"Direct3D��ʼ���ɹ�", L"��ʾ", MB_OK);
	return true;
}

void GraphicsClass::Shutdown()
{
	//�ͷ�D3D
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

	//��Ⱦ����
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