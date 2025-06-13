#ifndef GAMEOBJECTSTATES_H
#define GAMEOBJECTSTATES_H

class GameObjectStates
{
public:
    GameObjectStates()
    {
        m_controlable = false;
        m_interactable = false;
        m_can_interact = false;
    }

    bool m_controlable;
    bool m_interactable;
    bool m_can_interact;
};

#endif // GAMEOBJECTSTATES_H
