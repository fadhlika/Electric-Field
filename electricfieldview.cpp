#include "electricfieldview.h"

ElectricFieldView::ElectricFieldView(QGraphicsScene *scene, QWidget *parent): QGraphicsView(scene, parent)
{
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
}

void ElectricFieldView::resizeEvent(QResizeEvent *event)
{
    qDebug() <<"Resize event";
    this->fitInView(0, 0, this->width(), this->height(), Qt::KeepAspectRatio);
    QGraphicsView::resizeEvent(event);
}
