#include <QApplication>
#include "game.h"
#include <QIcon>
#include "mainwindow.h"
//#include <QWidget>


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

      MainWindow mainmenu; // вызываем класс
      mainmenu.setWindowTitle("Змейка"); // название окна
      mainmenu.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна
      mainmenu.show();// вывод
      return app.exec(); // запуск основного цикла программы

   Game game; // вызываеммый классс
   game.setWindowTitle("Змейка"); // назва окна
   game.setWindowIcon(QIcon(":/resources/Image/Icon.png")); // картинка окна

   return app.exec(); // запуск основного цикла программы
}
