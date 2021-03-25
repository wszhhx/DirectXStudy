#pragma once
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_



class InputClass {
public:
	InputClass();
	InputClass(const InputClass& other);
	~InputClass();

	void Initialize();
	
	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};

#endif // _INPUTCLASS_H_