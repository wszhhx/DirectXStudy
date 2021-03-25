#include"systemclass.h"
//#include "SystemClass.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	SystemClass* System;
	bool result;

	//创建System对象
	System = new SystemClass;
	if (!System) {
		return 0;
	}

	//初始化并运行system对象
	result = System->Initialize();
	if (result) {
		System->Run();
	}

	System->Shutdown();

	delete System;
	System = 0;
	return 0;
}