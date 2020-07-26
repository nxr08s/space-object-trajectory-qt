#include "helpwindow.h"

HelpWindow::HelpWindow(QWidget *parent):QDialog(parent)
{
    this->setModal(true);
    this->setWindowTitle("Помощь");
    this->setFixedSize(300,400);
    this->setLayout(new QVBoxLayout(this));

    QGroupBox *newGP = new QGroupBox(this);
    newGP->setTitle("Общие сведения");
    newGP->setLayout(new QVBoxLayout(this));
    newGP->layout()->addWidget(new QLabel("Построение траектории движениякосмического тела в поле тяготения."));
    newGP->layout()->addWidget(new QLabel("Используются примерные приближения к реальным значениям."));

    this->layout()->addWidget(newGP);



}

HelpWindow::~HelpWindow()
{
    this->deleteLater();
}
