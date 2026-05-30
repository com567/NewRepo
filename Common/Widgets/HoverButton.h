#pragma once

#include <QPushButton>

class HoverButton  : public QPushButton
{
	Q_OBJECT

public:
	HoverButton(QWidget *parent=nullptr);
	~HoverButton();

protected:
    	void enterEvent(QEnterEvent *event) override;
    	void leaveEvent(QEvent *event) override;
signals:
		void enter();
		void leave();

private:
};

