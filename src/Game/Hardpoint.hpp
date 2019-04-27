#pragma once

#include "HardpointOwner.hpp"

#include <memory>

namespace sf { class Transformable; }

namespace Game
{

class Attachement;

class Hardpoint
{
public:
    Hardpoint();
    Hardpoint(const Hardpoint& copy);
    ~Hardpoint() = default;

    Hardpoint& operator=(const Hardpoint& copy);

    bool hasAttachement() const;
    Attachement& getAttachement();
    const Attachement& getAttachement() const;
    void setAttachement(Attachement* aAttachement);
    void setAttachement(std::unique_ptr<Attachement>&& aAttachement);
    void removeAttachment();

    sf::Vector2f getGlobalPosition() const;
    float getGlobalDirection() const;

    void setParent(const HardpointOwner* aTransformable);
    const HardpointOwner* getParent() const;

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& aPos);
    float getDirection() const;
    void setDirection(float aDir);

private:
    std::unique_ptr<Attachement> m_attachement;
    sf::Vector2f m_position;
    float m_direction;

    const HardpointOwner* m_parent;
};

}
