#ifndef COMPONENTWIDGET_H
#define COMPONENTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "gameobject.h"
#include "Components.h"

class ComponentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComponentWidget(QWidget *parent = nullptr)
    {
        m_layout = new QVBoxLayout(this);
    }

private:
    GameObject* m_curr_object;
    QVBoxLayout* m_layout;
public slots:
    void show_object_data(GameObject* game_object)
    {
        m_curr_object = game_object;
        if(COMPONENTS.positions.count(game_object->get_id()) != 0)
        {
            QVBoxLayout* component_layout = new QVBoxLayout(this);
            component_layout->addWidget(new QLabel("Position"));
            m_layout->addLayout(component_layout);
        }
    }
};


#endif // COMPONENTWIDGET_H
