#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<math.h>

QImage j(600,600,QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
delete ui;
}
void MainWindow::DDA_Line(float x1,float y1,float x2,float y2)
{
//DDA Line Drawing Algorithm
float step, dx, dy, i, x, y;

dx = x2-x1;
dy = y2-y1;
if(abs(dx)>=abs(dy))
{
step = abs(dx);
}
else
{
step = abs(dy);
}
x = x1;
y = y1;
i = 0;
dx = (dx/step);
dy = (dy/step);
while (i<=step)
{
j.setPixel((x),(y),qRgb(150,40,255));
x = x + dx;
y = y + dy;
i++;
}
}

void MainWindow::koch(float it, float x1, float y1, float x5, float y5)
{
int x2,x3,x4,y2,y3,y4;
int dx,dy;
if(it == 0)
{
DDA_Line(x1,y1,x5,y5);
}
else
{
dx = (x5-x1)/3;
dy = (y5-y1)/3;
x2=x1+dx;
y2=y1+dy;
x3=(int)(0.5*(x1+x5)+sqrt(3)*(y1-y5)/6);
y3=(int)(0.5*(y1+y5)+sqrt(3)*(x5-x1)/6);
x4=2*dx+x1;
y4=2*dy+y1;
koch(it-1,x1,y1,x2,y2);
koch(it-1,x2,y2,x3,y3);
koch(it-1,x3,y3,x4,y4);
koch(it-1,x4,y4,x5,y5);
}
}
void MainWindow::on_pushButton_clicked()
{
 int it = ui->textEdit->toPlainText().toInt();
koch(it,600,350,0,350);
//koch(it,280,280,150,20);
//koch(it,20,280,280,280);
ui->label->setPixmap(QPixmap::fromImage(j));
}
