#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QGraphicsScene>
#include <QObject>

#include "gameobjectstreewidget.h"
#include "levelgraphicsview.h"
#include "runstopgamewidget.h"
#include "gamewindow.h"
#include "maptilelistwidget.h"
#include "componentwidget.h"
#include "editortoolswidget.h"
#include "gameobjectlayer.h"
#include "editor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
