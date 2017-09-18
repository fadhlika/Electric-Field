#include "testcharge.h"

TestCharge::TestCharge()
{
    setCursor(Qt::OpenHandCursor);
    setAcceptedMouseButtons(Qt::LeftButton|Qt::RightButton);
    setAcceptDrops(true);
    isConstructor = false;
    this->setZValue(10);
}

QRectF TestCharge::boundingRect() const
{
    return QRectF(-10, -10, 20, 20);
}

void TestCharge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::yellow);
    painter->drawEllipse(-10, -10, 20, 20);
}

void TestCharge::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ClosedHandCursor);
}


void TestCharge::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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
        mime->setProperty("Q", this->Q);
        mime->setProperty("Test", true);

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
    }
}

void TestCharge::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "Mouse release: " << event->scenePos();
    setCursor(Qt::OpenHandCursor);
}


int TestCharge::type() const
{
    if(isConstructor) return TypeConstructor;

    return Type;
}


