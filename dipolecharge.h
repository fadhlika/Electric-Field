#ifndef DIPOLECHARGE_H
#define DIPOLECHARGE_H

#include <QApplication>
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QDrag>
#include <QGraphicsSceneMouseEvent>
#include <QWidget>
#include <QDebug>
#include <QCursor>
#include <QMimeData>
#include <QGraphicsScene>

class DipoleCharge : public QGraphicsItem
{
public:
    DipoleCharge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    double Q;
    bool isConstructor;

    //int type() const;
    enum { Type = UserType + 7, TypeConstructor = UserType + 8};

protected:
    //void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DIPOLECHARGE_H
