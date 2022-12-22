#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <cmath>

QImage image(500, 500, QImage::Format_RGB888);
uint black = qRgb(0, 0, 0);
uint blue = qRgb(0, 0, 55);
uint green = qRgb(0, 255, 0);
uint red = qRgb(255, 0, 0);

QVector<float> polygon_x = {5, 30, 30, 5, 5};
QVector<float> polygon_y = {5, 5, 30, 30, 5};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    image.fill(Qt::white);
    ui->displayArea->setPixmap(QPixmap::fromImage(image));

    //draw central vertical and horizontal lines
    dda(250, 0, 250, 500, blue);
    dda(0, 250, 500, 250, blue);

    int size = polygon_x.size();
    for(int i=0; i<size-1; i++){
        dda(polygon_x[i], polygon_y[i], polygon_x[i+1], polygon_y[i+1], green);
    }

//    transform(5, 30);
//    scale(5, 5);
    rotation(30);

}

void MainWindow::rotation(int angle){
    int size = polygon_x.size();

    for(int i=0; i<size-1; i++){

        float p1_x = polygon_x[i]*cos(angle) - polygon_y[i]*sin(angle);
        float p1_y = polygon_x[i]*sin(angle) - polygon_y[i]*cos(angle);
        float p2_x = polygon_x[i+1]*cos(angle) - polygon_y[i+1]*sin(angle);
        float p2_y = polygon_x[i+1]*sin(angle) - polygon_y[i+1]*cos(angle);

        qDebug() << p1_x << " " << p1_y << " " << p2_x << p2_y;

        dda(p1_x, p1_y, p2_x, p2_y, red);
    }
}

void MainWindow::transform(float x1, float y1){
    float x = 0;
    float y = 0;

    if(250 > x1){
        x = 250 - x1;
    }else{
        x = x1 - 250;
    }
    if(250 > y1){
        y = 250 - y1;
    }else{
        y = y1 - 250;
    }

    qDebug() << x;

    int size = polygon_x.size();
    for(int i=0; i<size-1; i++){
        dda(polygon_x[i]+x, polygon_y[i]+y, polygon_x[i+1]+x, polygon_y[i+1]+y, red);
    }
}

void MainWindow::scale(float x, float y){

    int size = polygon_x.size();
    for(int i=0; i<size-1; i++){
        dda(polygon_x[i]*x, polygon_y[i]*y, polygon_x[i+1]*x, polygon_y[i+1]*y, red);
    }
}


void MainWindow::plot(float x, float y, uint color){
    image.setPixel(x, y, color);
}

void MainWindow::dda(float x1, float y1, float x2, float y2, uint color){
     float dx = x2 - x1;
     float dy = y2 - y1;

     float steps = std::max(abs(dy), abs(dx));

     dx = dx/steps;
     dy = dy/steps;

     for(int i=0; i<steps; i++){
          plot(x1, y1, color);
          x1 += dx;
          y1 += dy;
     }

     ui->displayArea->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

