#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //registering
    MapTileFactory::register_tile(QString("grass"),create_grass_tile);
    MapTileFactory::register_tile(QString("water"),create_water_tile);
    MapTileFactory::register_tile(QString("ground"),create_ground_tile);

    ui->setupUi(this);
    this->setWindowTitle("Lobster Engine");
    this->setStyleSheet("background-color: #3d3d45; color : white; border-color: black;" );

    QWidget* main_widget = new QWidget(this);
    QWidget* central_widget = new QWidget(main_widget);
    central_widget->setMinimumSize(200,200);

    central_widget->setStyleSheet("background-color:#3d3d45;");

    //GameObjectsTreeWidget* left_widget = new GameObjectsTreeWidget(nullptr,main_widget);
    GameObjectsTreeWidget* left_widget = new GameObjectsTreeWidget(Editor::get_instance()->get_game()->get_curr_level(),main_widget);
    left_widget->setMinimumSize(200,200);
    left_widget->setMaximumWidth(400);

    ComponentWidget* right_widget = new ComponentWidget(main_widget);
    right_widget->setMinimumSize(200,300);
    right_widget->setMaximumWidth(400);


    QVBoxLayout* left_layout = new QVBoxLayout(left_widget);
    QMenuBar*  left_menu_bar = new QMenuBar();
    QMenu *file_menu = new QMenu("File");
    QMenu *create_menu = new QMenu("Create");
    left_menu_bar->addMenu(file_menu);
    left_menu_bar->addMenu(create_menu);
    left_layout->setMenuBar(left_menu_bar);

    //----------------

    QVBoxLayout* central_layout = new QVBoxLayout(central_widget);

    MapTileListWidget* central_down = new MapTileListWidget(central_widget);

    LevelGraphicsView* view = new LevelGraphicsView(central_widget);
    GameObjectLayer* game_object_layer = new GameObjectLayer(Editor::get_instance()->get_game()->get_curr_level());


    view->get_current_scene()->addItem(game_object_layer);
    EditorToolsWidget* editor_tools = new EditorToolsWidget(view,nullptr);
    RunStopGameWidget* run_stop_window = new RunStopGameWidget();
    run_stop_window->set_game_window(central_widget);

    central_layout->addWidget(run_stop_window);
    central_layout->addWidget(editor_tools);
    central_layout->addWidget(view);
    central_layout->addWidget(central_down);

    QGraphicsScene scene;

    QHBoxLayout* whole_layout = new QHBoxLayout(main_widget);
    whole_layout->addWidget(left_widget);
    whole_layout->addWidget(central_widget);
    whole_layout->addWidget(right_widget);

    this->setCentralWidget(main_widget);

}



MainWindow::~MainWindow()
{
    delete ui;
}

