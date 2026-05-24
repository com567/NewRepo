#pragma once
#include<functional>

class Defer {

public:
	Defer(const std::function<void(void)>&fun)
		:m_fun(fun)
	{}
	~Defer() {
		if (m_fun)m_fun();
	}
private:
	std::function<void(void)> m_fun;
};