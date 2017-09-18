#include "dipolecharge.h"

DipoleCharge::DipoleCharge()
{

}

QRectF DipoleCharge::boundingRect() const
{
    return QRectF(-10, -30, 20, 60);
}

void DipoleCharge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(Qt::gray);
    painter->setPen(QPen(Qt::gray, 3));
    painter->drawLine(0, -20, 0, 20);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    painter->drawEllipse(-10, -30, 20, 20);

    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::white, 3));

    painter->drawLine(0, -25, 0, -15);
    painter->drawLine(-5, -20, 5, -20);


    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::blue);
    painter->drawEllipse(-10, 10, 20, 20);

    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::white, 3));
    painter->drawLine(-5, 20, 5, 20);
}
