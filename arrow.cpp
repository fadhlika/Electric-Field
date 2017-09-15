#include "arrow.h"

Arrow::Arrow()
{
    direction = 0.0;
}

QRectF Arrow::boundingRect() const
{
    return QRectF(-10, -15, 20, 30);
}
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    path.moveTo(0, -10);
    path.lineTo(10, 0);
    path.lineTo(5, 0);
    path.lineTo(5, 30);
    path.lineTo(-5, 30);
    path.lineTo(-5, 0);
    path.lineTo(-10, 0);
    path.closeSubpath();

    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawPath(path);
}

int Arrow::type() const
{
    return UserType+3;
}
