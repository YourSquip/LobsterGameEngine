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
#include <QFileDialog>

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
        m_position = dynamic_cast<Position*>(component);
        x_line = new QLineEdit(QString::fromStdString(std::to_string(m_position->x())));
        y_line = new QLineEdit(QString::fromStdString(std::to_string(m_position->y())));

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
        connect(m_component,m_component->item_changed,this,this->update_x_component_info);
        connect(m_component,m_component->item_changed,this,this->update_y_component_info);
        connect(x_line,x_line->textChanged,this,this->update_x_component);
        connect(y_line,y_line->textChanged,this,this->update_y_component);
    }
public slots:

    void update_x_component_info(Component* component)
    {
        m_position = dynamic_cast<Position*>(component);
        x_line->setText(QString::number(m_position->x()));
    }
    void update_y_component_info(Component* component)
    {
        m_position = dynamic_cast<Position*>(component);
        y_line->setText(QString::number(m_position->y()));

    }

    void update_x_component()
    {
        m_position->set_x(x_line->text().toInt());
    }


    void update_y_component()
    {
        m_position->set_y(y_line->text().toInt());
    }
private:
    QLabel* x_label;
    QLineEdit* x_line;

    QLabel* y_label;
    QLineEdit* y_line;
    Position* m_position;
};

class SpriteComponentInfoWidget:public ComponentInfoWidget
{
public:
    SpriteComponentInfoWidget(Component* component, QWidget* parent = nullptr):ComponentInfoWidget(component,parent)
    {

        qDebug()<<"SpriteComponentInfoWidget";
        m_sprite = dynamic_cast<Sprite*>(component);

        m_label =  new QLabel("pixmap:",this);
        m_pixmap = new QLabel(this);
        m_pixmap->setPixmap(m_sprite->get_pixmap().scaled(32,32));
        m_open_pixmap_button = new QPushButton("Choose sprite",this);
        connect(m_open_pixmap_button,m_open_pixmap_button->clicked,this,this->open_sprite_explorer);
        connect(m_sprite,m_sprite->item_changed,this,this->update_pixmap_component_info);
        QHBoxLayout* layout = new QHBoxLayout();


        layout->addWidget(m_label);
        layout->addWidget(m_pixmap);


        m_layout->addLayout(layout);
        m_layout->addWidget(m_open_pixmap_button);
        //connect(m_component,m_component->item_changed,this,this->update_x_component_info);
        //connect(m_component,m_component->item_changed,this,this->update_y_component_info);
        //connect(x_line,x_line->textChanged,this,this->update_x_component);
        //connect(y_line,y_line->textChanged,this,this->update_y_component);

    }
public slots:
    void open_sprite_explorer()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File", "../sprites", "Images (*.png *.xpm *.jpg)");
        if (!fileName.isEmpty()) {
            // Process the selected file
            QPixmap pixmap(fileName);
            m_sprite->set_pixmap(pixmap.scaled(32,32));
            qDebug()<<"file name:"<<fileName;
        }
    }
    void update_pixmap_component_info(Component* component)
    {
        m_sprite = dynamic_cast<Sprite*>(component);
        //x_line->setText(QString::number(m_position->x()));
        m_pixmap->setPixmap(m_sprite->get_pixmap());
    }

private:
    QLabel* m_label;
    QLabel* m_pixmap;
    Sprite* m_sprite;
    QPushButton* m_open_pixmap_button;

};

#endif // COMPONENTINFOWIDGET_H
