#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include<QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QObject>

#include "electricfield.h"

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    SettingDialog(double *dt, double *mass,
                  double * charge, QWidget *parent = 0);

    void okDialog();

signals:
    void settingAccepted(double dt, double mass, double charge);

public slots:
    void setDeltaT(QString);
    void setMass(QString);
    void setCharge(QString);

private:
    QLineEdit *dtLineEdit;
    QLineEdit *massLineEdit;
    QLineEdit *chargeLineEdit;

    double deltat;
    double chargemass;
    double chargevalue;
};

#endif // SETTINGDIALOG_H
