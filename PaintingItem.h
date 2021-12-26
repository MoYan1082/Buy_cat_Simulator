#pragma once

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QPushButton>

class PaintingItem : public QWidget
{
	Q_OBJECT


public:
	PaintingItem(QWidget* parent = nullptr, QString name = "", int sellPrice = 0);
	QString getName();

private:
	QWidget* mainWidget;
	QHBoxLayout* mainHLayout;
	QWidget* getImgWidget(int width, int height, QString path, bool k = false);

	int sellPrice = 20;
	QString name, path, path1, path2;
signals:
	void add();

};

