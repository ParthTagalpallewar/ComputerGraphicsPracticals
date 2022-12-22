#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


QImage img(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    img.fill(Qt::white);
    ui->drawingArea->setPixmap(QPixmap::fromImage(img));

    BresenhumLine();
}

void MainWindow::plot(int x, int y){
    img.setPixel(x, y, qRgb(0, 0, 0));
    qDebug() << "plot " << x << "    " << y;
}

void MainWindow::BresenhumLine(){
    int x1 = 150;
    int y1 = 150;
    int x2 = 250;
    int y2 = 250;

    int delta_x = x2 - x1;
    int delta_y = y2 - y1;

    float slope = delta_y / delta_x;
    int P = 2 * delta_y - delta_x;

    plot(x1, y1);

    //if slope is less than 1 then use
    //Iterate find y according to x that means
    //Accoring to decision parameter value of y will be y+1 or y
    for(int i=0; i<delta_x; i++){
        qDebug() << i << "dx itertor";

        if(slope < 1){

            if(P < 0){
                x1 += 1;
                P = P + 2 * delta_y;
            }
            else{
                x1 += 1;
                y1 += 1;
                P = P + (2 * delta_y) - (2*delta_x);
            }
            plot(x1, y1);

        }else{

            if(P < 0){
                y1 += 1;
                P = P + 2 * delta_x;
            }else{
                x1 += 1;
                y1 += 1;
                P = P + (2*delta_x) - (2*delta_y);
            }
            plot(x1, y1);

        }
    }
    ui->drawingArea->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

