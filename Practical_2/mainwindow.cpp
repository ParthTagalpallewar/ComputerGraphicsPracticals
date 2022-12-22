#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <QTime>

QImage img(500, 500, QImage::Format_RGB888);
QVector<int> x_vertices{100, 100, 200, 200, 100};
QVector<int> y_vertices{100, 200, 200, 100, 100};
QVector<float> slopes;

int y_min = 1000, y_max = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    img.fill(Qt::white);
    ui->drawingArea->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::plotPoint( int x , int y ) {
    img.setPixel( QPoint( x , y )  , qRgb( 0 , 0 , 0 ) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2){
    if(x1 > x2  && y1 > y2){
        swap(&x1, &x2);
        swap(&y1, &y2);
    }



    int dx = x2-x1;
    int dy = y2-y1;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);



    dx = dx / steps;
    dy = dy / steps;

    for(int i=0; i<steps; i++){
        plotPoint(x1, y1);
        x1 += dx;
        y1 += dy;
    }

    ui -> drawingArea -> setPixmap( QPixmap::fromImage( img ) ) ;

}

void MainWindow::drawPolygon(){
    int vertices = x_vertices.count()-1;

    qDebug() << vertices << "count";

    for(int i=0; i<vertices; i++){
        drawLine(x_vertices[i], y_vertices[i], x_vertices[i+1], y_vertices[i+1]);
    }
}

void MainWindow::on_startFilling_clicked()
{
    calminmax();
    calSlope();
    scanLine();
}

void MainWindow::calminmax(){
    for(int i: y_vertices){
        y_min = std::min(y_min, i);
        y_max = std::max(y_max, i);
    }
}

void MainWindow::calSlope(){

    int vertices = x_vertices.count()-1;

    for(int i=0; i<vertices; i++){
        int dx = x_vertices[i+1] - x_vertices[i];
        int dy = y_vertices[i+1] - y_vertices[i];

        float slope = 0.0f;

        if(dx == 0.0){
            slope = 0.0f;
        }if(dy == 0.0){
            slope = 1.0f;
        }
        else{
            slope = (float)dy/(float)dx;
        }

        slopes.append(slope);
    }
}

void MainWindow::scanLine(){
    int vertices = x_vertices.count()-1;

    for(int y=y_min; y<y_max; y++){

        QVector<int> x_inter;

        for(int i=0; i<vertices; i++){
            int y_vertex_min = std::min(y_vertices[i], y_vertices[i+1]);
            int y_vertex_max = std::max(y_vertices[i], y_vertices[i+1]);

            //y should be between vertex min y and max y
            if(y > y_vertex_min && y <= y_vertex_max){
                int x = x_vertices[i] + ( ( 1 / slopes[i] ) * ( y - y_vertices[i] ));
                x_inter.append(x);
            }
        }

        std::sort(x_inter.begin(), x_inter.begin());

        for( int i = 0 ; i < x_inter.count()-1 ; i+=2 ) {

            drawLine( x_inter[i] , y , x_inter[i+1]+1 , y) ;
            delay(20);
       }

    }
}

void MainWindow::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void MainWindow::on_pushButton_clicked()
{
    drawPolygon();
}

