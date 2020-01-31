#pragma once
#include <functional>

class InputComponent {

public:
	void BindKey(int keyCode, std::function<void()> func);

};