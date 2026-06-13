#include "UserService.h"
#include "ContextHolder.h"
#include "Common/Config/Config.h"
#include <QFile>

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
	auto user=ContextHolder::instance()->getSelf();
	return userService->modify_nickName(user->id,nick_name);
}

bool UserService::modify_avatar(qint32 id, const QByteArray& data, const QString& format)
{
    if (data.size() == 0)return false;
	auto user = ContextHolder::instance()->getSelf();
    if (user->id != id)return false;
	auto path = Config::instance()->profilePath();
	auto filename= QString::number(id) + "." + format;
	QFile file(path +"/"+ filename);

	if (!file.open(QIODevice::WriteOnly)) {
		qDebug()<<file.errorString();
        		return false;
	}
	file.write(data);
	return userService->modify_avatar(id,filename);
}

bool UserService::modify_dateBirth(const QString& date_birth )
{
	auto user = ContextHolder::instance()->getSelf();
	return userService->modify_dateBirth(user->id,date_birth);
}

bool UserService::modify_gender(const QString& gender )
{
	auto user = ContextHolder::instance()->getSelf();
	return userService->modify_gender(user->id,gender);
}

bool UserService::modify_phoneNumber(const QString& phone_number )
{
	if( phone_number.size() != 11)return false;
	auto user = ContextHolder::instance()->getSelf();
	return userService->modify_phoneNumber(user->id,phone_number);
}

bool UserService::delete_user(const QString& password )
{
	return userService->delete_user(password);
}
