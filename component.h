#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QPixmap>

class Component
{
public:
    Component()
    {

    }
    virtual ~Component()
    {

    }
    virtual QString get_name()=0;
    QString m_name;
};


class Position: public Component
{
public:
    Position()
    {
        m_name = "position";
        m_x = 0;
        m_y = 0;
    }
    Position(unsigned int x, unsigned int y)
    {
        m_name = "position";
        m_x = x;
        m_y = y;
    }
    float x()
    {
        return m_x;
    }
    float y()
    {
        return m_x;
    }

    void set_x(unsigned int x)
    {
        m_x = x;
    }
    void set_y(unsigned int y)
    {
        m_y = y;
    }

    QString get_name() override
    {
        return m_name;
    }
private:
    float m_x;
    float m_y;
};

class Sprite: public Component
{
public:
    Sprite()
    {
        m_name = "sprite";
        m_pixmap = QPixmap(":/sprites/icons/object.png");
    }

    Sprite(QPixmap pixmap)
    {
        m_name = "sprite";
        m_pixmap = pixmap;
    }


    QPixmap get_pixmap()
    {
        return m_pixmap;
    }

    void set_pixmap(QPixmap pixmap)
    {
        m_pixmap = pixmap;
    }

    QString get_name() override
    {
        return m_name;
    }

private:
    QPixmap m_pixmap;
};


#endif // COMPONENT_H
