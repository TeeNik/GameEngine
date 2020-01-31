#pragma once
#include <functional>

class InputSubscriber {
public:
	virtual void Subscribe(int, std::function<void()>&) = 0;
};
