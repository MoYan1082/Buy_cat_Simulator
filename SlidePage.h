#pragma once

#include <QLabel>
#include <QVBoxLayout>

#include "CustomIcon.h"
#include "SheildLayer.h"
#include "ScrollAreaCustom.h"

class SlidePage : public QWidget
{
    Q_OBJECT
private:
    int cornerRadius;
    QString pageName;
    ScrollAreaCustom* pageContentContainer;
    QLabel* nameLabel;
    CustomIcon* backIcon;
    SheildLayer* sheildLayer;
    QWidget* bgWidget;
    QFont textFont = QFont("Corbel Light", 24);

    bool onShown = false;
    QParallelAnimationGroup* curAni = nullptr;
    QGraphicsOpacityEffect* opacity;

    void resizeEvent(QResizeEvent* event);

public:
    const int preferWidth = 350;
    explicit SlidePage(int radius, QString name, QWidget* parent = nullptr);
    void SetRadius(int radius);
    void SetName(QString name);
    void AddContent(QWidget* widget);
    void AddContents(QVector<QWidget*> widgets);
    void RemoveContent(QWidget* widget);
    void RemoveContents(QVector<QWidget*> widgets);
    void UpdateContents();
    void ScrollToTop();

signals:
    void sizeChange();

public slots:
    void slideIn();
    void slideOut();

};