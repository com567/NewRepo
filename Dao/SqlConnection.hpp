#pragma once
#include<QSqlDatabase>
#include<QSqlError>
#include<QSqlQuery>

inline QSqlDatabase getConnection(const QString& con_name = "我是牢大")
{

	auto con = QSqlDatabase::addDatabase("QMYSQL",con_name);
	if (con.isOpen()) {
		qDebug() << "Database connection already open";
		return con;
	}
	con.setHostName("43.138.243.7");
	con.setPort(3306);
	con.setUserName("fu");
	con.setPassword("123456aA");
	con.setDatabaseName("hdy_student_manager");
	if (!con.open())
	{
		qDebug() << "Failed to connect to database:" << con.lastError().text();
	}
	return con;
}