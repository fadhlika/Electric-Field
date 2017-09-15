#include "charge.h"

Charge::Charge()
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    setAcceptDrops(true);
    isConstructor = false;

}

QRectF Charge::boundingRect() const
{
    return QRectF(-17, -17, 34, 34);
}

void Charge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(Q > 0) color = Qt::red;
    else color = Qt::blue;

    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-15, -15, 30, 30);

    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::white, 3));

    if(Q>0)
    {
        painter->drawLine(0, -10, 0, 10);
    }

    painter->drawLine(-10, 0, 10, 0);
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

        QPixmap pixmap(34, 34);
        pixmap.fill(Qt::transparent);

        QPainter painter(&pixmap);
        painter.translate(17, 17);
        painter.setRenderHint(QPainter::Antialiasing);
        paint(&painter, 0, 0);
        painter.end();

        drag->setPixmap(pixmap);
        drag->setHotSpot(QPoint(17, 17));

        drag->exec();
        setCursor(Qt::OpenHandCursor);
    } else {
        this->setPos(event->scenePos());
    }
}

void Charge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Mouse release: " << event->scenePos();
    setCursor(Qt::OpenHandCursor);
}

int Charge::type() const
{
    if(isConstructor)
        return UserType + 2;

    return Type;
}
