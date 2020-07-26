#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::helpPressed(){
    helpDialog *hlpWnd = new helpDialog(this);  // создание окна из класса, который мы определили
    hlpWnd->show(); // отображение этого окна
}

void MainWindow::aboutQtPressed(){
    QMessageBox::aboutQt(this,"Информация о Qt");   // вывод стандартного окошка "О Qt"
}

void MainWindow::updateButtonPressed(){
    double tempValue;

    // чтения начальной скорости и проверка
    tempValue = ui->oySpeedEdit->text().toDouble();
    if (tempValue <= 0 || tempValue > 1000){
        QMessageBox::critical(this,"Неверный ввод","Неверно введена начальная скорость",QMessageBox::Ok);
        return;
    }

    // чтение начальной позиции и проверка
    tempValue = ui->oxStartPosEdit->text().toDouble();
    if (tempValue < 7 || tempValue > 10000){
        QMessageBox::critical(this,"Неверный ввод","Неверно введено начальное расстояние",QMessageBox::Ok);
        return;
    }

    // если все проверки прошли успешно, о сообщаем окну отрисовки новые значения
    emit updatePaintWindow(ui->oySpeedEdit->text().toDouble() / 7.84,   // скорость с масштабированием
                           ui->oxStartPosEdit->text().toDouble() / 100, // расстояние с масштабированием(кривым)
                           ui->obsTimeEdit->text().toInt(),    // время обзора(насколько далеко рисовать траекторию)
                           ui->antialiasingCB->isChecked());    // сглаживание
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    // создание окна отрисовки и добавление его на это окно в слой (слои для растяжения окна при масшиабировании)
    pntWgt = new paintWidget(this);
    ui->paintWidgetLayout->insertWidget(0,pntWgt);

    // установка 2-ух полей ввода неактивными и валидатора ввода для времени обзора
    ui->oxSpeedEdit->setEnabled(false);
    ui->obsTimeEdit->setValidator(new QIntValidator(1,10000,this));
    ui->oyStartPosEdit->setEnabled(false);


    // создание панели меню
    QAction *tempAction;

    // пункт меню "Помощь"
    tempAction = ui->menuBar->addAction("Помощь");
    connect(tempAction,SIGNAL(triggered(bool)),this,SLOT(helpPressed()));   // соединение клавиши с ее обработчиком нажатия

    // пункт меню "Qt"
    tempAction = ui->menuBar->addAction("Qt");
    connect(tempAction,SIGNAL(triggered(bool)),this,SLOT(aboutQtPressed()));    // соединение с обработчиком нажатия

    connect(ui->updateButton,SIGNAL(clicked(bool)),this,SLOT(updateButtonPressed()));
    connect(this,SIGNAL(updatePaintWindow(double,double,int,bool)),pntWgt,SLOT(newDataRecived(double,double,int,bool)));

    // соединение клавиш изменения масштаба с слотами обработки окна отрисовки
    connect(ui->scaleDown,SIGNAL(clicked(bool)),pntWgt,SLOT(scaleDownPressed()));
    connect(ui->scaleUp,SIGNAL(clicked(bool)),pntWgt,SLOT(scaleUpPressed()));
    connect(ui->scaleReset,SIGNAL(clicked(bool)),pntWgt,SLOT(scaleResetPressed()));
    connect(this,SIGNAL(offsetChanged(int,int)),pntWgt,SLOT(offsetChanged(int,int)));
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_W:
        emit offsetChanged(0,-50);
        break;
    case Qt::Key_S:
        emit offsetChanged(0,50);
        break;
    case Qt::Key_A:
        emit offsetChanged(-50,0);
        break;
    case Qt::Key_D:
        emit offsetChanged(50,0);
        break;
    case Qt::Key_Equal:
        emit pntWgt->scaleUpPressed();
        break;
    case Qt::Key_Minus:
        emit pntWgt->scaleDownPressed();
        break;
    case Qt::Key_Escape:
        emit pntWgt->scaleResetPressed();
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
    this->update();
}

MainWindow::~MainWindow(){
    delete ui;
}
