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

class SearchBar : public QWidget {
	Q_OBJECT
	Q_PROPERTY(QColor color READ color WRITE setColor)

private:
	QLabel* SvgToQlabel(QString path);

	bool tagFocus = false;
	QWidget* border;
	QWidget* searchMainWidget;
	QLineEdit* lineEdit;
	QPushButton* clearButton;

public:
	SearchBar(QWidget *parent = nullptr);
	void clearFocus();
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	bool eventFilter(QObject* watched, QEvent* event);

	QColor color();
	void setColor(QColor color);

	
signals:
	void textEdited(QString text);
	void focusIn();
	void focusOut();
};

