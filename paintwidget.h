#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QList>

class paintWidget : public QWidget{
    Q_OBJECT

public:
    explicit paintWidget(QWidget *parent = nullptr);

    bool antialiasing;

    double scale;
    int xOffset;
    int yOffset;

    QList<QPointF> points;

    double calculateSpeed(double spd,double pos1,double pos2,double dt);


public slots:
    void scaleUpPressed();
    void scaleDownPressed();
    void scaleResetPressed();
    void newDataRecived(double ySpeed,double xStartPos,int observeTime, bool aa);
    void offsetChanged(int xAddition, int yAddition);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PAINTWIDGET_H
