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
    scene->addItem(control);

    charge1 = new Charge;
    charge1->isConstructor = true;
    charge1->Q = 1e-6;
    scene->addItem(charge1);

    charge2 = new Charge;
    charge2->isConstructor = true;
    charge2->Q = -1e-6;
    scene->addItem(charge2);

    testCharge = new TestCharge;
    testCharge->isConstructor = true;
    testCharge->Q = 1e-6;
    scene->addItem(testCharge);

    pChargeText = new QGraphicsTextItem("+1uC");
    pChargeText->setZValue(10);
    pChargeText->setDefaultTextColor(Qt::white);
    pChargeText->setFont(QFont("Arial", 13));
    scene->addItem(pChargeText);

    nChargeText = new QGraphicsTextItem("-1uC");
    nChargeText->setZValue(10);
    nChargeText->setDefaultTextColor(Qt::white);
    nChargeText->setFont(QFont("Arial", 13));
    scene->addItem(nChargeText);

    tChargeText = new QGraphicsTextItem("Test");
    tChargeText->setZValue(10);
    tChargeText->setDefaultTextColor(Qt::white);
    tChargeText->setFont(QFont("Arial", 13));
    scene->addItem(tChargeText);

    view = new ElectricFieldView(scene);
    view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setRenderHints(QPainter::Antialiasing);
    view->setGeometry(this->rect());
    scene->setSceneRect(view->rect());

    double dt = scene->interval(), mass = scene->chargeMass(), charge = testCharge->Q;

    dialog = new SettingDialog(&dt, &mass, &charge, this);
    connect(dialog, &SettingDialog::settingAccepted, this, &MainWindow::setSetting);

    QMenu *fileMenu = new QMenu;
    fileMenu->setTitle("File");

    QMenu *playbackMenu = new QMenu;
    playbackMenu->setTitle("Playback");

    QAction *playAction = new QAction;
    playAction->setText("Play");
    playAction->setIcon(QIcon(":/play.svg"));
    connect(playAction, &QAction::triggered, this, &MainWindow::StartTest);

    QAction *stopAction = new QAction;
    stopAction->setText("Stop");
    stopAction->setIcon(QIcon(":/stop.svg"));
    connect(stopAction, &QAction::triggered, this, &MainWindow::StopTest);

    QAction *resetAction = new QAction;
    resetAction->setText("Stop");
    resetAction->setIcon(QIcon(":/replay.svg"));
    connect(resetAction, &QAction::triggered, this, &MainWindow::Reset);

    QAction *settingAction = new QAction;
    settingAction->setText("Setting");
    settingAction->setIcon(QIcon(":/settings.svg"));
    connect(settingAction, &QAction::triggered, dialog, &SettingDialog::exec);

    ui->menuBar->addMenu(fileMenu);

    ui->toolBar->addAction(resetAction);
    ui->toolBar->addAction(playAction);
    ui->toolBar->addAction(stopAction);
    ui->toolBar->addAction(settingAction);

    this->setCentralWidget(view);
    scene->InitializeField();
}

void MainWindow::setSetting(double dt, double mass, double charge)
{
    this->scene->setParameters(dt, mass, charge);

    qDebug() << "Setting set";
}

void MainWindow::StartTest()
{
    scene->StartTest();
}

void MainWindow::StopTest()
{
    scene->StopTest();
}

void MainWindow::Reset()
{
    scene->Reset();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
   Q_UNUSED(event);
   qDebug()  << "Resize window";
   view->setGeometry(this->centralWidget()->rect());
   scene->setSceneRect(view->rect());

   double w = (this->width()/2);
   double h = this->height();

   charge1->setPos(w - 60, h - 110);
   charge2->setPos(w, h - 110);
   testCharge->setPos(w + 60, h - 110);
   control->setPos(w, h - 100);

   pChargeText->setPos(w - 85, h - 90);
   nChargeText->setPos(w - 25, h - 90);
   tChargeText->setPos(w + 40, h - 90);

   qDebug() << "Control pos" << control->boundingRect();
   qDebug() << "Scene size: " << scene->width() << scene->height();
   qDebug() << "View size: " << view->width() << view->height();
}

MainWindow::~MainWindow()
{
    delete ui;
}
