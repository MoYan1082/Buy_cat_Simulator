#include "CustomIcon.h"

CustomIcon::CustomIcon(QString iconPath, int r, QWidget* parent) :
    QPushButton(parent),
    radius(r) {
    QSvgRenderer renderer;
    renderer.load(iconPath);
    QSize size = renderer.defaultSize();
    iconImg = new QPixmap(size);
    iconImg->fill(Qt::transparent);
    QPainter painter(iconImg);
    painter.setRenderHints(QPainter::Antialiasing);
    renderer.render(&painter);

    widgetRatio = iconImg->height() / iconImg->width();
    bgColor = defaultColor;
}

CustomIcon::CustomIcon(const QPixmap& icon, int r, QWidget* parent) :
    QPushButton(parent),
    radius(r) {
    iconImg = new QPixmap(icon);

    widgetRatio = iconImg->height() / iconImg->width();
    bgColor = defaultColor;
}

void CustomIcon::paintEvent(QPaintEvent* event) {
    resize(height() / widgetRatio, height());

    QPainter bgPainter(this);
    bgPainter.setRenderHints(QPainter::Antialiasing);
    bgPainter.setPen(Qt::NoPen);
    bgPainter.setBrush(bgColor);
    bgPainter.drawRoundedRect(this->rect(), radius, radius);

    QPainter pixmapPainter(this);
    pixmapPainter.setRenderHints(QPainter::Antialiasing);
    pixmapPainter.translate(width() / 2, height() / 2);
    pixmapPainter.rotate(rotation);
    pixmapPainter.translate(-width() / 2, -height() / 2);
    int w = iconSizeRate * width();
    int h = iconSizeRate * height();
    pixmapPainter.drawPixmap(width() / 2 - w / 2, height() / 2 - h / 2, w, h, *iconImg);
}

void CustomIcon::enterEvent(QEnterEvent* event) {
    bgColor = hoverColor;
    update();
}

void CustomIcon::leaveEvent(QEvent* event) {
    bgColor = defaultColor;
    update();
}

void CustomIcon::mousePressEvent(QMouseEvent* event) {
    emit clicked();
    setFocus();
    iconSizeRate -= 0.1;
    update();
}

void CustomIcon::mouseReleaseEvent(QMouseEvent* event) {
    iconSizeRate += 0.1;
    update();
}

void CustomIcon::setRotationAngle(qreal angle) {
    rotation = angle;
    update();
}

qreal CustomIcon::rotationAngle() const {
    return rotation;
}