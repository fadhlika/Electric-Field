#include "settingdialog.h"

SettingDialog::SettingDialog(double *dt, double *mass, double * charge, QWidget *parent): QDialog(parent)
{
   deltat = *dt;
   chargemass = *mass;
   chargevalue = *charge;

   QLabel *title = new QLabel("Test Charge Parameter");

   QLabel *dtLabel = new QLabel("dt");
   QLineEdit *dtLineEdit = new QLineEdit;
   dtLineEdit->setText(QString::number(deltat));
   connect(dtLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setDeltaT(QString)));

   QLabel *massLabel = new QLabel("Mass");
   QLineEdit *massLineEdit = new QLineEdit;
   massLineEdit->setText(QString::number(chargemass));
   connect(massLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setMass(QString)));

   QLabel *chargeLabel = new QLabel("Charge");
   QLineEdit *chargeLineEdit = new QLineEdit;
   chargeLineEdit->setText(QString::number(chargevalue));
   connect(chargeLineEdit, SIGNAL(textChanged(QString)), this, SLOT(setCharge(QString)));

   QGridLayout *paramLayout = new QGridLayout;
   paramLayout->addWidget(title, 0, 0);
   paramLayout->addWidget(dtLabel, 1, 0);
   paramLayout->addWidget(dtLineEdit, 1, 1);
   paramLayout->addWidget(massLabel, 2, 0);
   paramLayout->addWidget(massLineEdit, 2, 1);
   paramLayout->addWidget(chargeLabel, 3, 0);
   paramLayout->addWidget(chargeLineEdit, 3, 1);

   QPushButton *defaultBtn = new QPushButton;
   defaultBtn->setDefault(true);
   defaultBtn->setText("OK");
   connect(defaultBtn, &QPushButton::clicked, this, &SettingDialog::okDialog);

   QPushButton *cancelBtn = new QPushButton;
   cancelBtn->setDefault(true);
   cancelBtn->setText("Cancel");
   connect(cancelBtn, SIGNAL(released()), this, SLOT(reject()));

   QHBoxLayout *btnLayout = new QHBoxLayout;
   btnLayout->addWidget(defaultBtn);
   btnLayout->addWidget(cancelBtn);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addLayout(paramLayout);
   mainLayout->addLayout(btnLayout);

   this->setLayout(mainLayout);
}

void SettingDialog::setDeltaT(QString s)
{
    deltat = s.toDouble();
    qDebug() << deltat;
}
void SettingDialog::setMass(QString s)
{
    chargemass = s.toDouble();
    qDebug() << chargemass;
}
void SettingDialog::setCharge(QString s)
{
    chargevalue  = s.toDouble();
    qDebug() << chargevalue;
}

void SettingDialog::okDialog()
{
    emit settingAccepted(deltat, chargemass, chargevalue);
    this->close();
}
