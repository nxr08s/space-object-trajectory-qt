#include "paintwidget.h"

paintWidget::paintWidget(QWidget *parent) : QWidget(parent){
    antialiasing = true;
    this->scaleResetPressed();  // сброс масштаба и смещения
}

double paintWidget::calculateSpeed(double spd, double pos1, double pos2, double dt){
    double temp = sqrt(pos1 * pos1 + pos2 * pos2);
    return (spd - (pos1 / (temp * temp * temp) * dt));
}

void paintWidget::scaleUpPressed(){
    scale *= 2;
}

void paintWidget::scaleDownPressed(){
    scale /= 2;
}

void paintWidget::scaleResetPressed(){
    scale = 50;
    xOffset = this->rect().center().x();
    yOffset = this->rect().center().y();
}

// Прием новых данных и перерасчет массива с точками.
void paintWidget::newDataRecived(double ySpd, double xStartPos,int observeTime,bool aa){
    antialiasing = aa;

    points.clear();

    // начальная скорость
    double ySpeed = ySpd;
    double xSpeed = 0;

    // начальная позиция
    double xPos = xStartPos;
    double yPos = 0;

    points.push_back(QPointF(xPos,yPos));
    for (double dt = 0; dt < float(observeTime) / 1000; dt += 0.00001){  // расчет точек с шагом 0.00001
        xSpeed = calculateSpeed(xSpeed,xPos,yPos,dt);   // вычисление новой скорости
        ySpeed = calculateSpeed(ySpeed,yPos,xPos,dt);

        xPos += xSpeed * dt;    // вычисление новой позиции
        yPos += ySpeed * dt;

        if (fabs(yPos) < 0.063 && fabs(xPos) < 0.063)   // проверка на столкновение с планетой (не всегда срабатывает,
            break;                                      // так как иногда не попадает в центр и улетает далеко-далеко.

        points.push_back(QPointF(xPos,yPos));   // добавление новой точки
    }
}

void paintWidget::offsetChanged(int xAddition, int yAddition){
    xOffset += xAddition;
    yOffset += yAddition;
}

void paintWidget::paintEvent(QPaintEvent *event){

   QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,antialiasing);

    painter.drawEllipse(xOffset,yOffset,0.062 * scale,0.062 * scale);   // отрисовка "планеты"

    // отрисовка траектории с учетом масштаба и смещений
    for (int i = 0; i < points.size() - 1; i++)
        painter.drawLine(points[i].x() * scale + xOffset, points[i].y() * scale + yOffset,
                         points[i + 1].x() * scale + xOffset, points[i + 1].y() * scale + yOffset);

    this->update();
}
