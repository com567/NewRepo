#pragma once
#include"Domain/Entity/User.hpp"
#include"Domain/Entity/Menu.hpp"
#include<QSqlQuery>
#include<iostream>
#include<memory>

namespace orm { 
		namespace mysql {
			namespace user {
				std::shared_ptr<User>from(const QSqlQuery& query);
				
			}
			namespace menu {
				std::shared_ptr<Menu>from(const QSqlQuery& query);
			}
		}
	}


