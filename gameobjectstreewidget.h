#ifndef GAMEOBJECTSTREEWIDGET_H
#define GAMEOBJECTSTREEWIDGET_H

#include <QTreeWidget>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QIcon>
#include <iostream>
#include <QDropEvent>
#include <QDragEnterEvent>

#include "level.h"
#include "editor.h"

class GameObjectTreeItem: public QTreeWidgetItem
{
public:
    GameObjectTreeItem():QTreeWidgetItem()
    {
        this->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled| Qt::ItemIsDragEnabled|  Qt::ItemIsDropEnabled);
        this->setIcon(0, QIcon(":/sprites/icons/object.png"));
    }
    GameObject* m_game_object;
};


class GameObjectsTreeWidget: public QWidget
{
    Q_OBJECT
public:
    GameObjectsTreeWidget(QWidget* parent = nullptr):QWidget(parent)
    {
        init_tree(Editor::get_instance()->get_game()->get_curr_level());
    }
    ~GameObjectsTreeWidget()
    {
        delete m_level;
        delete m_new_object_bttn;
        delete m_tree_widget;
        delete m_layout;
    }
    void init_tree(Level* level = nullptr)
    {
        m_level = level;

        m_tree_widget = new QTreeWidget(this);

        m_tree_widget->setDragEnabled(true);
        m_tree_widget->setAcceptDrops(true);
        m_tree_widget->setDropIndicatorShown(true);
        m_tree_widget->setDragDropMode(QAbstractItemView::InternalMove);

        QObject::connect(m_tree_widget, &QTreeWidget::itemSelectionChanged, this, &GameObjectsTreeWidget::select_tree_item);
        QObject::connect(m_tree_widget, &QTreeWidget::itemChanged, this, &GameObjectsTreeWidget::select_tree_item);

        m_new_object_bttn = new QPushButton("New Game Object");
        QObject::connect(m_new_object_bttn, &QPushButton::clicked, this, &GameObjectsTreeWidget::create_empty_object_in_tree);
        //QObject::connect(, &QPushButton::clicked, this, &GameObjectsTreeWidget::create_empty_object_in_tree);

        m_tree_widget->setHeaderHidden(true);

        m_layout = new QVBoxLayout(this);

        m_layout->addWidget(m_new_object_bttn);
        m_layout->addWidget(m_tree_widget);
    }

    void create_game_object_tree_widget()
    {
        m_tree_widget->clear();
        for (auto game_object : m_level->get_all_game_objects())
        {
            if (game_object->get_parent() == nullptr)
            {
                GameObjectTreeItem* item = create_game_object_hierarchy(game_object);
                m_tree_widget->insertTopLevelItem(0, item);
            }
        }
    }

    QTreeWidget* get_tree_widget()
    {
        return m_tree_widget;
    }

    GameObject* get_selected_game_object()
    {
        if(!get_tree_widget()->selectedItems().empty())
        {
            GameObjectTreeItem* item = static_cast<GameObjectTreeItem*>(get_tree_widget()->selectedItems().front());

            return item->m_game_object;
        }
        return nullptr;
    }

    GameObjectTreeItem* get_selected_item()
    {
        GameObjectTreeItem* item = static_cast<GameObjectTreeItem*>(get_tree_widget()->selectedItems().front());
        return item;
    }

    GameObjectTreeItem* create_game_object_hierarchy(GameObject* game_object)
    {
        GameObjectTreeItem* item = new GameObjectTreeItem();
        item->setText(0, QString(game_object->get_name()));
        item->m_game_object = game_object;
        if (!game_object->get_all_children().empty())
        {
            for (auto child : game_object->get_all_children())
            {
                item->addChild(create_game_object_hierarchy(child));
            }
        }
        return item;
    }
    /*void dragEnterEvent(QDragEnterEvent *event){
        m_dragged_item = get_selected_item();
        this->dragEnterEvent(event);
    }

    void dropEvent(QDropEvent *event){
        event->position();
        if(m_dragged_item){
            GameObjectTreeItem* dParent = static_cast<GameObjectTreeItem*>(m_dragged_item->parent());
            if(dParent){
                dParent->removeChild(m_dragged_item);
                dParent->insertChild(0, m_dragged_item);
            }
        }
    }*/
signals:

    void item_selected(GameObject* game_object);

public slots:

    void select_tree_item()
    {
        if (!get_tree_widget()->selectedItems().empty())
        {
            GameObjectTreeItem* item = static_cast<GameObjectTreeItem*>(get_tree_widget()->selectedItems().first());

            if (item != nullptr && item->m_game_object != nullptr)
            {
                GameObject* game_object = item->m_game_object;
                Editor::get_instance()->set_selected_game_obj(game_object);
                emit item_selected(game_object);
                std::cout << "\nitem_selected" << std::endl;

            }
        }

    }

    void create_empty_object_in_tree()
    {
        GameObject* new_object = new GameObject();
        GameObjectTreeItem* item = new GameObjectTreeItem();
        item->setText(0, QString(new_object->get_name()));
        item->m_game_object = new_object;
        this->m_level->add_game_object(new_object);
        m_tree_widget->insertTopLevelItem(0, item);
        emit object_added(new_object);
    }
signals:
    void object_added(GameObject* game_object);

private:

    Level* m_level;
    QPushButton* m_new_object_bttn;
    QTreeWidget* m_tree_widget;
    QVBoxLayout* m_layout;
    //GameObjectTreeItem* m_dragged_item;
};
#endif // GAMEOBJECTSTREEWIDGET_H
