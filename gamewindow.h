#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>

#include "game.h"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr)
    {
        test_label = new QLabel("GAME WINDOW",this);
    }
private:
    QLabel* test_label;
signals:


};

#endif // GAMEWINDOW_H
