#include "control.h"

Control::Control()
{

}

QRectF Control::boundingRect() const
{
    return QRectF(-100, -100, 200, 100);
}

void Control::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(Qt::white, 3));
    painter->setBrush(Qt::black);
    painter->drawRect(-100, -100, 200, 100);

    QFont font;
    font.setPointSize(18);
    painter->setFont(font);
    painter->drawText(-50, -15, "1uC");
    painter->drawText(0, -15, "-1uC");
}
