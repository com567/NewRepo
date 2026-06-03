#pragma once

#include <QPushButton>

class HoverButton  : public QPushButton
{
	Q_OBJECT

public:
	HoverButton(QWidget *parent=nullptr);
	~HoverButton();

	void setMakLayer(bool enabled);
	bool getMakLayer() const;
	void setAvatarIcon(const QIcon& icon);
	void setAvatarIconSize(const QSize& size);
    QIcon getAvatarIcon() const;
	QSize getAvatarIconSize() const;


protected:
    	void enterEvent(QEnterEvent *event) override;
    	void leaveEvent(QEvent *event) override;
		void paintEvent(QPaintEvent *event) override;
signals:
		void enter();
		void leave();

private:
	bool m_pressed;
	bool m_MakLayer;
	QSize m_avatarIconSize;
	QIcon m_avatarIcon;
};

