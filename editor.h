#ifndef EDITOR_H
#define EDITOR_H

#include <QDebug>
#include <QString>
#include <QMap>

#include "game.h"

class Editor
{
public:
    Editor();

private:
    Game* m_game;
};

#endif // EDITOR_H
