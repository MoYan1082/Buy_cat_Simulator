#pragma once

#include <qwidget.h>

class SheildLayer : public QWidget {
    Q_OBJECT

private:
    bool pressed = false;
    bool enabled = true;

    QWidget* bg;

    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent* event);

public:
    SheildLayer(QWidget* parent = nullptr);
    void setEnabled(bool e);

signals:
    void clicked();

};
