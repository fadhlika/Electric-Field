#include "arrow.h"

Arrow::Arrow()
{
    color = Qt::white;
}

QRectF Arrow::boundingRect() const
{
    return QRectF(-7.5, -20, 15, 40);
}
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPainterPath path;
    path.moveTo(0, -20);
    path.lineTo(7.5, -5);
    path.lineTo(3, -5);
    path.lineTo(3, 20);
    path.lineTo(-3, 20);
    path.lineTo(-3, -5);
    path.lineTo(-7.5, -5);
    path.closeSubpath();

    painter->setPen(color);
    painter->setBrush(color);
    painter->drawPath(path);
}

void Arrow::setColor(QColor color_)
{
    color = color_;
    this->update();
}

int Arrow::type() const
{
    return Type;
}
