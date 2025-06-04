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
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include "editorwidget.h"

QT_BEGIN_NAMESPACE

class MainWindow;

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


};
#endif // MAINWINDOW_H
