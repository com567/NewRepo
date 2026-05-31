#pragma once
#include "Common/Base/Singleton.hpp"
struct User;
class ContextHolder : public Singleton<ContextHolder>
{
	friend class Singleton<ContextHolder>;

public:
	ContextHolder();
	~ContextHolder();

	void setSelf(std::shared_ptr<User> user);
	std::shared_ptr<User> getSelf()const;
private:
	std::shared_ptr<User> m_user{};
};

