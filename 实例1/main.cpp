#include"systemclass.h"
//#include "SystemClass.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow) {
	SystemClass* System;
	bool result;

	//����System����
	System = new SystemClass;
	if (!System) {
		return 0;
	}

	//��ʼ��������system����
	result = System->Initialize();
	if (result) {
		System->Run();
	}

	System->Shutdown();

	delete System;
	System = 0;
	return 0;
}