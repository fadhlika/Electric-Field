#include "charge.h"

Charge::Charge()
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    setAcceptDrops(true);
    isConstructor = false;
    this->setZValue(10);
}

QRectF Charge::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void Charge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(Q > 0) color = Qt::red;
    else color = Qt::blue;

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-10, -10, 20, 20);

    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::white, 3));

    if(Q>0)
    {
        painter->drawLine(0, -5, 0, 5);
    }

    painter->drawLine(-5, 0, 5, 0);
}

void Charge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}

void Charge::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Mouse move charge: " << event->scenePos();
    if(QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
            .length() < QApplication::startDragDistance())
    {
        return;
    }

    if(this->isConstructor){
        QDrag *drag = new QDrag(event->widget());
        QMimeData *mime = new QMimeData;

        drag->setMimeData(mime);

        mime->setColorData(color);
        mime->setProperty("Q", this->Q);

        QPixmap pixmap(20, 20);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.translate(10, 10);
        painter.setRenderHint(QPainter::Antialiasing);
        paint(&painter, 0, 0);
        painter.end();

        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(10, 10));

        drag->exec();
        setCursor(Qt::OpenHandCursor);
    } else {
        this->setPos(event->scenePos());
    }
}

void Charge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "Mouse release: " << event->scenePos();
    setCursor(Qt::OpenHandCursor);
}

int Charge::type() const
{
    if(isConstructor)
        return TypeConstructor;

    return Type;
}
