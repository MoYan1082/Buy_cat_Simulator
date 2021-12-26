#pragma once

#include <QFont>
#include <QTimer>
#include <QMovie>
#include <QString>
#include <QWidget>
#include <QVector>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainterPath>
#include <QRegularExpression>
#include <QtWidgets/QMainWindow>
#include <QGraphicsDropShadowEffect>

#include "MenuIcon.h"
#include "GoodsItem.h"
#include "SlidePage.h"
#include "SearchBar.h"
#include "PaintingItem.h"
#include "ui_MainWindow.h"
#include "ScrollAreaCustom.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindow ui;
    
    bool maximized;
    bool mousePressed;
    int mouseState;
    const int cornerRadius = 20;
    const QColor mainBackGround = QColor(31, 31, 31);
    
    QRect lastGeometry;
    QPoint lastPos;
    QWidget* border = nullptr;
    QWidget* mainShadow1 = nullptr;
    QWidget* mainShadow2 = nullptr;
    QGraphicsDropShadowEffect* windowShadow;

    MenuIcon* menuIcon = nullptr;
    SearchBar* searchBar = nullptr;
    QLineEdit* logoLine = nullptr;
    QVector<GoodsItem*> goods;
    QVector<PaintingItem*> paintings;
    QVector<SlidePage*> pageList;
    QVector<QString> names = {
        "dahuang", "liangqian", "wushi", "huahua", "naiyou"
    };
    QVector<int> prices = {
        400, 2000, 50, 500, 500
    };
    SlidePage* createNewPage = nullptr;
    SlidePage* defaultSettingsPage = nullptr;
    ScrollAreaCustom* mainScroll = nullptr;

    enum {
        AT_LEFT = 1, AT_TOP = 2, AT_RIGHT = 4, AT_BOTTOM = 8,
        AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12
    };
    
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool eventFilter(QObject* watched, QEvent* event);
    
    void Init();
    void controlWindowScale();
};
