#pragma once

#include <SFML/System/Vector2.hpp>

#include <memory>

namespace Game
{

class Attachement;

class Hardpoint
{
public:
    Hardpoint() = default;
    Hardpoint(const Hardpoint& copy);
    ~Hardpoint() = default;

    Hardpoint& operator=(const Hardpoint& copy);

    bool hasAttachement() const;
    Attachement& getAttachement();
    const Attachement& getAttachement() const;
    void setAttachement(Attachement* aAttachement);
    void setAttachement(std::unique_ptr<Attachement>&& aAttachement);
    void removeAttachment();

    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& aPos);
    float getDirection() const;
    void setDirection(float aDir);

private:
    std::unique_ptr<Attachement> m_attachement;
    sf::Vector2f m_position;
    float m_direction;
};

}
