#include "game.h"
#include "mainwindow.h"

//#include <QVBoxLayout>
//#include <QPushButton>
Game::Game()
{
    resize(DOT_WIDTH * FIELD_WIDTH, DOT_HEIGHT * FIELD_HEIGHT);// размер поля
    Gamestart();
}

void Game::timerEvent(QTimerEvent * e)
{
    Q_UNUSED(e);
    if (p_inGame) {// если мы находимся в игре
        eatenApple();// проверка, съели ли яблоко
        move();
        chekField(); // проверка границы поля
    }
    this->repaint(); // перемальовка самого себе
}

void Game::keyPressEvent(QKeyEvent *event) //нажатие кнопки
{
    int key = event->key();
    if (key == Qt::Key_Left  && m_dir != Directions::right) { m_dir = Directions::left;  } // Влево - невозможно вправо
    if (key == Qt::Key_Right && m_dir != Directions::left)  { m_dir = Directions::right; } // вправо - невозможно влево
    if (key == Qt::Key_Up    && m_dir != Directions::down)  { m_dir = Directions::up;    } // вверх - невозможно вниз
    if (key == Qt::Key_Down  && m_dir != Directions::up)    { m_dir = Directions::down;  } // вниз - невозможно вверх
    if (key == Qt::Key_Escape)   {qApp->quit(); } // закритя вікна
    if (key == Qt::Key_Space) {g_pause();} // пауза

}

void Game::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); doDrawing();// функция для отрисовки
}

void Game::doDrawing()
{
    QPainter qp(this);
    if (p_inGame){
    setStyleSheet("background-color:lightgreen;");
    qp.setBrush(Qt::red);
    qp.drawEllipse(m_apple.x() * DOT_WIDTH, m_apple.y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
    for (int i = 0; i <  m_dots.size(); ++i) {
        if (i == 0) {
            qp.setBrush(Qt::darkBlue);
            qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        } else {
            qp.setBrush(Qt::blue);
            qp.drawEllipse(m_dots[i].x() * DOT_WIDTH, m_dots[i].y() * DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT);
        }
    }
    } else {
        gameOver();
    }
}

void Game::Apple() // расположение яблока
{
    QTime time = QTime::currentTime();// инициализация рандома яблока, вызов таймера
    srand((uint) time.msec());// время в мс
    m_apple.rx() = rand() % DOT_WIDTH; //рандом по х
    m_apple.ry() = rand() % DOT_HEIGHT;// рандом по у
}

void Game::move() { // движение змейки

    for (int i = m_dots.size()-1; i > 0; --i) {// двигает хвост на место предпоследнего элемента, то есть все элементы на элемент вперед
    m_dots[i] = m_dots[i-1];
    }
    switch (m_dir) {
        case left:  { m_dots[0].rx() -=1; break; } // движене влево, х уменьшается
        case right: { m_dots[0].rx() +=1; break; } // движение вправо, х увеличивается
        case up:    { m_dots[0].ry() -=1; break; } // движение вверх, у уменьшается
        case down:  { m_dots[0].ry() +=1; break; } // движение вниз, у увеличивается

    }
}

void Game::chekField() {
    if (m_dots.size() > 4) {// если более 4 элементов змейки, она может себя укусить
    for (int i = 1; i < m_dots.size(); ++i) {// проверка
        if (m_dots[0] == m_dots[i]) { // если голова равна какому-то не первому элементу
            p_inGame = false; // завершение игры
        }} }
    if (m_dots[0].x() >= FIELD_WIDTH)  { p_inGame = false; } // проверка на выход за пределы поля
    if (m_dots[0].x() < 0)             { p_inGame = false; }
    if (m_dots[0].y() >= FIELD_HEIGHT) { p_inGame = false; }
    if (m_dots[0].y() < 0)             { p_inGame = false; }

    if (!p_inGame) {       // Если мы не в игре, остановка таймера
    killTimer(g_timerId);
    t_active=false;
    }
}
void Game::gameOver() { // выводим окно что игра закончилась
     QMessageBox msgb;
     msgb.setWindowTitle("Змейка"); // название окна
     msgb.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна
     msgb.setText("Игра окончена! Нажмите 'Ок' чтобы начать заново."); // вывод сообщения об окончании игры
     msgb.exec(); // выполнение
     initGame(); // После выполнения возвращаемся в initGame
}

void Game::eatenApple() {
    if (m_apple == m_dots[0]) {  //  если яблокок = голова
         m_dots.push_back(QPoint (0,0)); // добавляется часть тела
         if (m_dots.size() == 625) {
             Win();
         } else {
        Apple(); // рандом яблока
         }
    }
}
void Game::Win() { // выводим окно что игра закончилась
     QMessageBox msgb;
     msgb.setWindowTitle("Змейка"); // название окна
     msgb.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна
     msgb.setText("Вы победили! Нажмите 'Ок' чтобы начать заново"); // вывод сообщения об окончании игры
     msgb.exec(); // выполнение
     initGame(); // После выполнения возвращаемся в initGame
}

void Game::Gamestart()
{
    QMessageBox msgb;
    msgb.setWindowTitle("Змейка"); // название окна
    msgb.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна
    msgb.setText("Вы в игре. Нажмите 'ОК' для начала игры.");
    msgb.exec();
    initGame();
}

void Game::g_pause() //пауза
{
   // QTimer m_timerId;
    if (t_active)
        {
            killTimer(g_timerId);
        }
   // m_timer.stop();
    QMessageBox msgb;
      msgb.setWindowTitle("Змейка"); // название окна
      msgb.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна
      msgb.setText("Вы в режиме паузы. Нажмите 'ОК' для продолжения");
      msgb.exec();
     startTimer(DELAY);
     t_active=true;
     }

void Game::initGame()
{
    p_inGame = true; // если мы в игре
    m_dir = right; // начальное напрвление змейки вправо
    m_dots.resize(2); // начальный размер змейки = 2
    for (int i = 0; i < m_dots.size(); ++i) // начальное расположение змейки
    {
        m_dots[i].rx() = m_dots.size() - i - 1; // расположение змейки
        m_dots[i].ry() = 0;
    }
    Apple(); // розположення яблока

  g_timerId = startTimer(DELAY); // запуск таймера
  t_active=true;

}
