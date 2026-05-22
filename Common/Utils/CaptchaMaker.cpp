#include "CaptchaMaker.h"
#include<QPainter>


CaptchaMaker::CaptchaMaker()
	:m_type(VerificationCode_type(RAND(0,2)))
{
    
}

CaptchaMaker::~CaptchaMaker()
{}



void CaptchaMaker::setType(VerificationCode_type type)
{
	m_type = type;
}

CaptchaMaker::VerificationCode_type CaptchaMaker::getType() const
{
	return m_type;
}

QPair<QString, QString> CaptchaMaker::createText()
{
	if (m_type == Char)
	{
		return createText_Char();
	}
	else if (m_type == Math)
	{
		return createText_Math();
	}
	else return {};
}

QPixmap CaptchaMaker::createImage(const QString& text)
{
	if (m_type == Char)
	{
		return createCharImage(text);
	}
	else if (m_type == Math)
	{
		return createMathImage(text);
	}
	else return {};
}



QPair<QString, QString> CaptchaMaker::createText_Char()
{
	QString m_text;
	for (int i = 0; i < 4; i++) {
		int type = RAND(0, 3);
		if (type==0) {
            m_text.append(QChar('A' + RAND(0, 26)));
		}
		else if (type==1) {
            m_text.append(QChar('a' + RAND(0, 26)));
		}
		else
		m_text.append(QChar('0' + RAND(0, 10)));
	}
	return QPair<QString, QString>(m_text,m_text);
}

QPair<QString, QString> CaptchaMaker::createText_Math()
{
	QString text,answer;
	int op=RAND(0,3);
	qint16 Left_operand=RAND(0,25);
	qint16 Right_operand=RAND(0,25);
    switch (op)
	{
        case 0:
			text = QString("%1+%2=?").arg(Left_operand).arg(Right_operand);
			answer = QString::number(Left_operand+Right_operand);
			break;
        case 1:
			text = QString("%1-%2=?").arg(Left_operand).arg(Right_operand);
			answer = QString::number(Left_operand - Right_operand);
			break;
        case 2:
			text = QString("%1×%2=?").arg(Left_operand).arg(Right_operand);
			answer = QString::number(Left_operand * Right_operand);
			break;
		default:
			break;
	}
	return QPair<QString, QString>({text,answer});
}

QPixmap CaptchaMaker::createMathImage(const QString& text)
{
    QPixmap pixmap(m_Image.imageSize);
	QLinearGradient gradient(0, 0, pixmap.width(), pixmap.height());
	gradient.setColorAt(0, m_Image.begin_color);
	gradient.setColorAt(1, m_Image.end_color);

	QPainter painter(&pixmap);
	//开启高质量渲染
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(gradient);
	painter.drawRect(pixmap.rect().adjusted(0, 0, -1, -1));

	
	painter.setFont(m_Image.math_font);

    painter.drawText(pixmap.rect(), Qt::AlignCenter, text);

	return pixmap;
}

QPixmap CaptchaMaker::createCharImage(const QString& text)
{
    QPixmap pixmap(m_Image.imageSize);
	//渐变背景
	QLinearGradient gradient(0,0,pixmap.width(),pixmap.height());
	gradient.setColorAt(0,m_Image.begin_color);
	gradient.setColorAt(1,m_Image.end_color);

    QPainter painter(&pixmap);
	//开启高质量渲染
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(gradient);
	painter.drawRect(pixmap.rect().adjusted(0,0,-1,-1));

    painter.setFont(m_Image.char_font);
	for (int i = 0; i < text.size(); i++) {
		painter.save();
		painter.setPen(QPen(QColor(RAND(35,255),RAND(35,255),RAND(35,255))));
		//随机倾斜
		if (RAND(0, 2) == 0) {
			painter.shear(RAND(0,36)/100.0,0);
		}
		//随机旋转
		else {
			painter.rotate(RAND(0,9));
		}

		painter.drawText(QRect((i * m_Image.imageSize.width() / 4) - 10, 0,m_Image.x,m_Image.y),Qt::AlignCenter,text.at(i)); 
			 
		painter.restore();
	}
	//绘制干扰线
    for (int i = 0; i < 5; i++) {
	
		painter.save();	//记录画笔
		painter.setPen(QPen(QColor(RAND(25,255),RAND(25,255),RAND(25,255))));
		painter.drawLine(QPoint(RAND(0,m_Image.imageSize.width()),RAND(0,m_Image.imageSize.height())),QPoint(RAND(0,m_Image.imageSize.width()),RAND(0,m_Image.imageSize.height())));
		painter.restore();	//恢复画笔
	}
	//绘制干扰点
    for (int i = 0; i < 150; i++) {
		painter.save();
		painter.setPen(QPen(QColor(RAND(0,255),RAND(0,255),RAND(0,255))));
		painter.drawPoint(RAND(0,m_Image.imageSize.width()),RAND(0,m_Image.imageSize.height()));
		painter.restore();
	}
	return pixmap;
}

