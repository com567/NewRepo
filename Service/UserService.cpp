#include "UserService.h"



UserService::UserService()
	:userService(UserDao::instance())
{
}

UserService::~UserService()
{
}

std::shared_ptr<User> UserService::searchUser_name(const QString& name )
{
	if (name.size() != 12)return nullptr;

	return userService->searchUser_name(name);
}

std::shared_ptr<User> UserService::searchNick_name(const QString& nick_name )
{
	if (nick_name.size() == 0 || nick_name.size() > 36)return nullptr;

	return userService->searchNick_name(nick_name);
}

bool UserService::register_user(const QString& account, const QString& password )
{
	if (account.size() == 0 || account.size() > 36)return false;
	return userService->register_user(account, password);
}

bool UserService::modify_password(const QString& account, const QString& new_password )
{
	if (account.size() == 0 || account.size() > 36|| new_password.size()<8)return false;
	return userService->modify_password(account, new_password);
}

bool UserService::modify_nickName(const QString& nick_name )
{
	if (nick_name.size() == 0 || nick_name.size() > 36)return false;
	return userService->modify_nickName(nick_name);
}

bool UserService::modify_avatar(const QString& avatar )
{
    if (avatar.size() == 0 || avatar.size() >= 250)return false;
	return userService->modify_avatar(avatar);
}

bool UserService::modify_dateBirth(const QString& date_birth )
{
	return userService->modify_dateBirth(date_birth);
}

bool UserService::modify_gender(const QString& gender )
{

	return userService->modify_gender(gender);
}

bool UserService::modify_phoneNumber(const QString& phone_number )
{
	if( phone_number.size() != 11)return false;
	return userService->modify_phoneNumber(phone_number);
}

bool UserService::delete_user(const QString& password )
{
	return userService->delete_user(password);
}
