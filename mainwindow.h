#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

#include "charge.h"
#include "electricfield.h"
#include "electricfieldview.h"
#include "arrow.h"
#include "control.h"

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

private:
    Ui::MainWindow *ui;
    ElectricField *scene;
    ElectricFieldView *view;
    Control *control;
    Charge *charge1;
    Charge *charge2;
};

#endif // MAINWINDOW_H
