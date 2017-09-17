#ifndef ELECTRICFIELD_H
#define ELECTRICFIELD_H

#include <QObject>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsItem>
#include <QList>
#include <QRectF>
#include <QGraphicsScene>
#include <QVariant>
#include <QApplication>
#include <QDesktopWidget>
#include <QTimer>
#include <math.h>

#include "charge.h"
#include "arrow.h"
#include "testcharge.h"


class ElectricField : public QGraphicsScene
{

public:
    ElectricField(QObject *parent = Q_NULLPTR);
    void InitializeField();
    void CalculateField();
    void CalculateForce();

    void StartTest();
    void StopTest();

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    const double K = 8.987552e9;
    const double mp = 1.6726219e-27;
    const double me = 9.10938356e-31;
    int NGridX;
    int NGridY;
    int GridW;
    double SceneToGridX(QPointF);
    double SceneToGridY(QPointF);
    double GridToSceneX(QPointF);
    double GridToSceneY(QPointF);

    TestCharge *testCharge;
    double Vx, Vy;
    double x, y;
    double dt;

    QTimer *timer;
};

#endif // ELECTRICFIELD_H
