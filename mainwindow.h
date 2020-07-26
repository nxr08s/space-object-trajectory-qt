#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QIntValidator>
#include <QMessageBox>
#include <QKeyEvent>

#include <paintwidget.h>
#include <helpdialog.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

    paintWidget *pntWgt;

private slots:
    void helpPressed();
    void aboutQtPressed();
    void updateButtonPressed();

signals:
    void updatePaintWindow(double ySpeed,double xStartPos,int oberveTime, bool aa);  // новые данные постройки траектории
    void offsetChanged(int xAddition, int yAddition);   // нажата одна из клавиш w, a, s, d.

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
