#ifndef COMPONENTINFOWIDGET_H
#define COMPONENTINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPixmap>
#include <QImage>
#include <QPushButton>

#include "component.h"

class ComponentInfoWidget:public QWidget
{
public:
    ComponentInfoWidget(Component* component, QWidget* parent = nullptr):QWidget(parent)
    {
        m_component = component;
        m_name = new QLabel(component->get_name(),this);

        qDebug()<<"name:"<<component->get_name();
        m_layout = new QVBoxLayout(this);
        m_layout->addWidget(m_name);
        qDebug()<<"ComponentInfoWidget";
        this->setVisible(true);
    }
protected:
    QLabel* m_name;
    QVBoxLayout* m_layout;
    Component* m_component;
};

class PositionComponentInfoWidget:public ComponentInfoWidget
{
public:
    PositionComponentInfoWidget(Component* component, QWidget* parent = nullptr):ComponentInfoWidget(component,parent)
    {

        qDebug()<<"PositionComponentInfoWidget";
        Position* position = dynamic_cast<Position*>(component);
        x_line = new QLineEdit(QString::fromStdString(std::to_string(position->x())));
        y_line = new QLineEdit(QString::fromStdString(std::to_string(position->y())));

        x_label =  new QLabel("x:",this);
        y_label =  new QLabel("y:",this);

        QHBoxLayout* x_layout = new QHBoxLayout(this);
        x_layout->addWidget(x_label);
        x_layout->addWidget(x_line);

        QHBoxLayout* y_layout = new QHBoxLayout(this);
        y_layout->addWidget(y_label);
        y_layout->addWidget(y_line);

        m_layout->addLayout(x_layout);
        m_layout->addLayout(y_layout);
        this->show();
    }
private:
    QLabel* x_label;
    QLineEdit* x_line;

    QLabel* y_label;
    QLineEdit* y_line;
};

class SpriteComponentInfoWidget:public ComponentInfoWidget
{
public:
    SpriteComponentInfoWidget(Component* component, QWidget* parent = nullptr):ComponentInfoWidget(component,parent)
    {

        qDebug()<<"SpriteComponentInfoWidget";
        Sprite* sprite = dynamic_cast<Sprite*>(component);

        m_label =  new QLabel("pixmap:",this);
        m_pixmap = new QLabel(this);
        m_pixmap->setPixmap(sprite->get_pixmap().scaled(32,32));
        QHBoxLayout* layout = new QHBoxLayout();

        layout->addWidget(m_label);
        layout->addWidget(m_pixmap);

        m_layout->addLayout(layout);


    }
private:
    QLabel* m_label;
    QLabel* m_pixmap;

};

#endif // COMPONENTINFOWIDGET_H
