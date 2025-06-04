#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QGraphicsScene>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QIcon icon(":/sprites/app_icon.png");
    a.setWindowIcon(icon);
    MainWindow w;

    w.show();

    return a.exec();


}
