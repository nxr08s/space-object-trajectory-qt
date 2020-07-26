#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QPalette pal = a.palette();
    pal.setColor(QPalette::Background,Qt::white);
    a.setPalette(pal);

    a.setWindowIcon(QIcon(QPixmap(":/icon.png")));

    MainWindow w;
    w.show();

    return a.exec();
}
