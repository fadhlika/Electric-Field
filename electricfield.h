#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H

#include <QObject>
#include <QGraphicsSceneDragDropEvent>
#include <QList>
#include <QRectF>
#include <QGraphicsScene>
#include <QVariant>
#include <QApplication>
#include <QDesktopWidget>
#include "charge.h"
#include "arrow.h"
#include <math.h>

class ElectricField : public QGraphicsScene
{
public:
    ElectricField(QObject *parent = Q_NULLPTR);
    void InitializeField();
    void CalculateField();
    enum { ChargeNormal = 65537, ChargeConstructor = 65538, ArrowField = 65539};

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    int NGridX;
    int NGridY;
    int GridW;
    double x;
    double y;
    const double K = 8.987552e9;
    int SceneToGridX(QPointF);
    int SceneToGridY(QPointF);
    QGraphicsItem *item;
};

#endif // ELECTRICFIELD_H
