#pragma once

#include <QLabel>
#include <QDebug>
#include <QWidget>
#include <QPainter>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QSvgRenderer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include "SearchBar.h"

class MenuIcon : public QWidget
{
	Q_OBJECT
private:

	
public:
	MenuIcon(QWidget* parent = nullptr);

	QLabel* menulabel;
	QWidget* mainWidget;
	bool eventFilter(QObject* watched, QEvent* event);

signals:
	void clicked();
};

