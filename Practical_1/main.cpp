#include "mainwindow.h"

#include <QApplication>
#include <QtGui>
#include <QLabel>

void dda_line(int x1, int y1, int x2, int y2, QImage* image){

    float dx = (float) x2 - x1;
    float dy = (float) y2 - y1;

    float steps = std::max(dx, dy);

    dx = dx/steps;
    dy = dy/steps;

    for(int i=0; i<=steps; i++){

        image->setPixel(x1, y1, qRgb(250, 250, 250));
        x1 += dx;
        y1 += dy;
    }
};

void EightWaySymmetricPlot(int xc,int yc,int x,int y, QImage* image)
  {
   image->setPixel(x+xc, y+yc, qRgb(250, 250, 250));
//   image->setPixel(x+xc,-y+yc, qRgb(250, 250, 250));
//   image->setPixel(-x+xc,-y+yc, qRgb(250, 250, 250));
//   image->setPixel(-x+xc,y+yc, qRgb(250, 250, 250));

//   image->setPixel(y+xc,x+yc, qRgb(250, 250, 250));
//   image->setPixel(y+xc,-x+yc, qRgb(250, 250, 250));
//   image->setPixel(-y+xc,-x+yc, qRgb(250, 250, 250));
//   image->setPixel(-y+xc,x+yc, qRgb(250, 250, 250));
  };

void BresenhamCircle(int xc,int yc,int r, QImage* image)
   {
    int x=0,y=r,d=3-(2*r);
    EightWaySymmetricPlot(xc,yc,x,y, image);

    while(x<=y)
     {
      if(d<=0)
             {
        d=d+(4*x)+6;
      }
     else
      {
        d=d+(4*x)-(4*y)+10;
        y=y-1;
      }
       x=x+1;
       EightWaySymmetricPlot(xc,yc,x,y, image);
      }
    }

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(450, 450);
    w.setWindowTitle("Practical Number 1");

    QImage image(400, 400, QImage::Format_RGB888);

    //Creating Rectangle
    dda_line(100, 100, 300, 100, &image);
    dda_line(100, 100, 100, 300, &image);
    dda_line(100, 300, 300, 300, &image);
    dda_line(300, 100, 300, 300, &image);

    //vertical center = 150
    //horizontal center = 200

    //Creating Rhombus
    dda_line(200, 100, 100, 200, &image);
    dda_line(100, 200, 200, 300, &image);
    dda_line(200, 300, 300, 200, &image);
    dda_line(200, 100, 300, 200, &image);

    //circle
    BresenhamCircle(200, 200, 70, &image);

    QLabel i;
    i.setPixmap(QPixmap::fromImage(image));

    i.show();
    return a.exec();
}




