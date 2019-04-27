#pragma once

#include <SFML/Graphics/Drawable.hpp>

namespace Game
{

class Player : public sf::Drawable
{
public:
    void update(float aDt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
};

}
