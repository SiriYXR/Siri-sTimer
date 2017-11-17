#pragma once

#include <QtWidgets/QWidget>
#include "ui_SirisTimer.h"

#include <QLabel>
#include <QSpinBox>
#include <QScrollBar>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QTimer>
#include <QMessageBox>
#include <QSystemTrayicon>
#include <QMenu>

class SirisTimer : public QWidget
{
	Q_OBJECT

public:
	SirisTimer(QWidget *parent = Q_NULLPTR);
private:
	void updateTimeStr();

	void doTask();
	void taskRemind();
	void taskShutDown();
	void taskRestart();
	
private slots:
	void Begin();
	void Pause();
	void Stop();
	void updateTime();
	void hideWindow();
	void showWindow();
	void on_activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);

private:
	Ui::SirisTimerClass ui;

	QLabel *label;
	QLabel *label2;
	QLabel *label3;
	QLabel *label4;
	QSpinBox *spinBox;
	QScrollBar *scrollBar;
	QComboBox *comboBox;
	QPushButton *buttonBegin;
	QLineEdit *lineEdit;

	QPushButton *buttonStop;
	QPushButton *buttonPause;
	QPushButton *buttonTray;

	QSystemTrayIcon *trayIcon;
	QMenu *trayMenu;
	QAction *showAction;
	QAction *pauseAction;
	QAction *stopAction;
	QAction *exitAction;

	QTimer *timer;

	int time;
	bool ispause;
	bool isrun;
};
