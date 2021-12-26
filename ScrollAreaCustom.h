#pragma once

#include <QTimer>
#include <Qwidget>
#include <QPainter>
#include <QStyleOption>
#include "ScrollIndicator.h"
#include "ScrollListContainer.h"
#define MAXSPEED 70

class ScrollAreaCustom;
class ScrollListContainer;
class ScrollIndicator;

class ScrollAreaCustom : public QWidget
{
    Q_OBJECT

private:
    QTimer* getCord;
    QTimer* rfrshView;

    ScrollListContainer* container;
    ScrollIndicator* indicator;

    QPropertyAnimation* bounce;

    bool pressed = false;
    bool scrollDown = true;
    bool outOfEdge = false;
    bool ignoreMaxSpeed = false;

    int strtY;
    int lastY;
    int bfEdgeY;    //last y value before out of edge

    int curSpd = 0;
    int damp = 1;
    int moveStored = 0;
    int nextMove = 1;

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void bounceBack();


public:
    explicit ScrollAreaCustom(QWidget* parent = nullptr);
    void addWidget(QWidget* newWidget, bool setAnimation = true);
    void addWidgets(QVector<QWidget*> widgets);
    void RemoveWidget(QWidget* w = nullptr);
    void scrollToTop();
    void updateHeight();
    void clear();

signals:

private slots:
    void scrollContainer();
    void updateSpd();
    void scrollIndicator(int dp);

};
