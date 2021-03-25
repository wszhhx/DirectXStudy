#include"inputclass.h"

InputClass::InputClass() {

}

InputClass::InputClass(const InputClass& other) {

}

InputClass::~InputClass() {

}

void InputClass::Initialize() {
	int i;

	//初始化所有键盘输入状态
	for (int i = 0; i < 256; ++i) {
		m_keys[i] = false;
	}
	return;
}

void InputClass::KeyDown(unsigned int input) {
	m_keys[input] = true;

	return;
}

void InputClass::KeyUp(unsigned int input) {
	m_keys[input] = false;
	return;
}

bool InputClass::IsKeyDown(unsigned int input) {
	//返回指定索引的键位按下状态
	return m_keys[input];
}