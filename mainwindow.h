#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>

#include "charge.h"
#include "electricfield.h"
#include "electricfieldview.h"
#include "arrow.h"
#include "control.h"
#include "testcharge.h"
#include "settingdialog.h"
#include "dipolecharge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void resizeEvent(QResizeEvent *event);
    void StartTest();
    void StopTest();
    void Reset();

    void ShowSettingDialog();
    void setSetting(double dt, double mass, double charge);

private:
    Ui::MainWindow *ui;

    ElectricField *scene;
    ElectricFieldView *view;

    Control *control;

    Charge *charge1;
    Charge *charge2;
    TestCharge *testCharge;

    QGraphicsTextItem *pChargeText;
    QGraphicsTextItem *nChargeText;
    QGraphicsTextItem *tChargeText;

    SettingDialog *dialog;
};

#endif // MAINWINDOW_H
