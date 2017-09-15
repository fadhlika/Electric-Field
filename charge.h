#ifndef CHARGE_H
#define CHARGE_H

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

class Charge : public QGraphicsItem
{
public:
    Charge();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

    double Q;
    double x;
    double y;
    bool isConstructor;

    int type() const;
    enum { Type = UserType + 1};

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QColor color;
};

#endif // CHARGE_H
