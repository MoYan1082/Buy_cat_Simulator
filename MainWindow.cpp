#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    maximized = false;
    mousePressed = false;
    mouseState = 0;

    QTimer* t = new QTimer(this);
    connect(t, &QTimer::timeout, this, [=]() {Init(); });
    t->setSingleShot(true);
    t->start(10);

    connect(ui.adjSizeBtn, &QPushButton::clicked, this, [=]() {controlWindowScale(); });
}

void MainWindow::Init() {
    QPainterPath path;
    QRect mainMaskRect = ui.mainWidget->rect();
    mainMaskRect.setSize(mainMaskRect.size());
    path.addRoundedRect(mainMaskRect, cornerRadius, cornerRadius);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui.mainWidget->setMask(mask);

    QString mainStyle;
    ui.mainWidget->setObjectName("mainWidget");
    mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() +
        QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
    ui.mainWidget->setStyleSheet(mainStyle);

    windowShadow = new QGraphicsDropShadowEffect(this);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0, 0, 0));
    windowShadow->setOffset(0, 0);
    ui.mainWidget->setGraphicsEffect(windowShadow);
    
    border = new QWidget(this);
    border->move(ui.mainWidget->pos() - QPoint(1, 1));
    border->resize(ui.mainWidget->size() + QSize(2, 2));
    QString borderStyle;
    borderStyle = "background-color:#00FFFFFF;border:1.5px solid #686868; border-radius:" + QString::asprintf("%d", cornerRadius) + "px";
    border->setStyleSheet(borderStyle);
    border->setAttribute(Qt::WA_TransparentForMouseEvents);
    border->show();
    /*****************************************************************/
    // 设置logo
    QFont logoFont = QFont("Harlow Solid Italic", 25);
    logoLine = new QLineEdit(ui.mainWidget);
    logoLine->setFont(logoFont);
    logoLine->setText("Moyan");
    logoLine->setReadOnly(true);
    logoLine->setStyleSheet("color:#0096FA;background-color:#00000000;border-style:none;border-width:0px;");
    logoLine->move(10, 15);
    logoLine->setFixedSize(logoLine->size().width(), logoLine->size().height() + 12);
    logoLine->show();

    // 搜索框
    menuIcon = new MenuIcon();
    searchBar = new SearchBar(ui.mainWidget);
    searchBar->show(); 
    menuIcon->show();

    int shiftMargin = ((double)(ui.mainWidget->width() - searchBar->width()) / 2) - logoLine->width() - menuIcon->width() - 30;
    logoLine->setFixedSize(logoLine->size().width() + shiftMargin, logoLine->size().height());

    QWidget* titleInnerWidget = new QWidget(ui.mainWidget);
    QHBoxLayout* innerLayout = new QHBoxLayout();
    titleInnerWidget->setLayout(innerLayout);
    innerLayout->setContentsMargins(0, 0, 0, 0);
    innerLayout->setAlignment(Qt::AlignLeft);
    innerLayout->addWidget(menuIcon);
    innerLayout->addWidget(logoLine);
    innerLayout->addWidget(searchBar);
    /*****************************************************************/
    mainScroll = new ScrollAreaCustom(ui.mainWidget);
    mainScroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainScroll->setMinimumWidth(754 + 20);
    mainScroll->setMinimumHeight(300);

    // 将图片写入
    for(int i = 0; i < names.size(); i++) {
        QString it = names[i];
        int price = prices[i];
        PaintingItem* item = new PaintingItem(this, it, price);
        mainScroll->addWidget(item);
        paintings.push_back(item);
    }
    /*****************************************************************/
    // 侧边栏
    defaultSettingsPage = new SlidePage(cornerRadius, "Shopping Cart", ui.mainWidget);
    defaultSettingsPage->show();
    for (QString it : names) {
        GoodsItem* goodsItem = new GoodsItem(this, it);
        goods.push_back(goodsItem);
    }
    pageList.push_back(defaultSettingsPage);

    /*****************************************************************/
    // 阴影遮挡板
    mainShadow1 = new QWidget(ui.mainWidget);
    mainShadow1->move(0, 0);
    mainShadow1->resize(ui.mainWidget->size().width(), 48);
    mainShadow1->setStyleSheet("background-color:black; border-top-left-radius:" + QString::asprintf("%d", cornerRadius) + "px;" + 
        + "border-top-right-radius:" + QString::asprintf("%d", cornerRadius) + "px");
    mainShadow2 = new QWidget(ui.mainWidget);
    mainShadow2->move(0, 105);
    mainShadow2->resize(ui.mainWidget->size().width(), ui.mainWidget->size().height() - 110);
    mainShadow2->setStyleSheet("background-color:black; border-bottom-left-radius:" + QString::asprintf("%d", cornerRadius) + "px;" +
        +"border-bottom-right-radius:" + QString::asprintf("%d", cornerRadius) + "px");

    QGraphicsOpacityEffect* opacity = new QGraphicsOpacityEffect(this);
    opacity->setOpacity(0.5);
    mainShadow1->setGraphicsEffect(opacity);
    mainShadow2->setGraphicsEffect(opacity);
    mainShadow1->hide();
    mainShadow2->hide();
    mainShadow1->installEventFilter(this);
    mainShadow2->installEventFilter(this);
    /*****************************************************************/
    for (GoodsItem* it : goods) {
        connect(it, &GoodsItem::buy, this, [=]() {
            defaultSettingsPage->RemoveContent(it);
            });
    }
    for (PaintingItem* it : paintings) {
        connect(it, &PaintingItem::add, this, [=]() {
            for (GoodsItem* goodsIt : goods) {
                if (goodsIt->getName() == it->getName()) {
                    defaultSettingsPage->AddContent(goodsIt);
                    mainScroll->RemoveWidget(it);
                    for (int i = 0; i < paintings.size(); i++) {
                        if (paintings[i]->getName() == it->getName()) {
                            paintings.remove(i, 1);
                        }
                    }
                    break;
                }
            }
            });
    }
    connect(menuIcon, &MenuIcon::clicked, this, [=]() {
        searchBar->clearFocus();
        defaultSettingsPage->slideIn();
        });
    connect(searchBar, &SearchBar::focusIn, this, [=]() {
        mainShadow1->show();
        mainShadow2->show();
        });
    connect(searchBar, &SearchBar::focusOut, this, [=]() {
        mainShadow1->hide();
        mainShadow2->hide();
        });
    connect(searchBar, &SearchBar::textEdited, this, [=](QString text) {
        // 清空mainScroll内的组件
        for (int i = 0; i < paintings.size(); i++) {
            PaintingItem* it = paintings[i];
            it->hide();
            mainScroll->RemoveWidget(it);
        }
        
        if (text == "") {
            for (int i = 0; i < paintings.size(); i++) {
                PaintingItem* it = paintings[i];
                mainScroll->addWidget(it, false);
                it->show();
            }
        }
        else {
            for (int i = 0; i < paintings.size(); i++) {
                PaintingItem* it = paintings[i];
                if (it->getName().contains(QRegularExpression(text))) {
                    mainScroll->addWidget(it, false);
                    it->show();
                }
            }
        }
        });
    /*****************************************************************/
    ui.displayLayout->addWidget(titleInnerWidget);
    ui.displayLayout->addWidget(mainScroll);
    ui.displayLayout->setAlignment(Qt::AlignTop);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        mousePressed = true;
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::NoButton)
        mousePressed = false;
    if (!mousePressed) {
        mouseState = 0;
        if (!maximized && abs(event->pos().x() - ui.mainWidget->pos().x()) < 5)
            mouseState |= AT_LEFT;
        if (!maximized && abs(event->pos().y() - ui.mainWidget->pos().y()) < 5)
            mouseState |= AT_TOP;
        if (!maximized && abs(event->pos().x() - ui.mainWidget->pos().x() - ui.mainWidget->width()) < 5)
            mouseState |= AT_RIGHT;
        if (!maximized && abs(event->pos().y() - ui.mainWidget->pos().y() - ui.mainWidget->height()) < 5)
            mouseState |= AT_BOTTOM;
        if (mouseState == AT_TOP_LEFT || mouseState == AT_BOTTOM_RIGHT)
            setCursor(Qt::SizeFDiagCursor);
        else if (mouseState == AT_TOP_RIGHT || mouseState == AT_BOTTOM_LEFT)
            setCursor(Qt::SizeBDiagCursor);
        else if (mouseState & (AT_LEFT | AT_RIGHT))
            setCursor(Qt::SizeHorCursor);
        else if (mouseState & (AT_TOP | AT_BOTTOM))
            setCursor(Qt::SizeVerCursor);
        else
            unsetCursor();
    }
    else {
        if (mouseState == 0) {
            if (maximized) {
                qreal xRatio = (double)event->pos().x() / (double)ui.mainWidget->width();
                qreal yRatio = (double)event->pos().y() / (double)ui.mainWidget->height();
                controlWindowScale();
                this->move(QPoint(event->globalPosition().x() - ui.mainWidget->width() * xRatio,
                                  event->globalPosition().y() - ui.mainWidget->height() * yRatio));
                lastPos = QPoint(ui.mainWidget->width() * xRatio, ui.mainWidget->height() * yRatio);
            }
            else
                this->move(event->globalPosition().toPoint() - lastPos);
        }
        else {
            QPoint d = event->globalPosition().toPoint() - frameGeometry().topLeft() - lastPos;
            if (mouseState & AT_LEFT) {
                this->move(this->frameGeometry().x() + d.x(), this->frameGeometry().y());
                this->resize(this->width() - d.x(), this->height());
            }
            if (mouseState & AT_RIGHT) {
                this->resize(this->width() + d.x(), this->height());
            }
            if (mouseState & AT_TOP) {
                this->move(this->frameGeometry().x(), this->frameGeometry().y() + d.y());
                this->resize(this->width(), this->height() - d.y());
            }
            if (mouseState & AT_BOTTOM) {
                this->resize(this->width(), this->height() + d.y());
            }
        }
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    mousePressed = false; 
    if (event->globalPosition().y() < 2)  controlWindowScale(); 
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    if (logoLine) {
        int shiftMargin = ((double)(ui.mainWidget->width() - searchBar->width()) / 2) - logoLine->width() - menuIcon->width();
        logoLine->setFixedSize(logoLine->size().width() + shiftMargin, logoLine->size().height());
    }
    if (border)
        border->resize(ui.mainWidget->size() + QSize(2, 2));
    
    QPainterPath path;
    path.addRoundedRect(ui.mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
    QRegion mask(path.toFillPolygon().toPolygon());
    ui.mainWidget->setMask(mask);
    if (mainShadow1) {
        mainShadow1->resize(ui.mainWidget->size().width(), 48);
    }
    if (mainShadow2) {
        mainShadow2->resize(ui.mainWidget->size().width(), ui.mainWidget->size().height() - 110);
    }

    //Resize all pages
    for (int i = 0; i < pageList.size(); i++) {
        pageList[i]->resize(ui.mainWidget->width() * 0.3 < pageList[i]->preferWidth ? pageList[i]->preferWidth - 1 : ui.mainWidget->width() * 0.3 - 1, ui.mainWidget->height());
        pageList[i]->resize(pageList[i]->width() + 1, pageList[i]->height());
    }
}

void MainWindow::controlWindowScale() {
    if (!maximized) {
        lastGeometry = this->frameGeometry();
        windowShadow->setEnabled(false);
        border->hide();
        ui.verticalLayout->setContentsMargins(0, 0, 0, 0);

        QString mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + ";border-radius:0px;}";
        ui.mainWidget->setStyleSheet(mainStyle);
        this->showMaximized();
        maximized = true;
        QPainterPath path;
        path.addRect(ui.mainWidget->rect());
        QRegion mask(path.toFillPolygon().toPolygon());
        ui.mainWidget->setMask(mask);
    }
    else {
        ui.verticalLayout->setContentsMargins(30, 30, 30, 30);
        this->showNormal();
        QString mainStyle = "QWidget#mainWidget{background-color:" + mainBackGround.name() + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
        ui.mainWidget->setStyleSheet(mainStyle);
        QPainterPath path;
        path.addRoundedRect(ui.mainWidget->rect(), cornerRadius - 1, cornerRadius - 1);
        QRegion mask(path.toFillPolygon().toPolygon());
        ui.mainWidget->setMask(mask);
        border->show();
        windowShadow->setEnabled(true);
        this->resize(lastGeometry.width(), lastGeometry.height());
        this->move(lastGeometry.x(), lastGeometry.y());
        maximized = false;
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event) {
    if (watched == mainShadow1 || watched == mainShadow2) {
        if (event->type() == QEvent::MouseButtonPress) {

            if(searchBar) searchBar->clearFocus();
        }
    }
    return QWidget::eventFilter(watched, event);
}