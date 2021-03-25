#include"systemclass.h"

SystemClass::SystemClass() {
	m_Input = 0;
	m_Graphics = 0;
}

SystemClass::SystemClass(const SystemClass& other) {

}

SystemClass::~SystemClass() {

}

bool SystemClass::Initialize() {
	int screenWidth, screenHeight;
	bool result;

	//�ڽ�����ʽ����֮ǰ���Ƚ���ʾ����Ŀ�߳�ʼ��Ϊ0
	screenWidth = 0;
	screenHeight = 0;

	//��ʼ������API
	InitializeWindows(screenWidth, screenHeight);

	//���������ࡢ���������ڶ�ȡ�������û��ڼ����ϵ�����
	m_Input = new InputClass;
	if (!m_Input) {
		//--Msg
		return false;
	}

	//��ʼ��������
	m_Input->Initialize();

	//����ͼ���࣬���ฺ�����е���Ⱦ����
	m_Graphics = new GraphicsClass;
	if (!m_Graphics) {
		//--Msg
		return false;
	}

	//��ʼ��ͼ����
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result) {
		//--Msg
		return false;
	}
	return true;

}

void SystemClass::Shutdown() {
	//�ͷ�ͼ����
	if (m_Graphics) {
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	//�ͷ�������
	if (m_Input) {
		delete m_Input;
		m_Input = 0;
	}

	//�رմ���
	ShutdownWindows();
	return;
}

void SystemClass::Run() {
	MSG msg;
	bool done, result;

	//��ʼ����Ϣ�ṹ
	ZeroMemory(&msg, sizeof(MSG));

	//֡ѭ����ֱ���յ��û��رյ���Ϣ
	done = false;
	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			done = true;
		}
		else {
			result = Frame();
			if (!result) {
				done = true;
			}
		}
	}
	return;
}

bool SystemClass::Frame() {
	bool result;

	//���û�����ESC�������˳�
	if (m_Input->IsKeyDown(VK_ESCAPE)) {
		return false;
	}

	//�������ͼ������Ⱦ��ǰ֡
	result = m_Graphics->Frame();
	if (!result) {
		return false;
	}
	return true;
}


//ֻ����������Ҫ���û����룬�������뽻��ϵͳĬ�ϴ�����
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
		//�����û����¼��̰���
		case WM_KEYDOWN: {
			//��INPUT�����¼���̰��µ�״̬
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}
		
		//�����û��ͷż��̰���
		case WM_KEYUP: {
			m_Input->KeyUp((unsigned int)wparam);
			return 0;
		}
		default: {
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}


	}
}

void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight) {
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	//��ȫ�ֵ�Ӧ��ָ��ָ��ϵͳ����
	ApplicationHandle = this;

	//��ȡ��Ӧ��ʵ��
	m_hinstance = GetModuleHandle(NULL);

	//���ñ�Ӧ�õ�����
	m_applicationName = L"God Herhsel Engine";

	//���ô������Ĭ��״̬
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	//ע�ᴰ����
	RegisterClassEx(&wc);

	//���û���Ļ�ֱ���
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//�����û�����ȫ����������ʾ����
	if (FULL_SCREEN) {
		//����ʾ��Χ��Ϊ�û�����ֱ��ʣ���ɫ����Ϊ32����
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//�������Ͻǵ�ԭ��
		posX = posY = 0;
	}
	else {
		//��Ϊ����ģʽ����Ĭ��Ϊ800x600�ֱ���
		screenWidth = 800;
		screenHeight = 600;

		//�����ڷŵ���Ļ�м�
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//���ݴ������ô������ڲ����ش��ھ��
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	//��������ʾ�ڶ��㣬����ϵͳ������������
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//�������
	ShowCursor(false);
	return;

}

void SystemClass::ShutdownWindows() {
	//��ʾ���
	ShowCursor(true);

	//��Ϊȫ����ʾ����ر�ʱ�ָ�����
	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}
	//�Ƴ�����
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	//�Ƴ�Ӧ��ʵ��
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	//�ͷ�ָ��
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
		//�������ѱ�����
		case WM_DESTROY: 
		{
			PostQuitMessage(0);
			return 0;
		}

		//�����ڱ��ر�
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
		default:
		{
			
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}