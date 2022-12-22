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

    void EightWaySymmetry(int x, int y);
    void BresenhumCircle();
    void drawPixel(int x, int y);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
