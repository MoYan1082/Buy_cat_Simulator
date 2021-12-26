#include "GoodsItem.h"

GoodsItem::GoodsItem(QWidget* parent, QString name) :
	QWidget(parent), name(name) {
	QWidget* mainWidget = new QWidget(this);
	mainWidget->setFixedSize(300, 100);
	/*************************************************************/
	QPixmap pix(":/img/img/#" + name + "-3.jpg");
	pix = pix.scaled(QSize(70, 70), Qt::KeepAspectRatio);
	QLabel* imgLabel = new QLabel(mainWidget);
	imgLabel->setScaledContents(true);
	imgLabel->setPixmap(pix);
	
	// ÉèÖÃÃÉ°æ
	QWidget* imgWidget = new QWidget(mainWidget);
	imgWidget->setFixedSize(70, 70);
	imgWidget->hide();
	QPainterPath path;
	QRect mainMaskRect = imgWidget->rect();
	mainMaskRect.setSize(mainMaskRect.size());
	path.addRoundedRect(mainMaskRect, 35, 35);
	QRegion mask(path.toFillPolygon().toPolygon());
	imgLabel->setMask(mask);

	// Ïû³ý¾â³Ý
	QWidget* border = new QWidget(mainWidget);
	border->resize(72, 72);
	border->move(8.8, 10);
	border->setStyleSheet("background-color:#00000000;border:3px solid #686868;border-radius:36px;");
	/*************************************************************/

	QFont titleFont = QFont("Bahnschrift", 15);
	QLineEdit* nameLine = new QLineEdit(mainWidget);
	nameLine->setFont(titleFont);
	nameLine->setText("Name: " + name);
	nameLine->setReadOnly(true);
	nameLine->setStyleSheet("color:#858585;background-color:#00000000;border-style:none;border-width:0px;");

	buyButton = new QPushButton(mainWidget);
	buyButton->setFixedSize(60, 30);
	buyButton->setText("BUY");
	buyButton->setStyleSheet("color:white;background-color:#0096FA;border-radius:15px;");
	buyButton->setCursor(Qt::PointingHandCursor);
	buyButton->installEventFilter(this);
	connect(buyButton, &QPushButton::clicked, this, [=]() {
		emit buy();
		});

	QVBoxLayout* vLayout = new QVBoxLayout(mainWidget);
	vLayout->addWidget(nameLine);
	vLayout->addWidget(buyButton);
	QWidget* nameWidget = new QWidget(mainWidget);
	nameWidget->setLayout(vLayout);
	nameWidget->resize(nameWidget->size().width(), nameWidget->size().height() + 50);
	/*************************************************************/

	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	mainWidget->setLayout(mainLayout);
	mainLayout->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	mainLayout->addWidget(imgLabel);
	mainLayout->addWidget(nameWidget);

	this->setStyleSheet("background-color:#00000000;border-radius:10px;");
	this->setFixedSize(300, 100);
}

bool GoodsItem::eventFilter(QObject* watched, QEvent* event) {
	if (watched == buyButton) {
		if (event->type() == QEvent::Enter) {
			buyButton->setStyleSheet("color:white;background-color:#1FA3FB;border-radius:15px;");
		}
		if (event->type() == QEvent::Leave) {
			buyButton->setStyleSheet("color:white;background-color:#0096FA;border-radius:15px;");
		}
	}
	return QWidget::eventFilter(watched, event);
}

QString GoodsItem::getName() {
	return this->name;
}

void GoodsItem::enterEvent(QEnterEvent* event) {
	this->setStyleSheet("background-color:#3A3A3A;border-radius:10px;");
}

void GoodsItem::leaveEvent(QEvent* event) {
	this->setStyleSheet("background-color:#00000000;border-radius:10px;");
}