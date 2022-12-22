#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QDebug"


QImage img(500, 500, QImage::Format_RGB888);
int xc, yc;
int r;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(Qt::white);

    ui->drawingArea->setPixmap(QPixmap::fromImage(img));
    xc = 200;
    yc = 200;
    r = 10;

    BresenhumCircle();
}

void MainWindow::EightWaySymmetry(int x, int y){



    drawPixel(x, y);
    drawPixel(x, -y);
    drawPixel(-x, -y);
    drawPixel(-x, y);
    drawPixel(y, x);
    drawPixel(y, -x);
    drawPixel(-y, -x);
    drawPixel(-y, x);
}

void MainWindow::drawPixel(int x, int y){

    img.setPixel(x+xc, y+yc, qRgb(0, 0, 0));
}

void MainWindow::BresenhumCircle(){
    int d = 3 - (2*r);
    int x = 0, y = r;
    EightWaySymmetry(x, y);

    qDebug() << x << " " << y << " D:- " <<d;

    while(x <= y){
        if(d < 0){
            d += (4*x) + 6;
        }else{
            d += (4*x) - (4*y) + 10;
            y -= 1;
        }

        x += 1;
        EightWaySymmetry(x, y);

        qDebug() << x << " " << y << " D:- " <<d;

    }

     ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

