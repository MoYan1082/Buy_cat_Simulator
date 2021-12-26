#include "PaintingItem.h"

PaintingItem::PaintingItem(QWidget* parent, QString name, int sellPrice) :
	QWidget(parent), name(name), sellPrice(sellPrice) {
	path = ":/img/img/" + name + ".jpg";
	path1 = ":/img/img/#" + name + "-1.jpg";
	path2 = ":/img/img/#" + name + "-2.jpg";
	/*************************************************************/
	mainWidget = new QWidget(this);
	mainWidget->setFixedSize(754, 234);
	mainWidget->setStyleSheet("background-color:#3A3A3A;border-radius:10px");
	mainWidget->installEventFilter(this);
	/*************************************************************/
	QWidget* imgWidget = getImgWidget(170, 200, path, true);
	imgWidget->move(17, 17);
	QWidget* imgWidget1 = getImgWidget(200, 95, path1);
	imgWidget1->move(192, 17);
	QWidget* imgWidget2 = getImgWidget(200, 95, path2);
	imgWidget2->move(192, 17 + 5 + imgWidget1->height());
	/*************************************************************/
	QFont titleFont = QFont("Bahnschrift", 24);
	QLineEdit* nameLine = new QLineEdit(mainWidget);
	nameLine->setFont(titleFont);
	nameLine->setText("Name " + name);
	nameLine->setMinimumWidth(200);
	nameLine->setReadOnly(true);
	nameLine->setStyleSheet("color:white;background-color:#00000000;border-style:none;border-width:0px;margin-left:1px;");
	nameLine->move(500, 40);
	QFont titleFont2 = QFont("Bahnschrift", 20);
	QLineEdit* sellLine = new QLineEdit(mainWidget);
	sellLine->setFont(titleFont2);
	sellLine->setText(QString("Price: %1$").arg(sellPrice));
	sellLine->setMinimumWidth(200);
	sellLine->setReadOnly(true);
	sellLine->setStyleSheet("color:white;background-color:#00000000;border-style:none;border-width:0px;margin-left:1px;");
	sellLine->move(500, 70);
	/*************************************************************/
	QPushButton* addButton = new QPushButton(mainWidget);
	addButton->setText("ADD");
	addButton->setStyleSheet("color:white;background:#C87E87;border-radius:4px;");
	addButton->setFixedSize(92, 40);
	addButton->move(500, 150);
	addButton->setCursor(Qt::PointingHandCursor);
	connect(addButton, &QPushButton::clicked, this, [=]() {
		emit add();
		});
	/*************************************************************/
	mainHLayout = new QHBoxLayout(this);
	mainHLayout->setAlignment(Qt::AlignHCenter);
	mainHLayout->addWidget(mainWidget);
	this->setLayout(mainHLayout);
	this->setFixedHeight(234 + 10);
}

QString PaintingItem::getName() {
	return this->name;
}

QWidget* PaintingItem::getImgWidget(int width, int height, QString path, bool k) {
	QPixmap pix(path);
	QLabel* mainLabel = new QLabel(mainWidget);
	mainLabel->setScaledContents(true);
	if ((double)pix.height() / pix.width() > (double)height / width) {
		mainLabel->setFixedSize(height * pix.width() / pix.height(), height);
		pix.scaled(height * pix.width() / pix.height(), height, Qt::KeepAspectRatio);
	} else {
		mainLabel->setFixedSize(width, width * pix.height() / pix.width());
		pix.scaled(width, width * pix.height() / pix.width(), Qt::KeepAspectRatio);
	}
	mainLabel->setPixmap(pix);

	QWidget* imgWidget = new QWidget(mainWidget);
	imgWidget->resize(width, height);
	QHBoxLayout* imgLayout = new QHBoxLayout(imgWidget);
	if(k) imgLayout->setAlignment(Qt::AlignHCenter);
	else  imgLayout->setAlignment(Qt::AlignLeft);
	imgLayout->addWidget(mainLabel);
	imgWidget->setLayout(imgLayout);

	return imgWidget;
}