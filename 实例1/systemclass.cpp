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

	//在接收正式参数之前，先将显示区域的宽高初始化为0
	screenWidth = 0;
	screenHeight = 0;

	//初始化窗口API
	InitializeWindows(screenWidth, screenHeight);

	//创建输入类、该载体用于读取并处理用户在键盘上的输入
	m_Input = new InputClass;
	if (!m_Input) {
		//--Msg
		return false;
	}

	//初始化输入类
	m_Input->Initialize();

	//创建图形类，该类负责所有的渲染操作
	m_Graphics = new GraphicsClass;
	if (!m_Graphics) {
		//--Msg
		return false;
	}

	//初始化图形类
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if (!result) {
		//--Msg
		return false;
	}
	return true;

}

void SystemClass::Shutdown() {
	//释放图形类
	if (m_Graphics) {
		m_Graphics->Shutdown();
		delete m_Graphics;
		m_Graphics = 0;
	}

	//释放输入类
	if (m_Input) {
		delete m_Input;
		m_Input = 0;
	}

	//关闭窗口
	ShutdownWindows();
	return;
}

void SystemClass::Run() {
	MSG msg;
	bool done, result;

	//初始化信息结构
	ZeroMemory(&msg, sizeof(MSG));

	//帧循环，直至收到用户关闭的消息
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

	//若用户按下ESC键，则退出
	if (m_Input->IsKeyDown(VK_ESCAPE)) {
		return false;
	}

	//否则调用图形类渲染当前帧
	result = m_Graphics->Frame();
	if (!result) {
		return false;
	}
	return true;
}


//只监听我们想要的用户输入，其余输入交给系统默认处理即可
LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
	switch (umsg) {
		//监听用户按下键盘按键
		case WM_KEYDOWN: {
			//让INPUT对象记录键盘按下的状态
			m_Input->KeyDown((unsigned int)wparam);
			return 0;
		}
		
		//监听用户释放键盘按键
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

	//让全局的应用指针指向系统对象
	ApplicationHandle = this;

	//获取本应用实例
	m_hinstance = GetModuleHandle(NULL);

	//设置本应用的名字
	m_applicationName = L"God Herhsel Engine";

	//设置窗口类的默认状态
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

	//注册窗口类
	RegisterClassEx(&wc);

	//绑定用户屏幕分辨率
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	//根据用户设置全屏与否调整显示区域
	if (FULL_SCREEN) {
		//将显示范围设为用户桌面分辨率，颜色设置为32比特
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		//调整左上角的原点
		posX = posY = 0;
	}
	else {
		//若为窗口模式，则默认为800x600分辨率
		screenWidth = 800;
		screenHeight = 600;

		//将窗口放到屏幕中间
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	//根据窗口设置创建窗口并返回窗口句柄
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	//将窗口显示在顶层，并将系统焦点置于其上
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	//隐藏鼠标
	ShowCursor(false);
	return;

}

void SystemClass::ShutdownWindows() {
	//显示鼠标
	ShowCursor(true);

	//若为全屏显示，则关闭时恢复设置
	if (FULL_SCREEN) {
		ChangeDisplaySettings(NULL, 0);
	}
	//移除窗口
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	//移除应用实例
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	//释放指针
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam) {
	switch (umessage) {
		//若窗口已被销毁
		case WM_DESTROY: 
		{
			PostQuitMessage(0);
			return 0;
		}

		//若窗口被关闭
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