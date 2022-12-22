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

    void plot(float x, float y, uint color);
    void dda(float x1, float y1, float x2, float y2, uint color);

    void transform(float x1, float y1);
    void scale(float x, float y);
    void rotation(int angle);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H


