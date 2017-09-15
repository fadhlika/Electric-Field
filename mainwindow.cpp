#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(800, 600);
    this->setWindowTitle("Medan Listrik");

    scene = new ElectricField;
    scene->setBackgroundBrush(QBrush(Qt::black));

    control = new Control;
    control->setZValue(5);
    scene->addItem(control);

    charge1 = new Charge;
    charge1->isConstructor = true;
    charge1->Q = 1e-6;
    charge1->setZValue(10);
    scene->addItem(charge1);

    charge2 = new Charge;
    charge2->isConstructor = true;
    charge2->Q = -1e-6;
    charge2->setZValue(10);
    scene->addItem(charge2);

    view = new ElectricFieldView(scene);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setRenderHints(QPainter::Antialiasing);
    view->setGeometry(this->rect());
    scene->setSceneRect(view->rect());

    this->setCentralWidget(view);
    scene->InitializeField();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   Q_UNUSED(event);
   qDebug()  << "Resize window";
   view->setGeometry(this->rect());
   scene->setSceneRect(view->rect());

   double w = (this->width()/2);
   double h = this->height();

   charge1->setPos(w - 50, h - 60);
   charge2->setPos(w + 50, h - 60);
   control->setPos(w, h);

   qDebug() << "Control pos" << control->boundingRect();
   qDebug() << "Scene size: " << scene->width() << scene->height();
   qDebug() << "View size: " << view->width() << view->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}
