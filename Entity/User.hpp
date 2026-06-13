#pragma once
#include"Common/Config/Config.h"
#include<QPixmap>
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
    QPixmap _pixmap;
    QPixmap avatarPixmap() {
        if (avatar.isEmpty()) 
            _pixmap.load(":/image/defaultAvatar.png");
        
        else 
            _pixmap.load(Config::instance()->profilePath() + "/" + avatar);

        return _pixmap; 
    }
};