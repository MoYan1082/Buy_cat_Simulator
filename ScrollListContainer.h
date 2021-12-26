#pragma once

#include <Qwidget>
#include <QLineEdit>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>

class ScrollListContainer : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollListContainer(QWidget* parent = nullptr);
    void AddWidget(QWidget* widget, bool setAnimation = true);
    void RemoveWidget(QWidget* widget = nullptr);
    void updateHeight();
    void clear();

private:
    int spacing = 3;
    QVector<QWidget*> widgets;
    int size = 0;
    QVector<int> ys;

    void paintEvent(QPaintEvent* event);

signals:

private slots:

};

