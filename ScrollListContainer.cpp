#include "ScrollListContainer.h"

ScrollListContainer::ScrollListContainer(QWidget* parent) 
    : QWidget(parent) {
    size = 0;
    spacing = 3;

}

void ScrollListContainer::paintEvent(QPaintEvent* event) {
    for (int i = 0; i < widgets.size(); i++) {
        widgets[i]->resize(this->width(), widgets[i]->height());
    }
}

void ScrollListContainer::AddWidget(QWidget* widget, bool setAnimation) {
    // 增加高度
    this->resize(this->width(), this->height() + widget->height() + spacing);
    widgets.push_back(widget);
    size++;
    ys.push_back(0);
    // 适应宽度
    //widget->resize(this->width(), widget->height());
    widget->show();

    if (setAnimation) {
        QGraphicsOpacityEffect* widgetOpac = new QGraphicsOpacityEffect(widget);
        widgetOpac->setOpacity(0);
        widget->setGraphicsEffect(widgetOpac);

        QParallelAnimationGroup* dpGroup = new QParallelAnimationGroup;
        QSequentialAnimationGroup* newWidgetFadeIn = new QSequentialAnimationGroup;
        for (int i = 0; i < size - 1; i++) {
            ys[i] += widget->height() + spacing;
            QPropertyAnimation* move = new QPropertyAnimation(widgets[i], "pos");
            move->setDuration(750);
            move->setStartValue(widgets[i]->pos());
            move->setEndValue(QPoint(widgets[i]->x(), ys[i]));
            move->setEasingCurve(QEasingCurve::InOutQuart);
            dpGroup->addAnimation(move);
        }
        newWidgetFadeIn->addPause(300);
        QPropertyAnimation* fade = new QPropertyAnimation(widgetOpac, "opacity", widget);
        fade->setDuration(300);
        fade->setStartValue(0);
        fade->setEndValue(0.99);
        newWidgetFadeIn->addAnimation(fade);
        dpGroup->addAnimation(newWidgetFadeIn);
        dpGroup->start();
        connect(dpGroup, &QPropertyAnimation::stateChanged, [=]() {
            if (dpGroup->state() == QAbstractAnimation::Stopped) {
                if (widgetOpac->opacity() != 0.99) {
                    fade->start(QAbstractAnimation::DeleteWhenStopped);
                    connect(fade, &QPropertyAnimation::finished, [=]() {widgetOpac->deleteLater(); });
                }
                else {
                    dpGroup->deleteLater();
                    widgetOpac->deleteLater();
                }
            }
            });
    }
    else {
        for (int i = 0; i < size - 1; i++) {
            ys[i] += widget->height() + spacing;
            widgets[i]->move(QPoint(widgets[i]->pos().x(), ys[i]));
        }
    }
}

void ScrollListContainer::RemoveWidget(QWidget* widget) {
    int index = widgets.indexOf(widget);
    if (index == -1 || widget == nullptr) return;
    
    this->resize(this->width(), this->height() - widget->height() - spacing);
    this->parentWidget()->update();
    widget->move(0, 0);
    widget->hide();
    widget->setParent(nullptr);
    
    QParallelAnimationGroup* dpGroup = new QParallelAnimationGroup;
    for (int i = index - 1; i >= 0; i--) {
        ys[i] -= (widget->height() + spacing);
        QPropertyAnimation* move = new QPropertyAnimation(widgets[i], "pos");
        move->setDuration(750);
        move->setStartValue(widgets[i]->pos());
        move->setEndValue(QPoint(widgets[i]->x(), ys[i]));
        move->setEasingCurve(QEasingCurve::InOutQuart);
        dpGroup->addAnimation(move);
    }
    dpGroup->start(QAbstractAnimation::DeleteWhenStopped);
    widgets.remove(index);
    size--;
    ys.remove(index);
}

void ScrollListContainer::updateHeight() {
    for (int i = size - 2; i >= 0; i--) {
        ys[i] = ys[i + 1] + widgets[i + 1]->height() + spacing;
        widgets[i]->move(widgets[i]->pos().x(), ys[i]);
    }
    this->resize(this->width(), ys[0] + widgets[0]->height() + 3);
}

void ScrollListContainer::clear() {
    int n = size;
    for (int i = 0; i < n; i++)
        RemoveWidget();
}