#pragma once

#include <QRandomGenerator>
#include <QPixmap>
#include <QFont>
#define RAND(min,max) QRandomGenerator::global()->bounded(min,max)
class CaptchaMaker
{
public:
	enum  VerificationCode_type
	{
		Char,	   //4位字符
		Math,	   //4则运算
	};

	struct Image { 
		QSize imageSize{130,40};
		QColor begin_color{QColor(195,195,180)};
		QColor end_color{QColor(240,240,240)};
		QFont char_font{QFont("黑体",22,QFont::Bold)};
		QFont math_font{QFont("Forte", 20)};
		int x{ 35 };
		int y{ 25 };
	
	};
public:
	CaptchaMaker();
	~CaptchaMaker();

	void setType(VerificationCode_type type);
	VerificationCode_type getType()const;
	QPair<QString,QString>createText();
    QPixmap createImage(const QString&text);

	static QString RandomAccount() {
		QString account="";
		for (int i = 0;i < 12;i++) {
			account.append(QChar('0'+ RAND(0, 10)));
		}
		return account;
	}
private:
	VerificationCode_type m_type;
    Image m_Image;
	
	QPair<QString,QString>createText_Char();
    QPair<QString,QString>createText_Math();
    QPixmap createMathImage(const QString&text);
	QPixmap createCharImage(const QString&text);
};

