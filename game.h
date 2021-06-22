#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QKeyEvent>
#include <QApplication>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QIcon>
#include <QObject>
#include <QTime>
class Game : public QWidget
{
public: Game();
protected:
    void timerEvent(QTimerEvent*) override;
    void keyPressEvent(QKeyEvent *event) override; // Обработка нажатия клавиш
    void paintEvent(QPaintEvent *event) override;// отрисовка
    void inGameEvent();
private:

    static const int DOT_WIDTH   = 25; // ширина ячейки
    static const int DOT_HEIGHT  = 25;
    static const int FIELD_WIDTH   = 25; // умноженное на DOT_WIDTH для размера поля
    static const int FIELD_HEIGHT = 25; // высота умноженная на DOT_HEIGHT
   static const int DELAY = 200; //  Время движения змейки по 1 клетке

    void doDrawing(); //отрисовка
    void Apple(); // расположение яблока
    void move(); // движение змейки
    void chekField(); // проверка на конец поля
    void gameOver(); // конец игры
    void Win(); // Победа
    void eatenApple();// проверка яблока
    void Gamestart();
    int g_timerId; // таймер
    QPoint m_apple; // точка нахождения яблока
    void g_pause();
    int g_timepause;

    enum Directions { // изменения для стрелок
        left, right, up, down
    };

   Directions m_dir; // изменение движения змейки

    bool p_inGame;
    QVector<QPoint> m_dots; // вектор хранящий информацию о всех частях тела змейки
    void initGame();
    bool t_active=false;


};
#endif // GAME_H
