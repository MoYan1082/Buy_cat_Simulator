#include "SheildLayer.h"

void SheildLayer::mousePressEvent(QMouseEvent* event) {
    if (enabled)
        pressed = true;
}

void SheildLayer::mouseReleaseEvent(QMouseEvent* event) {
    if (enabled && pressed)emit clicked(); pressed = false;
}

void SheildLayer::resizeEvent(QResizeEvent* event) {
    bg->resize(this->parentWidget()->size());
}

SheildLayer::SheildLayer(QWidget* parent) : QWidget(parent) {
    bg = new QWidget(this);
    bg->resize(parent->size());
    bg->setStyleSheet("background-color:#5a000000");
    bg->setAttribute(Qt::WA_TransparentForMouseEvents);
    bg->show();
}

void SheildLayer::setEnabled(bool e) {
    enabled = e;
}