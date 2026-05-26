#include "NotifyTipBox.h"
#include <QTimerEvent>
NotifyTipBox::NotifyTipBox(QWidget *parent)
	:NotifyTipBox(Login_successfully,parent)
{
	
}

NotifyTipBox::NotifyTipBox(Message_type type,qint32 delay,QWidget* parent)
	:QWidget(parent)
	,m_timerId(0)
{
	setFixedSize(420,60);
	if (m_preDatas.isEmpty()) {
		m_preDatas.append({
					QPixmap(":/Resources/warn_close.svg"),QString("输入不能为空")
					,QColor(255,255,205), QColor(255,165,5), QColor(240,255,5)
		});
		m_preDatas.append({
					QPixmap(":/Resources/succeed_close.svg"),QString("登录成功")
					,QColor(220,255,225), QColor(40,255,40), QColor(0, 255, 10)
		});	
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("登录失败")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
		m_preDatas.append({
					QPixmap(":/Resources/succeed_close.svg"),QString("注册成功")
					, QColor(220,255,225), QColor(40,255,40), QColor(0, 255, 10)
		});
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("注册失败")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
			});
		m_preDatas.append({
					QPixmap(":/Resources/succeed_close.svg"),QString("修改成功")
					,QColor(220,255,225), QColor(40,255,40), QColor(0, 255, 10)
		});
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("修改失败")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("账号或密码错误")
					, QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
        m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("密码至少为8位且包含大小写字母")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("验证码错误")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
        m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("两次密码输入不一致")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
		m_preDatas.append({
					QPixmap(":/Resources/tip_close.svg"),QString("用户不存在")
					,QColor(255, 210, 210), QColor(255, 50, 60) ,QColor(255, 20, 20)
		});
		
	}
	setMessage_type(type);
	m_delay = delay;

	if (m_timerId == 0) {
        m_timerId = startTimer(m_delay);
	}
}

NotifyTipBox::NotifyTipBox(Message_type type,QWidget* parent)
	:NotifyTipBox(type,1000,parent)
{

}



NotifyTipBox::~NotifyTipBox()
{
	if (m_animation) {
		m_animation->stop();
		m_animation->deleteLater();
		m_animation = nullptr;
	}
	if (m_timerId) {
		killTimer(m_timerId);
		m_timerId = 0;
	}
}



void NotifyTipBox::setMessage_type(Message_type type)
{
	m_data = m_preDatas[type];
}


void NotifyTipBox::setTipData(TipData& data)
{
    m_data = data;
}

TipData NotifyTipBox::getTipData() const
{
	return m_data;
}



void NotifyTipBox::Begin_animate()
{

	Update_animate(
		100,
		1.0,
		1.0,
		0.6,
		0.4,
		2,
        [this]() {
        }
	);
	
	// 重置/重启计时器：每次 animate 都重新开始计时
	if (m_timerId) {
		killTimer(m_timerId);
		m_timerId = 0;
	}
	if (m_delay> 0)
		m_timerId = startTimer(m_delay);
}

void NotifyTipBox::Update_animate(
	int duration,
	qreal startValue,
	qreal endValue,
	double midPos,
	qreal midValue,
	int loopCount,
	std::function<void()> finishedCallback
)
{
	   // 如果还没有效果则创建
	if (!graphicsEffect()) {
		auto* effect = new QGraphicsOpacityEffect(this);
		effect->setOpacity(1.0);
		setGraphicsEffect(effect);
	}

	auto* effect = qobject_cast<QGraphicsOpacityEffect*>(graphicsEffect());
	if (!effect)
		return;

	if (m_animation) {
		if (m_animation->state() == QAbstractAnimation::Running)
			m_animation->stop();
		m_animation->deleteLater();
		m_animation = nullptr;
	}

	// 创建动画，作用于 effect 的 opacity 属性
	m_animation = new QPropertyAnimation(effect, "opacity", this);
	m_animation->setDuration(duration);                   // 每次闪烁周期（毫秒）
	m_animation->setStartValue(startValue);
	m_animation->setKeyValueAt((qreal)midPos, QVariant::fromValue(midValue)); // 中间透明度（越低越暗）
	m_animation->setEndValue(endValue);
	m_animation->setEasingCurve(QEasingCurve::InOutSine);
	m_animation->setLoopCount(loopCount);                    // 闪烁次数，-1 表示无限循环

	connect(m_animation, &QAbstractAnimation::finished, this, [this,finishedCallback]() {
		// 动画结束后不立即删除内存，使用 deleteLater 保证安全
		if (m_animation) {
			m_animation->deleteLater();
			m_animation = nullptr;
		}
		if(finishedCallback)
            finishedCallback();
		});

	m_animation->start();
}

void NotifyTipBox::End_animate()
{
	
	
	// 停掉计时器
	if (m_timerId) {
		killTimer(m_timerId);
		m_timerId = 0;
	}

	Update_animate(
		400,
		1.0,
		0.0,
		-1.0,
		0.0,
		1,
        [this]() {
            this->close();
        }
	);
}

void NotifyTipBox::closeEvent(QCloseEvent* event)
{
	emit disappeared(this);
	event->ignore();
}

void NotifyTipBox::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	
	painter.setPen(m_data.borderColor);
	painter.setBrush(m_data.backgroundColor);
	painter.drawRect(rect());

	painter.drawPixmap(QPoint(55,22), m_data.icon);

	auto font = painter.font();
	font.setPixelSize(13);
	font.setBold(true);
    painter.setFont(font);
	painter.setPen(m_data.textColor);
	painter.drawText(QPoint(75,35),m_data.msg);
}

void NotifyTipBox::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_timerId)
	{
		killTimer(m_timerId);
		m_delay = 0;	
		End_animate();
	}

}

