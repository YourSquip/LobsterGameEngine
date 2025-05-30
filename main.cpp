#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QGraphicsScene>

#include "gameobjectstreewidget.h"
#include "levelgraphicsview.h"
#include "runstopgamewidget.h"
#include "gamewindow.h"
#include "maptilelistwidget.h"
#include "componentwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Lobster Engine");
    w.setStyleSheet("background-color: #3d3d45; color : white; border-color: black;" );
    QIcon icon(":/sprites/app_icon.png");
    a.setWindowIcon(icon);
    QWidget* main_widget = new QWidget(&w);
    QWidget* central_widget = new QWidget(main_widget);
    central_widget->setMinimumSize(200,200);
    //central_widget->setMaximumHeight(700);
    central_widget->setStyleSheet("background-color:#3d3d45;");
    //QWidget* left_widget = new QWidget(main_widget);
    GameObjectsTreeWidget* left_widget = new GameObjectsTreeWidget(nullptr,main_widget);
    left_widget->setMinimumSize(200,200);
    left_widget->setMaximumWidth(400);
    //left_widget->setStyleSheet("background-color:blue;");
    //QWidget* right_widget = new QWidget(main_widget);
    ComponentWidget* right_widget = new ComponentWidget(main_widget);
    right_widget->setMinimumSize(200,300);
    right_widget->setMaximumWidth(400);
    //right_widget->setStyleSheet("background-color:red;");
    //----------------

    QVBoxLayout* left_layout = new QVBoxLayout(left_widget);
    QMenuBar*  left_menu_bar = new QMenuBar();
    QMenu *file_menu = new QMenu("File");
    QMenu *create_menu = new QMenu("Create");
    left_menu_bar->addMenu(file_menu);
    left_menu_bar->addMenu(create_menu);
    left_layout->setMenuBar(left_menu_bar);

    //----------------

     QVBoxLayout* central_layout = new QVBoxLayout(central_widget);
     //QWidget* central_down = new QWidget(central_widget);
     MapTileListWidget* central_down = new MapTileListWidget(central_widget);
     //central_down->setStyleSheet("background-color:green;");
     LevelGraphicsView* view = new LevelGraphicsView(central_widget);
     RunStopGameWidget* run_stop_window = new RunStopGameWidget();
     run_stop_window->set_game_window(central_widget);
     //QLabel* game_loop_is_running_lbl = new QLabel("game loop is not running");
    //run_stop_window->setMinimumSize(200,200);

     //central_layout->addWidget(game_loop_is_running_lbl);
     central_layout->addWidget(run_stop_window);
     central_layout->addWidget(view);
     central_layout->addWidget(central_down);


     QGraphicsScene scene;




    QHBoxLayout* whole_layout = new QHBoxLayout(main_widget);
    whole_layout->addWidget(left_widget);
    whole_layout->addWidget(central_widget);
    whole_layout->addWidget(right_widget);


    w.setCentralWidget(main_widget);

    w.show();

    return a.exec();


}
