#include "DatabaseMap.h"

namespace orm {
	namespace mysql {
		namespace user {
			std::shared_ptr<User>from(const QSqlQuery& query) {
                auto user = std::make_shared<User>();
				user->id=query.value("id").toInt();
				user->userName=query.value("user_name").toString();
				user->nickName=query.value("nick_name").toString();
				user->password=query.value("password").toString();
				if(query.value("gender").toString()=="男")
				user->gender=1;
                else if(query.value("gender").toString()=="女")
                user->gender=2;
				else
				user->gender=0;
				user->dateBirth=query.value("date_birth").toString();
				user->avatar=query.value("avatar").toString();
				user->creationTime=query.value("creation_time").toString();
				user->creator=query.value("creator").toString();
				user->onlineTime=query.value("online_time").toString();
				user->remark=query.value("remark").toString();
				user->phoneNumber=query.value("phone_number").toString();
				user->user_state=query.value("user_state").toInt();
				user->is_unsubscribe=query.value("is_unsubscribe").toInt();
				return user;
			}

		}
	}
}
