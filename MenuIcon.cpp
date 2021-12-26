#include "MenuIcon.h"

MenuIcon::MenuIcon(QWidget* parent) :
	QWidget(parent) {

	mainWidget = new QWidget(this);
	mainWidget->setFixedSize(40, 40);
	mainWidget->setStyleSheet("background-color:#00000000;border-radius:20px;");
	mainWidget->installEventFilter(this);

	QSvgRenderer renderer;
	renderer.load(QString(":/icons/icons/menu.svg"));
	QSize size = renderer.defaultSize();
	QPixmap* iconImg = new QPixmap(size);
	iconImg->fill(Qt::transparent);
	QPainter painter(iconImg);
	painter.setRenderHints(QPainter::Antialiasing);
	renderer.render(&painter);

	menulabel = new QLabel(mainWidget);
	menulabel->setPixmap(*iconImg);
	menulabel->setAlignment(Qt::AlignHCenter);
	menulabel->setFixedSize(24, 24);
	menulabel->move(8, 8);
	menulabel->setAttribute(Qt::WA_TransparentForMouseEvents);


	this->setFixedSize(40, 40);
}

bool MenuIcon::eventFilter(QObject* watched, QEvent* event) {
	if (watched == mainWidget) {
		if (event->type() == QEvent::Enter) {
			mainWidget->setStyleSheet("background-color:#3A3A3A;border-radius:20px;");
		}
		if (event->type() == QEvent::Leave) {
			mainWidget->setStyleSheet("background-color:#00000000;border-radius:20px;");
		}
		if (event->type() == QEvent::MouseButtonPress) {
			emit clicked();
		}
	}
	return QWidget::eventFilter(watched, event);
}