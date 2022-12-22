#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QVector>

QImage img(500, 500, QImage::Format_RGB888);

QVector<int> box_x{100, 100, 300, 300, 100};
QVector<int> box_y{100, 300, 300, 100, 100};

float x_min=1000, x_max=0, y_min=1000, y_max=0;

class Line{
public:
    float x1, y1, x2, y2;



    Line(float _x1, float _y1, float _x2, float _y2){
        x1 = _x1;
        y1 = _y1;
        x2 = _x2;
        y2 = _y2;
    }
};

Line l1(50, 250, 150, 150);

void MainWindow::calculate_minmax(){
    int n = box_x.size();
    for(int i=0; i < n; i++){
        x_min = std::min(x_min,(float)box_x[i]);
        y_min = std::min(y_min,(float)box_y[i]);

        x_max = std::max(x_max,(float)box_x[i]);
        y_max = std::max(y_max,(float)box_y[i]);

    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    img.fill(Qt::white);
    ui->displayArea->setPixmap(QPixmap::fromImage(img));

    drawBox();
    //dda(l1.x1, l1.y1, l1.x2, l1.y2);
    calculate_minmax();
    clip(l1.x1, l1.y1, l1.x2, l1.y2);

    qDebug() << x_min << " " << x_max;
    qDebug() << y_min << " " << y_max;
}

void MainWindow::plot(float x, float y){
    img.setPixel(x, y, qRgb(0, 0, 255));
}

void MainWindow::dda(float x1, float y1, float x2, float y2){


    float dx = (float) x2 - x1;
    float dy = (float) y2 - y1;

    float steps = std::max(abs(dx), abs(dy));

    dx =  dx/steps;
    dy = dy/steps;

    qDebug() << dx << "dx";


    for(int i=0; i<steps; i++){

       //qDebug() << x1 << " " << x2 << "dx";


       plot(x1, y1);
       x1 = x1 + dx;
       y1 += dy;
    }
    ui->displayArea->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::drawBox(){
    int n = box_x.size();
    for(int i=0; i<n-1; i++){
        dda(box_x[i], box_y[i], box_x[i+1], box_y[i+1]);
    }


}

void MainWindow::clip(int x1, int y1, int x2, int y2){
    //1-left, 2- top, 3-right, 4-bottom
    int side = 0;
    //Identify the size of line
    if(x1 < x_min && y1 < y_max && y1 > y_min ){

        // we have x size as x_min need ysize
        int x = x_min;
        float m = (y2 - y1)/(x2-x1);
        int y = m * (x-x1) + y1;

        qDebug() << x2 << " " << x1;

        qDebug() << y2 << " " << y;
        qDebug() << m << "slope " << y << " y";



        dda(x, y, x2, y2);
    }else{
        qDebug() << "other size";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

