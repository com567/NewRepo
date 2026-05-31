#include "ContextHolder.h"
#include "Entity/User.hpp"
ContextHolder::ContextHolder()
{}

ContextHolder::~ContextHolder()
{}

void ContextHolder::setSelf(std::shared_ptr<User> user)
{
	m_user = user;
}

std::shared_ptr<User> ContextHolder::getSelf() const
{
	return m_user;
}

