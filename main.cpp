#include "mainwindow.h"
#include "gamemap.h"

#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QGraphicsScene>

#include "centralview.h"
#include "gamemap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QWidget* main_widget = new QWidget(&w);
    QWidget* central_widget = new QWidget(main_widget);
    central_widget->setMinimumSize(200,200);
    //central_widget->setMaximumHeight(700);
    central_widget->setStyleSheet("background-color:black;");
    QWidget* left_widget = new QWidget(main_widget);
    left_widget->setMinimumSize(200,300);
    left_widget->setMaximumWidth(400);
    left_widget->setStyleSheet("background-color:blue;");
    QWidget* right_widget = new QWidget(main_widget);
    right_widget->setMinimumSize(200,300);
    right_widget->setMaximumWidth(400);
    right_widget->setStyleSheet("background-color:red;");
    //----------------

    QVBoxLayout* left_layout = new QVBoxLayout(left_widget);
    QMenuBar*  left_menu_bar = new QMenuBar();
    QMenu *file_menu = new QMenu("File");
    left_menu_bar->addMenu(file_menu);
    left_layout->setMenuBar(left_menu_bar);

    //----------------

     QVBoxLayout* central_layout = new QVBoxLayout(central_widget);
     QWidget* central_down = new QWidget(central_widget);
     central_down->setStyleSheet("background-color:green;");
     CentralView* view = new CentralView(central_widget);
     central_layout->addWidget(view);
     central_layout->addWidget(central_down);
     central_layout->addWidget(new Tile(central_widget));

     QGraphicsScene scene;
     //scene.add
    //----------------



    QHBoxLayout* whole_layout = new QHBoxLayout(main_widget);
    whole_layout->addWidget(left_widget);
    whole_layout->addWidget(central_widget);
    whole_layout->addWidget(right_widget);


    /*GameMap* game_map = new GameMap(central_widget);
    game_map->make_grid(1,1);

    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);
    fileMenu->addAction("Save");
    fileMenu->addAction("Exit");

    QVBoxLayout* vert_layout = new QVBoxLayout(central_widget);

    vert_layout->setMenuBar(menuBar);

    vert_layout->addWidget(game_map);
    //MapGridBorders* borders = new MapGridBorders(central_widget);
    borders->resize(400,400);*/
    w.setCentralWidget(main_widget);

    w.show();
    return a.exec();
}
