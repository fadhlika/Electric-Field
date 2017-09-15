#ifndef ARROW_H
#define ARROW_H

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
#include <QPainterPath>
#include <QtMath>
#include <vector>
#include <QColor>

class Arrow : public QGraphicsItem
{
public:
    Arrow();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
    void setColor(QColor color_);

    int type() const;

private:
    QColor color;
};

#endif // ARROW_H
