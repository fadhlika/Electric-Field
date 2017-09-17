#include "control.h"

Control::Control()
{
    this->setZValue(5);
}

QRectF Control::boundingRect() const
{
    return QRectF(-120, -40, 240, 80);
}

void Control::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::white, 2));
    painter->setBrush(Qt::black);
    //painter->drawRect(-100, -100, 200, 100);
    painter->drawRoundedRect(-120, -40, 240, 80, 10, 10);
}

int Control::type() const
{
    return Type;
}
