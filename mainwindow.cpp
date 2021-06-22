#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include "game.h"
#include <QTimer>
MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Game();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::pauseSlot(){

}
void MainWindow::on_pushButton_clicked()
{
    game->show();  // Показ игры
    this->close();    // закрываем меню
}
void MainWindow::on_pushButton_2_clicked()
{
    this->close();    // закрываем меню
}
