#pragma once

#include "../IState.hpp"
#include "../Game/Enemy.hpp"
#include "../Game/Player.hpp"

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>

#include <deque>

namespace Game
{
namespace States
{

class GameState : public IState
{
public:
    GameState();

    void handleEvent(const sf::Event& aEvent) override;
    void update(float aDt) override;
    void preDraw(sf::RenderTarget& aTarget) override;
    void draw(sf::RenderTarget& aTarget) override;
    void postDraw(sf::RenderTarget& aTarget) override;

private:
    void generateStarfields();

    void startEncounter();

    Game::Player m_player;
    std::deque<Game::Enemy> m_enemies;

    sf::VertexArray m_starfield1, m_starfield2;
    sf::View m_gameView;
};

}
}
