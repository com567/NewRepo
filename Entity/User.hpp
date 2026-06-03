#pragma once
#include<QString>


struct User{
    qint32  id;
    QString userName;
    QString nickName;
    QString password;
    qint8 gender{0};
    QString dateBirth;
    QString avatar;
    QString creationTime;
    QString creator;
    QString onlineTime;
    QString remark;
    QString phoneNumber;
    qint8 user_state;
    qint8 is_unsubscribe;
};