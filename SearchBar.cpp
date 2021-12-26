#include "SearchBar.h"

SearchBar::SearchBar(QWidget* parent) :
	QWidget(parent) {

	searchMainWidget = new QWidget(this);
	searchMainWidget->resize(432, 40);
	searchMainWidget->setStyleSheet("background-color:#3A3A3A;border-radius:4px;");
	searchMainWidget->move(6, 6);

	border = new QWidget(this);
	border->move(searchMainWidget->pos() - QPoint(5, 5));
	border->resize(searchMainWidget->size() + QSize(10, 10));
	border->setStyleSheet("background-color:#00FFFFFF;border:5px solid #154565; border-radius:10px");
	border->setAttribute(Qt::WA_TransparentForMouseEvents);
	border->hide();

	QFont textFont = QFont("Corbel", 14);
	lineEdit = new QLineEdit();
	lineEdit->setFixedHeight(22);
	lineEdit->setFont(textFont);
	lineEdit->resize(378, 22);
	lineEdit->setStyleSheet("background-color:#00000000;border-radius:4px;");
	lineEdit->setPlaceholderText(QStringLiteral("SEARCH"));	
	QPalette palette = lineEdit->palette();
	palette.setColor(QPalette::PlaceholderText, Qt::gray);
	palette.setColor(QPalette::Text, Qt::white);
	lineEdit->setPalette(palette);
	lineEdit->installEventFilter(this);

	QLabel* label = SvgToQlabel(":/icons/icons/search.svg");
	label->setAlignment(Qt::AlignHCenter);
	label->setMaximumSize(16, 16);
	label->setContentsMargins(0, 1, 0, 0);

	clearButton = new QPushButton();
	clearButton->setMaximumSize(16, 16);
	clearButton->setStyleSheet("background-color:#272727;border-radius:8px;");
	QLabel*  clearLabel = SvgToQlabel(":/icons/icons/clear.svg");
	clearLabel->setAlignment(Qt::AlignHCenter);
	clearLabel->setParent(clearButton);
	clearButton->hide();

	QHBoxLayout* mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(16, 9, 16, 9);
	mainLayout->addWidget(label);
	mainLayout->addWidget(lineEdit);
	mainLayout->addWidget(clearButton);
	searchMainWidget->setLayout(mainLayout);

	this->setFixedSize(border->size());

	connect(lineEdit, &QLineEdit::textChanged, this, [=]() {
		if (lineEdit->text() != "")
			clearButton->show();
		else
			clearButton->hide();
		emit textEdited(lineEdit->text());
		});

	connect(lineEdit, &QLineEdit::textEdited, this, [=]() {
		emit textEdited(lineEdit->text());
		});

	connect(clearButton, &QPushButton::clicked, this, [=]() {
		if (lineEdit->text() != "")
			lineEdit->setText("");
		});

}

void SearchBar::enterEvent(QEnterEvent* event) {
	if (!tagFocus) {
		QPropertyAnimation* animation = new QPropertyAnimation(this, "color");
		animation->setDuration(100);
		animation->setStartValue(QColor(58, 58, 58));
		animation->setEndValue(QColor(82, 82, 82));
		animation->start();
	}
}
void SearchBar::leaveEvent(QEvent* event) {
	if (!tagFocus) {
		QPropertyAnimation* animation = new QPropertyAnimation(this, "color");
		animation->setDuration(30);
		animation->setStartValue(QColor(82, 82, 82));
		animation->setEndValue(QColor(58, 58, 58));
		animation->start();
	}
}

void SearchBar::setColor(QColor color) {
	this->searchMainWidget->setStyleSheet(QString("background-color: rgb(%1, %2, %3);border-radius:4px;")
		.arg(color.red()).arg(color.green()).arg(color.blue()));
}

QColor SearchBar::color() {
	return Qt::black;
}

void SearchBar::clearFocus() {
	lineEdit->clearFocus();
}

QLabel* SearchBar::SvgToQlabel(QString path) {
	QSvgRenderer renderer;
	renderer.load(path);
	QSize size = renderer.defaultSize();
	QPixmap* iconImg = new QPixmap(size);
	iconImg->fill(Qt::transparent);
	QPainter painter(iconImg);
	painter.setRenderHints(QPainter::Antialiasing);
	renderer.render(&painter);

	QLabel* label = new QLabel();
	label->setPixmap(*iconImg);
	return label;
}

bool SearchBar::eventFilter(QObject* watched, QEvent* event) {
	if (watched == lineEdit) {
		if (event->type() == QEvent::FocusIn) {
			emit focusIn();
			border->show();
			tagFocus = true;
			searchMainWidget->setStyleSheet("background-color:#3A3A3A;border-radius:4px;");
		}
		else if (event->type() == QEvent::FocusOut) {
			emit focusOut();
			border->hide();
			tagFocus = false;
		}
	}
	return QWidget::eventFilter(watched, event);     // 将事件交给上层对话框
}