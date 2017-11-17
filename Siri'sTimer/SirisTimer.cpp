#include "SirisTimer.h"
#include <QDebug>

#include <windows.h>


SirisTimer::SirisTimer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setFixedSize(400, 200);
	this->setWindowIcon(QIcon(":/SirisTimer/timer"));

	label = new QLabel(this);
	label->setText(u8"设定时间:");
	label->move(20, 10);
	label->setStyleSheet("font-size:15px;");

	spinBox = new QSpinBox(this);
	spinBox->setGeometry(QRect(20, 40, 80, 25));
	spinBox->setRange(0, 1440);
	spinBox->setSuffix(u8"分钟");
	spinBox->setValue(30);

	scrollBar = new QScrollBar(this);
	scrollBar->setGeometry(QRect(120, 40, 270, 25));
	scrollBar->setOrientation(Qt::Horizontal);
	scrollBar->setPageStep(10);
	scrollBar->setValue(30);
	scrollBar->setRange(0, 120);

	connect(scrollBar, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), scrollBar, SLOT(setValue(int)));

	label2 = new QLabel(this);
	label2->setText(u8"设定任务:");
	label2->move(20, 80);
	label2->setStyleSheet("font-size:15px;");

	comboBox = new QComboBox(this);
	comboBox->setGeometry(QRect(20, 100, 100, 25));
	QStringList str;
	str << u8"提醒" << u8"关机" << u8"重启";
	comboBox->addItems(str);

	lineEdit = new QLineEdit(this);
	lineEdit->setGeometry(QRect(130, 100, 250, 25));
	lineEdit->setMaxLength(20);

	buttonBegin = new QPushButton(this);
	buttonBegin->setGeometry(QRect(170, 150, 60, 30));
	buttonBegin->setText(u8"开始");
	connect(buttonBegin, SIGNAL(clicked()), this, SLOT(Begin()));

	label3 = new QLabel(this);
	label3->setText(u8"倒计时");
	label3->move(160, 10);
	label3->setStyleSheet("font-size:30px;");
	label3->setHidden(true);

	label4 = new QLabel(this);
	label4->setText(u8"00:00:00");
	label4->move(40, 50);
	label4->setStyleSheet("font-size:80px;color:#00BFFF;");
	label4->setHidden(true);

	buttonPause = new QPushButton(this);
	buttonPause->setGeometry(QRect(90, 150, 60, 30));
	buttonPause->setText(u8"暂停");
	buttonPause->setHidden(true);
	connect(buttonPause, SIGNAL(clicked()), this, SLOT(Pause()));

	buttonStop = new QPushButton(this);
	buttonStop->setGeometry(QRect(170, 150, 60, 30));
	buttonStop->setText(u8"取消");
	buttonStop->setHidden(true);
	connect(buttonStop, SIGNAL(clicked()), this, SLOT(Stop()));

	buttonTray = new QPushButton(this);
	buttonTray->setGeometry(QRect(250, 150, 60, 30));
	buttonTray->setText(u8"托盘");
	buttonTray->setHidden(true);
	connect(buttonTray, SIGNAL(clicked()), this, SLOT(hideWindow()));

	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(QIcon(":/SirisTimer/timer"));
	trayIcon->setToolTip("Siri'sTimer");
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

	showAction = new QAction(u8"显示主界面", this);
	connect(showAction, SIGNAL(triggered()), this, SLOT(showWindow()));
	pauseAction = new QAction(u8"暂停任务", this);
	connect(pauseAction, SIGNAL(triggered()), this, SLOT(Pause()));
	stopAction = new QAction(u8"停止任务", this);
	connect(stopAction, SIGNAL(triggered()), this, SLOT(Stop()));
	exitAction = new QAction(u8"退出程序", this);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	trayMenu = new QMenu(this);
	trayMenu->addAction(showAction);
	trayMenu->addSeparator();
	trayMenu->addAction(pauseAction);
	trayMenu->addAction(stopAction);
	trayMenu->addSeparator();
	trayMenu->addAction(exitAction);
	trayIcon->setContextMenu(trayMenu);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

	time = 0;
	ispause = false;
	isrun = false;
	timer->start(1000);
}

void SirisTimer::Begin()
{
	label->setHidden(true);
	label2->setHidden(true);
	spinBox->setHidden(true);
	scrollBar->setHidden(true);
	comboBox->setHidden(true);
	buttonBegin->setHidden(true);
	lineEdit->setHidden(true);
	label3->setHidden(false);
	label4->setHidden(false);
	buttonPause->setHidden(false);
	buttonStop->setHidden(false);
	buttonTray->setHidden(false);

	ispause = false;
	isrun = true;
	time = spinBox->value() * 60;
}

void SirisTimer::updateTimeStr()
{
	QString str;
	str.sprintf("%02d:%02d:%02d", time / 3600, (time % 3600) / 60, time % 60);
	label4->setText(str);
}


void SirisTimer::doTask()
{
	int index = comboBox->currentIndex();
	switch (index) {
	case 0:
		taskRemind();
		break;
	case 1:
		taskShutDown();
		break;
	case 2:
		taskRestart();
		break;
	default:
		return;
	}
}

void SirisTimer::taskRemind()
{
	QMessageBox::information(this, u8"提醒！", lineEdit->text());
}

void SirisTimer::taskShutDown()
{
	ShellExecute(0, L"open", L"shutdown.exe", L"/s /t 60", 0, 0);
}

void SirisTimer::taskRestart()
{
	ShellExecute(0, L"open", L"shutdown.exe", L"/r /t 60", 0, 0);
}

void SirisTimer::updateTime()
{
	if (isrun) {
		if (!ispause) {
			updateTimeStr();
			if (time)
				time--;
			else {
				showWindow();
				doTask();
				Stop();
			}
		}
	}
	else {

	}
}

void SirisTimer::hideWindow()
{
	this->hide();
	trayIcon->show();
}

void SirisTimer::showWindow()
{
	this->show();
	trayIcon->hide();
}

void SirisTimer::on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		trayIcon->showMessage("Siri's Timer", u8"欢迎使用此程序", QSystemTrayIcon::Information, 1000);
		break;
	case QSystemTrayIcon::DoubleClick:
		showWindow();
		break;
	default:
		break;
	}
}

void SirisTimer::Pause()
{
	ispause = !ispause;
	if (ispause) {
		buttonPause->setText(u8"继续");
		pauseAction->setText(u8"继续任务");
	}
	else {
		buttonPause->setText(u8"暂停");
		pauseAction->setText(u8"暂停任务");
	}
}

void SirisTimer::Stop()
{
	label->setHidden(false);
	label2->setHidden(false);
	spinBox->setHidden(false);
	scrollBar->setHidden(false);
	comboBox->setHidden(false);
	buttonBegin->setHidden(false);
	lineEdit->setHidden(false);
	label3->setHidden(true);
	label4->setHidden(true);
	buttonPause->setHidden(true);
	buttonStop->setHidden(true);
	buttonTray->setHidden(true);

	ispause = true;
	isrun = false;
}
