#pragma once

#include <QColor>
#include <QTimer>
#include <QEvent>
#include <Qwidget>
#include <QPainter>
#include <QEnterEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEasingCurve>
#include <QPropertyAnimation>

class ScrollIndicator :
    public QWidget
{
    Q_OBJECT

private:
    const QColor defaultColor = QColor(142, 198, 240);
    const QColor hoverColor = QColor(0, 150, 250);
    const QColor pressColor = QColor(0, 150, 250);
    QColor curColor;
    QTimer* hovTimer;
    QTimer* aniPause;

    int lastY;
    int margin;
    int defaultWidth;
    int defaultWidthAtFocus;
    bool pressed;

    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

public:
    explicit ScrollIndicator(QWidget* parent = nullptr);

signals:
    void scrollPage(int);

private slots:
    void setHoverActive();
};