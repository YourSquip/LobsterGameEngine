#include "mainwindow.h"
#include "gamemap.h"

#include <QApplication>
#include <QWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget* central_widget = new QWidget(&w);
    GameMap* game_map = new GameMap(central_widget);
    game_map->make_grid(1,1);

    w.setCentralWidget(central_widget);

    w.show();
    return a.exec();
}
