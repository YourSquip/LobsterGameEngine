#include "mainwindow.h"
//#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Lobster Engine");
    this->setStyleSheet("background-color: #3d3d45; color : white; border-color: black;" );
    EditorWidget* editor_widget = new EditorWidget(this);
    this->setCentralWidget(editor_widget);
}



MainWindow::~MainWindow()
{
}


