#pragma once

#include <QPainter>
#include <QSvgRenderer>
#include <qpushbutton.h>

class CustomIcon : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(qreal rotationAngle READ rotationAngle WRITE setRotationAngle NOTIFY rotationAngleChanged)
private:
    int radius;
    qreal widgetRatio;
    qreal iconSizeRate = 0.8;
    qreal rotation = 0;
    QPixmap* iconImg;

    /* for hover and click effects */
    QColor bgColor;
    QColor defaultColor = QColor(0, 0, 0, 0);
    QColor hoverColor = QColor(58, 58, 58);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

protected:
    qreal rotationAngle() const;

public:
    CustomIcon(QString iconPath, int r = 0, QWidget* parent = nullptr);
    CustomIcon(const QPixmap& icon, int r = 0, QWidget* parent = nullptr);

    void setRotationAngle(qreal angle = 0);

signals:
    void rotationAngleChanged();
};

