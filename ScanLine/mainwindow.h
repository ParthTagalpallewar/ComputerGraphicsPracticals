#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void plotPoint( int x , int y );
    void drawLine(int x1, int y1, int x2, int y2);
    void swap(int *a, int *y);
    void drawPolygon();

    void calminmax();
    void calSlope();
    void scanLine();

    void delay(int millisecondsToWait);

private slots:
    void on_startFilling_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
