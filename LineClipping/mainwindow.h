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

    void dda(float x1, float y1, float x2, float y2);
    void plot(float x, float y);
    void drawBox();
    void calculate_minmax();
    void clip(int x1, int y1, int x2, int y2);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
