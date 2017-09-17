#ifndef TESTCHARGE_H
#define TESTCHARGE_H

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

class TestCharge : public QGraphicsItem
{
public:
    TestCharge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    double Q;
    bool isConstructor;

    int type() const;
    enum { Type = UserType + 1, TypeConstructor = UserType + 2};

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

};

#endif // TESTCHARGE_H
