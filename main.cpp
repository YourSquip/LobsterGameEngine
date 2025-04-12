#include "mainwindow.h"
#include "gamemap.h"

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget* central_widget = new QWidget(&w);
    GameMap* game_map = new GameMap(central_widget);
    game_map->make_grid(1,1);

    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);
    fileMenu->addAction("Save");
    fileMenu->addAction("Exit");

    QVBoxLayout* vert_layout = new QVBoxLayout(central_widget);

    vert_layout->setMenuBar(menuBar);

    vert_layout->addWidget(game_map);
    MapGridBorders* borders = new MapGridBorders(central_widget);
    borders->resize(400,400);
    w.setCentralWidget(central_widget);

    w.show();
    return a.exec();
}
