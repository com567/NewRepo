#pragma once
#include"../Entity/User.hpp"
#include<QSqlQuery>
#include<iostream>
#include<memory>

namespace orm { 
		namespace mysql {
			namespace user {
				std::shared_ptr<User>from(const QSqlQuery& query);
				
			}
		}
	}


