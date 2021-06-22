#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "game.h"
#include <QDialog>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 //QTime m_timerId;
private slots:
    void pauseSlot();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::MainWindow *ui;
    Game *game;

};

#endif // MAINWINDOW_H
