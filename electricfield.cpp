#include "electricfield.h"

ElectricField::ElectricField(QObject *parent): QGraphicsScene(parent)
{
    GridW = 60;

    testCharge = Q_NULLPTR;

    Vx = 0;
    Vy = 0;
    dt = 0.0167;

    chargeTestMass = 1e-5;

    timer = new QTimer;
    timer->setInterval(16);
    connect(timer, &QTimer::timeout, this, &ElectricField::CalculateForce);
}

void ElectricField::setParameters(double deltat, double mass, double charge)
{
    dt = deltat;
    chargeTestMass = mass;

    QPointF pos;
    foreach (QGraphicsItem *item, this->items()) {
        if(item->type() == TestCharge::TypeConstructor){
            pos = item->scenePos();
            this->removeItem(item);
            delete item;
        }
    }

    TestCharge *t = new TestCharge;
    t->isConstructor = true;
    t->setZValue(15);
    t->Q = charge;
    t->setPos(pos);
    this->addItem(t);
}

double ElectricField::interval()
{
    return dt;
}

double ElectricField::chargeMass()
{
    return chargeTestMass;
}

void ElectricField::StartTest()
{
    timer->start();
}

void ElectricField::StopTest()
{
    timer->stop();
    Vx = 0;
    Vy = 0;
}

void ElectricField::Reset()
{
    foreach (QGraphicsItem *item, this->items()) {
        if(item->type() == Charge::Type){
            this->removeItem(item);
            delete item;
        } else if(item->type() == TestCharge::Type){
            this->removeItem(item);
            testCharge = Q_NULLPTR;
        } else if(item->type() == Arrow::Type){
            item->setRotation(0);
            item->hide();
        }
    }
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
        if(c->type() == Arrow::Type) {
            c->setTransformOriginPoint(0, 0);
            c->hide();
        }
    }
}

void ElectricField::CalculateField()
{
    //qDebug() << "Clear vector";

    double *Ex = new double[NGridX*NGridY];
    double *Ey = new double[NGridX*NGridY];
    double *E = new double[NGridX*NGridY];

    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            //qDebug() << i << j;
            Ex[i*NGridY+j] = 0;
            Ey[i*NGridY+j] = 0;
            E[i*NGridY+j] = 0;
        }
    }

    //qDebug() << "Calculate Ex and Ey";
    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            foreach (QGraphicsItem *item, this->items()) {
                if(item->type() == Charge::Type) {
                    Charge *c = qgraphicsitem_cast<Charge*>(item);
                    if(c != 0) {
                        double Rx = i - SceneToGridX(c->scenePos());
                        double Ry = j - SceneToGridY(c->scenePos());
                        double R = std::pow(std::sqrt(Rx*Rx + Ry*Ry),3);
                        Ex[i*NGridY+j] += K*c->Q*Rx/R;
                        Ey[i*NGridY+j] += K*c->Q*Ry/R;
                    }
                }
            }
        }
    }

    //qDebug() << "Calculate E";
    for(int i=0; i < NGridX; i++){
        for(int j=0; j < NGridY; j++){
            E[i*NGridY+j] = std::sqrt(Ex[i*NGridY+j]*Ex[i*NGridY+j] + Ey[i*NGridY+j]*Ey[i*NGridY+j]);
        }
    }

    //qDebug() << "Set E saturation";
    double Qmax = 0;
    foreach (QGraphicsItem *item, this->items()) {
        if(item->type() == Charge::Type) {
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
            if(E[i*NGridY+j] > Esat) E[i*NGridY+j] = Esat;
            else if(E[i*NGridY+j] < -Esat) E[i*NGridY+j] = -Esat;
        }
    }

    //qDebug() << "Rotate arrow" ;
    for(int i=0; i < NGridX; i++){
        double x = (i*GridW);
        for(int j=0; j < NGridY; j++){
            double y = (j*GridW);
            double tetha = atan2(Ey[i*NGridY+j],Ex[i*NGridY+j]) * 180 / 3.14159265;
            tetha += 90;
            if(tetha < 0) tetha += 360;
            foreach (QGraphicsItem *item, this->items(QRectF(x, y, GridW, GridW))) {
                if(item->type() == Arrow::Type){
                    Arrow *arrow = qgraphicsitem_cast<Arrow*>(item);
                    arrow->setRotation(tetha);

                    QColor color(Qt::white);
                    double alpha = E[i*NGridY+j]/Esat;

                    color.setAlphaF(alpha);
                    arrow->setColor(color);
                }
            }
        }
    }

    //qDebug() << "Calculate done";
    delete[] Ex;
    delete[] Ey;
    delete[] E;
}

void ElectricField::CalculateForce()
{
    //double *Fx = new double[NGridX*NGridY];
    //double *Fy = new double[NGridX*NGridY];
    qDebug() << "Calculate force";
    if(testCharge == Q_NULLPTR) return;

    double Fx = 0, Fy = 0;
    foreach(QGraphicsItem *c, this->items()){
        if(c->type() == Charge::Type){
            Charge *charge = qgraphicsitem_cast<Charge*>(c);

            if(charge != 0) {
                double Rx = SceneToGridX(testCharge->scenePos()) - SceneToGridX(charge->scenePos());
                double Ry = SceneToGridY(testCharge->scenePos()) - SceneToGridY(charge->scenePos());
                qDebug() << Rx << Ry;
                if(std::fabs(Rx) < 1.5) {
                    if(Rx < 0) Rx = -1.5;
                    else if(Rx > 0) Rx = 1.5;
                }
                if(std::fabs(Ry) < 1.5) {
                    if(Ry < 0) Ry = -1.5;
                    else if(Ry > 0) Ry = 1.5;
                }
                //qDebug() << Rx << Ry;
                double R = std::pow((Rx*Rx + Ry*Ry), 3);

                Fx += (K * testCharge->Q * charge->Q * Rx) / R;
                Fy += (K * testCharge->Q * charge->Q * Ry) / R;
            }
        }
    }

    double ax = Fx / chargeTestMass; //(testCharge->Q > 0 ? mp : me);
    double ay = Fy / chargeTestMass; //(testCharge->Q > 0 ? mp : me);
    Vx += ax*dt;
    Vy += ay*dt;
    double xi = SceneToGridX(testCharge->scenePos()) + Vx*dt;
    double yi = SceneToGridY(testCharge->scenePos()) + Vy*dt;

    qDebug() << xi  << yi << GridToSceneX(QPointF(xi, yi)) << GridToSceneY(QPointF(xi, yi));

    QPointF pos(GridToSceneX(QPointF(xi, yi)), GridToSceneY(QPointF(xi, yi)));
    testCharge->setPos(pos);
    //this->CalculateField();
}

double ElectricField::SceneToGridX(QPointF pos)
{
    return (pos.x()-20)/GridW;
}

double ElectricField::SceneToGridY(QPointF pos)
{
    return (pos.y()-20)/GridW;
}

double ElectricField::GridToSceneX(QPointF pos)
{
    return (pos.x()*GridW)+20;
}

double ElectricField::GridToSceneY(QPointF pos)
{
    return (pos.y()*GridW)+20;
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
    //qDebug() << "Drag move";
}

void ElectricField::dropEvent(QGraphicsSceneDragDropEvent *event){
    //qDebug() << "Drop: " << event->scenePos();

    QGraphicsScene::dropEvent(event);

    double Q = qvariant_cast<double>(event->mimeData()->property("Q"));
    bool test = qvariant_cast<bool>(event->mimeData()->property("Test"));

    if(!test){
        Charge *charge = new Charge;
        charge->Q = Q;
        charge->setPos(event->scenePos());

        this->addItem(charge);
        qDebug() << "New charge";

        foreach (QGraphicsItem *c, this->items()) {
            if(c->type() == Arrow::Type) {
                if(!c->isVisible()) c->show();
            }
        }
        this->CalculateField();
    } else {
        if(testCharge != Q_NULLPTR) return;

        TestCharge *charge = new TestCharge;
        charge->Q = Q;
        charge->setPos(event->scenePos());

        this->addItem(charge);
        qDebug() << "New test charge";

        foreach(QGraphicsItem *c, this->items()){
            if(c->type() == TestCharge::Type){
                testCharge = qgraphicsitem_cast<TestCharge*>(c);
                x = SceneToGridX(testCharge->scenePos());
                y = SceneToGridY(testCharge->scenePos());
            }
        }
    }
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

        TestCharge *tCharge = qgraphicsitem_cast<TestCharge*>(this->mouseGrabberItem());
        if(testCharge != 0){
            this->removeItem(tCharge);
            delete tCharge;
            testCharge = Q_NULLPTR;
            Vx = 0;
            Vy = 0;
            this->CalculateField();
        }

        int i = 0;
        foreach (QGraphicsItem *c, this->items()) {
            if((c->type() == Charge::Type) || (c->type() == TestCharge::Type)) i++;
        }

        if(i == 0) {
            foreach (QGraphicsItem *c, this->items()) {
                if(c->type() == Arrow::Type) {
                    c->hide();
                }
            }
        }
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
