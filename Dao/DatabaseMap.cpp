#include "DatabaseMap.h"

namespace orm {
	namespace mysql {
		namespace user {
			std::shared_ptr<User>from(const QSqlQuery& query) {
                auto user = std::make_shared<User>();
				user->id=query.value("id").toInt();
				user->user_name=query.value("user_name").toString();
				user->nick_name=query.value("nick_name").toString();
				user->password=query.value("password").toString();
				user->gender=query.value("gender").toString();
				user->dateBirth=query.value("date_birth").toString();
				user->avatar=query.value("avatar").toString();
				user->creationTime=query.value("creation_time").toString();
				user->creator=query.value("creator").toString();
				user->onlineTime=query.value("online_time").toString();
				user->remark=query.value("remark").toString();
				user->phoneNumber=query.value("phone_number").toString();
			}

		}
	}
}
