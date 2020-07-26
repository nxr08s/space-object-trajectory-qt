#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) : QDialog(parent), ui(new Ui::helpDialog){
    ui->setupUi(this);

    this->setModal(true);
    this->setFixedSize(510,320);
}

helpDialog::~helpDialog(){
    delete ui;
}
