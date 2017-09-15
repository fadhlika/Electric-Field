#ifndef ELECTRICFIELDVIEW_H
#define ELECTRICFIELDVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>
#include <QWidget>

class ElectricFieldView : public QGraphicsView
{
public:
    ElectricFieldView(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);

    void resizeEvent(QResizeEvent *event);
};

#endif // ELECTRICFIELDVIEW_H
