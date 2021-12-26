#pragma once

#include <QEvent>
#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainterPath>

class GoodsItem : public QWidget 
{
    Q_OBJECT
private:
    QString name = "";
    QPushButton* buyButton = nullptr;

public:
    GoodsItem(QWidget* parent = nullptr, QString name = "");
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event);
    QString getName();

signals:
    void buy();
};

