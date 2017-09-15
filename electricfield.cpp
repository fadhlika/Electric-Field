#include "electricfield.h"

ElectricField::ElectricField(QObject *parent): QGraphicsScene(parent)
{
    GridW = 75;
}

void ElectricField::InitializeField()
{
    QDesktopWidget *widget = QApplication::desktop();
    QRect mainScreenSize = widget->availableGeometry(widget->primaryScreen());

    this->NGridX = mainScreenSize.width() / GridW;
    this->NGridY = mainScreenSize.height() / GridW;
    qDebug() << "Number of grid: " << NGridX << this->NGridY;

    for(double x=20; x < mainScreenSize.width() - GridW; x += GridW){
        for(double y=20; y < mainScreenSize.height() - GridW; y += GridW){
            Arrow *arrow = new Arrow;
            arrow->setPos(x, y);
            this->addItem(arrow);
        }
    }

    foreach (QGraphicsItem *c, this->items()) {
        if(c->type() == ArrowField) {
            c->setTransformOriginPoint(0, 0);
            c->hide();
        }
    }
}

void ElectricField::CalculateField()
{
    //qDebug() << "Clear vector";

    double Ex[NGridX][NGridY];
    double Ey[NGridX][NGridY];
    double E[NGridX][NGridY];

    for(int i=0; i < NGridX; i++){
        for(int j=0; j <= NGridY; j++){
            Ex[i][j] = 0;
            Ey[i][j] = 0;
            E[i][j] = 0;
        }
    }

    //qDebug() << "Calculate Ex and Ey";
    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            foreach (QGraphicsItem *item, this->items()) {
                if(item->type() == ChargeNormal) {
                    Charge *c = qgraphicsitem_cast<Charge*>(item);
                    if(c != 0) {
                        double Rx = i - SceneToGridX(c->scenePos());
                        double Ry = j - SceneToGridY(c->scenePos());
                        double R = std::pow(std::sqrt(Rx*Rx + Ry*Ry),3);
                        Ex[i][j] += K*c->Q*Rx/R;
                        Ey[i][j] += K*c->Q*Ry/R;
                    }
                }
            }
        }
    }

    //qDebug() << "Calculate E";
    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            E[i][j] = std::sqrt(Ex[i][j]*Ex[i][j] + Ey[i][j]*Ey[i][j]);
        }
    }


    //qDebug() << "Set E saturation";
    double Qmax = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if(item->type() == ChargeNormal) {
            Charge *c = qgraphicsitem_cast<Charge*>(item);
            if(c != 0) {
                if(Qmax < std::fabs(c->Q))
                    Qmax = std::fabs(c->Q);
            }
        }
    }

    double Esat = K * Qmax / (1.5*1.5);
    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            if(E[i][j] > Esat) E[i][j] = Esat;
            else if(E[i][j] < -Esat) E[i][j] = -Esat;
        }
    }

    //qDebug() << "Rotate arrow" ;
    for(int i=0; i < NGridX; i++){
        double x = (i*GridW);
        for(int j=0; j < NGridY; j++){
            double y = (j*GridW);
            double tetha = atan2(Ey[i][j],Ex[i][j]) * 180 / 3.14159265;
            tetha += 90;
            if(tetha < 0) tetha += 360;
            foreach (QGraphicsItem *item, this->items(QRectF(x, y, GridW, GridW))) {
                if(item->type() == ArrowField){
                    Arrow *arrow = qgraphicsitem_cast<Arrow*>(item);
                    arrow->setRotation(tetha);

                    QColor color(Qt::white);
                    double alpha = E[i][j]/Esat;

                    color.setAlphaF(alpha);
                    arrow->setColor(color);
                }
            }
        }
    }

    //qDebug() << "Calculate done";
}

double ElectricField::SceneToGridX(QPointF pos)
{
    return (pos.x()-20)/GridW;
}

double ElectricField::SceneToGridY(QPointF pos)
{
    return (pos.y()-20)/GridW;
}

void ElectricField::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    //qDebug() << "Drag enter" << event->scenePos();
}

void ElectricField::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //Q_UNUSED(event);
    QGraphicsScene::dragLeaveEvent(event);
    //qDebug() << "Drag leave" << event->scenePos();
    update();
}

void ElectricField::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    event->setAccepted(true);
    qDebug() << "Drag move";
}

void ElectricField::dropEvent(QGraphicsSceneDragDropEvent *event){
    //qDebug() << "Drop: " << event->scenePos();
    QGraphicsScene::dropEvent(event);

    double Q = qvariant_cast<double>(event->mimeData()->property("Q"));

    Charge *charge = new Charge;
    charge->Q = Q;
    charge->setPos(event->scenePos());
    charge->setZValue(10);

    this->addItem(charge);
    foreach (QGraphicsItem *c, this->items()) {
        if(c->type() == ArrowField) {
            if(!c->isVisible()) c->show();
        }
    }
    this->CalculateField();

}

void ElectricField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if(event->button() == Qt::RightButton)
    {
        Charge *charge = qgraphicsitem_cast<Charge*>(this->mouseGrabberItem());
        if(charge != 0){
            this->removeItem(charge);
            delete charge;
            this->CalculateField();
        }

        int i = 0;
        foreach (QGraphicsItem *c, this->items()) {
            if(c->type() == ChargeNormal) i++;
        }

        if(i == 0) {
            foreach (QGraphicsItem *c, this->items()) {
                if(c->type() == ArrowField) {
                    c->hide();
                }
            }
        }
    } else {

    }
    //qDebug() << "Mouse press scene" << event->scenePos();
}

void ElectricField::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    //qDebug() << "Grid: " << SceneToGridX(event->scenePos())
    //         << SceneToGridY(event->scenePos()) << event->scenePos();

    Charge *charge = qgraphicsitem_cast<Charge*>(this->mouseGrabberItem());
    if(charge != 0){
        //qDebug() << "Item post from scene" << charge->Q;
        this->CalculateField();
    }
}

void ElectricField::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

}
