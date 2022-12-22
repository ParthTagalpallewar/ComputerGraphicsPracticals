#include "mainwindow.h"
#include "./ui_mainwindow.h"

QImage img(500, 500, QImage::Format_RGB888);



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    img.fill(Qt::white);
    ui->drawingArea->setPixmap(QPixmap::fromImage(img));

    drawMidPointCircle();

}

void MainWindow::eightWaySymmentry(int x, int y){
    addPixel(x, y);
    addPixel(x, -y);
    addPixel(-x, -y);
    addPixel(-x, y);

    addPixel(y,x);
    addPixel(-y, x);
    addPixel(-y, -x);
    addPixel(y, -x);
}

void MainWindow::addPixel(int x, int y){
    img.setPixel(x+200, y+200, qRgb(0, 0, 0));
}

void MainWindow::drawMidPointCircle(){
    int r = 100;
    int x = 0, y = r;

    eightWaySymmentry(x, y);


    int p = 1 - r;

    while(x <= y){

        if(p < r){
            x += 1;
            p = p +(2*x) + 5;
        }else{
            x += 1;
            y -= 1;
            p = p + (2*x) - (2*y) + 5;
        }

        eightWaySymmentry(x, y);

    }

    ui->drawingArea->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

