#include"inputclass.h"

InputClass::InputClass() {

}

InputClass::InputClass(const InputClass& other) {

}

InputClass::~InputClass() {

}

void InputClass::Initialize() {
	int i;

	//��ʼ�����м�������״̬
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
	//����ָ�������ļ�λ����״̬
	return m_keys[input];
}